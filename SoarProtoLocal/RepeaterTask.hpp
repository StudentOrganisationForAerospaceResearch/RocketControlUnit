/**
 ******************************************************************************
 * File Name          : RepeaterTask.hpp
 * Description        :
 ******************************************************************************
*/
#ifndef SOAR_SYSTEM_PROTOCOL_REPEATER_HPP_
#define SOAR_SYSTEM_PROTOCOL_REPEATER_HPP_
/* Includes ------------------------------------------------------------------*/
#include "Task.hpp"
#include "SystemDefines.hpp"
#include "UARTTask.hpp"
#include "WriteBufferFixedSize.h"
#include "CoreProto.h"
#include "ControlMessage.hpp"
#include "ProtocolTask.hpp"

/* Enums ------------------------------------------------------------------*/
enum REPEATER_TASK_COMMANDS {
    REPEATER_TASK_COMMAND_NONE = 0,
    EVENT_REPEATER_RX_COMPLETE = PROTOCOL_TX_REQUEST_DATA + 1 // We start after Protocol Task Commands
};

/* Macros ------------------------------------------------------------------*/
// Task Definition
constexpr uint8_t TASK_REPEATER_PRIORITY = 2;            // Priority of the repeater task
constexpr uint8_t TASK_REPEATER_QUEUE_DEPTH_OBJS = 10;        // Size of the repeater task queue
constexpr uint16_t TASK_REPEATER_STACK_DEPTH_WORDS = 300;        // Size of the repeater task stack


/* Class ------------------------------------------------------------------*/
class RepeaterTask : public Task
{
public:
    RepeaterTask(UART_HandleTypeDef* huart, uint16_t uartTaskCmd);

    virtual void InitTask() = 0;

    //Public Interfaces
    // Sends data to the linked UART. Does not wrap in transport layer, use SendProtobufMessage for messages not already wrapped
    inline void SendData(uint8_t* data, uint16_t size);

    // Sends a protobuf message to the linked UART. Wraps in transport layer, does processing in the calling task
    void SendProtobufMessage(EmbeddedProto::WriteBufferFixedSize<DEFAULT_PROTOCOL_WRITE_BUFFER_SIZE>& writeBuffer, Proto::MessageID msgId);

    //Functions exposed to HAL callbacks
    void InterruptRxData();

protected:
    void Run(void* pvParams);    // Main run code
    
    bool ReceiveData();          // Arms the UART to receive data

    // Member variables
    uint8_t* protocolRxBuffer;
    uint16_t protocolMsgIdx;
    bool isProtocolMsgReady;

    uint8_t protocolRxChar; // Character received from UART Interrupt

    const UART_HandleTypeDef* uartHandle;
    const uint16_t uartTaskCommand;
};

inline void RepeaterTask::SendData(uint8_t* data, uint16_t size)
{
    Command cm;
    cm.CopyDataToCommand(data, size);

    // Send it to the UART task using the task's registered uartTaskCommand
    UARTTask::Inst().SendCommandReference(cm);
}

#endif    // SOAR_SYSTEM_PROTOCOL_REPEATER_TASK_HPP_
