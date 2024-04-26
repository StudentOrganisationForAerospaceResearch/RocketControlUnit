#
# FILE: Codec.py
# BRIEF: This file contains the codec class for the Command and Telemetry Protocol
# AUTHOR: Christopher Chan (cjchanx)
#

from cobs import cobs   # pip install cobs
from crc import Calculator, Crc16 # pip install crc

# Constants and helpers
PROTO_CHKSUM_BYTES = 2
PROTO_MSGID_BYTES = 2

def GetCOBSOverhead(unencodedSize):
    return unencodedSize // 254 + 1

# Main class - import this class to use the codec
class Codec:
    @staticmethod
    def GetEncodedSize(unencodedSize):
        # The encoded size is the unencoded size + 1 byte for the message ID + COBS Overhead + 1 byte for the 0x00 delimiter
        return unencodedSize + 1 + GetCOBSOverhead(unencodedSize + 1) + 1

    @staticmethod
    def Encode(buf, length, msgId): #TODO: Write descriptions ask what msgid refers to
        
        # Make a new buffer encoded with just the message ID and enough space for the checksum
        encodedBuf = bytearray(length+1)

        # We encode the message ID first
        encodedBuf[0] = msgId

        # Then we copy the rest of the buffer
        for i in range(0, length):
            encodedBuf[i+1] = buf[i]

        # Calculate a checksum
        calc = Calculator(Crc16.XMODEM)
        chksum = calc.checksum(encodedBuf)

        #print(f'Calculated checksum: {chksum}')

        # Then we append the checksum in little endian order
        encodedBuf.append(chksum & 0xFF)
        encodedBuf.append((chksum >> 8) & 0xFF)

        # Then we encode the whole thing in COBS
        cobsEncodedBuf = cobs.encode(encodedBuf)
        encodedBuf = bytearray(cobsEncodedBuf)

        # Add a 0x00 for delimiting the end of the message
        encodedBuf.append(0)

        return encodedBuf

    @staticmethod
    def Decode(buf, length):

        #print(buf)
        #print(f'my buf len: {len(buf)}')
        # Decode the buffer
        decodedBuf = cobs.decode(buf)

        #print('my len is ' + f'{len(decodedBuf)}')

        # Verify the checksum (untested)
        bufChksm = decodedBuf[-2:]
        bufChksm = bufChksm[0] + (bufChksm[1] << 8)
        calc = Calculator(Crc16.XMODEM)
        chksum = calc.checksum(decodedBuf[:-2])

        #TODO: This is untested, may not work
        # If the checksum is valid, get rid of the checksum. Otherwise, print and return invalid data
        if chksum == bufChksm:
            decodedBuf = decodedBuf[:-2]
        else:
            print(f'Error: Checksum invalid')
            return None, None

        # The first byte is the message ID
        msgId = decodedBuf[0]

        # The rest of the buffer is the data and checksum
        data = decodedBuf[1:]



        return msgId, data