#include "comIf.h"
#include "comIfPkts.hpp"
#include "bufferedUart.hpp"
#include "charBuffer.hpp"

typedef uint32_t CmdStatus;
typedef uint32_t MemAddr;
typedef uint32_t RegIndex;




// class ComputerInterfacePacket
// {
// private:
//     Header header;
//     bool PacketComplete;
//     ComputerInterfacePacket(Header header);

// public:
//     static uint8_t PeakPacketSize(CharBuffer inputBuffer)
//     {
//         return inputBuffer.peak(1);
//     }

//     static bool ReadyToParse(CharBuffer inputBuffer)
//     {
//         if (inputBuffer.getSize() < 4)
//         {
//             return false;
//         }
//         uint8_t packetSize = PeakPacketSize(inputBuffer);
//         if (inputBuffer.getSize() < packetSize)
//         {
//             return false;
//         }
//         return true;
//     }
//     static ComputerInterfacePacket *ParsePacket(CharBuffer* inputBuffer);
// };


// ComIf *interface;

/// @brief Initializes The computer interface on the given UART connection
/// @param Core Pointer to the HAL Uart Handle
void CompIfInit(UART_HandleTypeDef *Core)
{
    // interface = new
}

/// @brief This method handles the Uart interrupt for this interface
void CompIfUartInterruptHAndler();

/// @brief This Method handles all of the computer interface's work that can be completed synchonously.
void CompIfSyncHandler();
