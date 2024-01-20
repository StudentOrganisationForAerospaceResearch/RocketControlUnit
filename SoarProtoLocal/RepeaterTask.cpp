/**
  ******************************************************************************
  * File Name          : RepeaterTask.cpp
  * Description        : The base RepeaterTask, includes basic logic for receiving until either
  *                      the buffer is full, or the end-frame byte for protocol is detected.
  ******************************************************************************
*/
#include "UARTTask.hpp"
#include "SystemDefines.hpp"
#include "RepeaterTask.hpp"
#include "cobs.h"

/**
 * @brief Constructor, sets all member variables
 */
RepeaterTask::RepeaterTask(UART_HandleTypeDef* huart, uint16_t uartTaskCmd) : Task(TASK_REPEATER_QUEUE_DEPTH_OBJS),
    uartTaskCommand(uartTaskCmd)
{
    // Setup Buffers
    protocolRxBuffer = soar_malloc(PROTOCOL_RX_BUFFER_SZ_BYTES + 1);
    memset(protocolRxBuffer, 0, PROTOCOL_RX_BUFFER_SZ_BYTES + 1);

    // Setup index and flags
    protocolMsgIdx = 0;
    isProtocolMsgReady = false;

    // Setup the internal variables
    uartHandle = huart;
}

/**
 * @brief Runcode for the RepeaterTask
 */
void RepeaterTask::Run(void* pvParams)
{
    // Arm the interrupt
    ReceiveData();

    while (1) {
        Command cm;

        // Wait forever for a command
        qEvtQueue->ReceiveWait(cm);

        // If this is a repeater Rx Complete event, process it
        if (cm.GetCommand() == PROTOCOL_COMMAND && cm.GetTaskCommand() == REPEATER_TASK_COMMANDS::EVENT_REPEATER_RX_COMPLETE) {
            SendData(protocolRxBuffer, protocolMsgIdx);

            // We can mark the rx buffer as safe to write to now
            protocolMsgIdx = 0;
            isProtocolMsgReady = false;
        }

        cm.Reset();
    }
}

/**
 * @brief Receive data, currently receives by arming interrupt
 */
bool RepeaterTask::ReceiveData()
{
    HAL_UART_Receive_IT((UART_HandleTypeDef*)uartHandle, &protocolRxChar, 1);
    return true;
}

/**
 * @brief Receive data to the buffer
 * @return Whether the protocolRxBuffer is ready or not
 */
void RepeaterTask::InterruptRxData()
{
    // If we already have an unprocessed protocol message, ignore this byte
    if (!isProtocolMsgReady) {
        // Check COBS byte for end of message
        if (protocolRxChar == '\0' || protocolMsgIdx == PROTOCOL_RX_BUFFER_SZ_BYTES) {
            // If the message is of insufficient length, reset the buffer
            if (protocolMsgIdx < PROTOCOL_MINIMUM_MESSAGE_LENGTH) {
                protocolMsgIdx = 0;
                isProtocolMsgReady = false;
            }
            else {
                // Null terminate and process
                protocolRxBuffer[protocolMsgIdx++] = '\0';
                isProtocolMsgReady = true;

                // Notify the protocol task
                Command cm(PROTOCOL_COMMAND, EVENT_PROTOCOL_RX_COMPLETE);
                bool res = qEvtQueue->SendFromISR(cm);

                // If we failed to send the event, we should reset the buffer, that way ProtocolTask doesn't stall
                if (res == false) {
                    protocolMsgIdx = 0;
                    isProtocolMsgReady = false;
                }
            }
        }
        else {
            protocolRxBuffer[protocolMsgIdx++] = protocolRxChar;
        }
    }

    //Re-arm the interrupt
    ReceiveData();
}

/*
 * @brief Interface function to quickly send a protobuf message by providing the write buffer and the message ID
 * @param writeBuffer The write buffer containing the serialized protobuf message
 * @param msgId The message ID of the message
 */
void RepeaterTask::SendProtobufMessage(EmbeddedProto::WriteBufferFixedSize<DEFAULT_PROTOCOL_WRITE_BUFFER_SIZE>& writeBuffer, Proto::MessageID msgId)
{
    // Note: This function runs inside the calling task
    uint8_t* data = writeBuffer.get_data();
    uint16_t size = writeBuffer.get_size();

    uint16_t msgSize = GET_COBS_MAX_LEN(size + PROTOCOL_OVERHEAD_BYTES);

    // Temporary array to store the pre-COBS message
    const uint16_t preCobsSize = size + PROTOCOL_OVERHEAD_BYTES;
    uint8_t arr[preCobsSize];

    // Wrap in the message header and checksum
    arr[0] = (uint8_t)msgId;
    memcpy(&(arr[1]), data, size);
    uint16_t chkSum = Utils::getCRC16(arr, size + 1);
    *((uint16_t*)&arr[preCobsSize - PROTOCOL_CHECKSUM_BYTES]) = chkSum;

    // Send the data by wrapping in a COBS frame and sending direct to UART Task
    Command protoTx(DATA_COMMAND, uartTaskCommand);
    protoTx.AllocateData(msgSize);

    // Encode in COBS
    cobs_encode_result cobsEncRes = cobs_encode(protoTx.GetDataPointer(), msgSize, arr, preCobsSize);

    if (cobsEncRes.status != COBS_ENCODE_OK) {
        protoTx.Reset();
        SOAR_PRINT("WARNING: COBS encode failed in repeater task\n");
    }

    SOAR_ASSERT(cobsEncRes.out_len + 1 == msgSize, "COBS Size Mismatch %d %d\n", cobsEncRes.out_len + 1, msgSize);
    protoTx.GetDataPointer()[msgSize - 1] = 0x00;
    UARTTask::Inst().SendCommandReference(protoTx);
}
