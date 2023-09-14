#include "comIf.h"
#include "bufferedUart.hpp"
#include "charBuffer.hpp"

typedef uint32_t CmdStatus;
typedef uint32_t MemAddr;
typedef uint32_t RegIndex;

enum cmdID
{
    rstPkt = 0x1,
    setMem = 0x2,
    getMem = 0x3,
    dbSetReg = 0x11,
    dbGetReg = 0x12,
    dbFlags = 0x13,
    dbSetPC = 0x14,
    dbGetPC = 0x15,
    dbPause = 0x16,
    dbStep = 0x17,
    dbGetBP = 0x18,
    dbTogBP = 0x19,
    dbTogDB = 0x1A
};

class PacketField
{
protected:
    PacketField() {}
    uint8_t data;
public:
    PacketField(uint8_t data): data(data){}
    PacketField(CharBuffer* que){
        
    }
    virtual bool parseFromQue(CharBuffer* que) { data = que.pop(); }
    virtual bool appendToQue(CharBuffer* que) { que.append(data); }

    void setData(uint8_t flags) { data = flags; }
    uint8_t getData() { return data; }

};

class FlagField : public PacketField
{
protected:
    FlagField() {}
public:
    FlagField(uint8_t flags): PacketField(data){}
    void setFlag(uint8_t index) { data |= (1 << index); }
    void resetFlag(uint8_t index) { data &= ~(1 << index); }
    bool getFlag(uint8_t index) { return data & (1 << index); }
};

class Header : protected PacketField
{
protected:
    Header();
    PacketField cmd;
    PacketField dataLen;
    PacketField unused;
    FlagField flags;
public:
    Header(cmdID cmd, uint8_t dataSize, uint8_t flags) : cmd(PacketField(cmd)), datLen(dataSize), flags(flags) {}

    Header(CharBuffer que) : Header()
    {

        this->cmd = que.pop();
        this->datLen = que.pop();
        que.pop();
        this->flags = que.pop();
    }

    virtual bool appendToQue(CharBuffer que)
    {
        uint8_t raw[4] = {cmd, datLen, 0, flags};
        for (uint16_t i = 0; i < 4; i++)
        {
            que.append(raw[i]);
        }
    }
};
class ComputerInterfacePacket
{
private:
    Header header;
    bool PacketComplete;
    ComputerInterfacePacket(Header header);

public:
    static uint8_t PeakPacketSize(CharBuffer inputBuffer)
    {
        return inputBuffer.peak(1);
    }

    static bool ReadyToParse(CharBuffer inputBuffer)
    {
        if (inputBuffer.getSize() < 4)
        {
            return false;
        }
        uint8_t packetSize = PeakPacketSize(inputBuffer);
        if (inputBuffer.getSize() < packetSize)
        {
            return false;
        }
        return true;
    }
    static ComputerInterfacePacket *ParsePacket(CharBuffer inputBuffer);
};

struct SetMemMsg
{
    Header header;
    MemAddr address;
    uint32_t data[];
};
struct SetMemResponse
{
    Header header;
    CmdStatus status;
};

struct GetMemData
{
    Header header;
    MemAddr address;
    uint32_t ReadLength;
};
struct GetMemResponse
{
    const Header header;
    const CmdStatus status;
    uint32_t data[];
};

struct GetRegData
{
    Header header;
    uint32_t Register;
};
struct GetRegResponse
{
    Header header;
    uint32_t RegisterVal;
};

struct SetRegData
{
    Header header;
    uint32_t Register;
    uint32_t value;
};
struct SetRegResponse
{
    Header header;
    CmdStatus status;
};

struct GetPcData
{
    Header header;
};
struct GetPcResponse
{
    Header header;
    uint32_t PC;
};

struct SetPcData
{
    Header header;
    uint32_t value;
};
struct SetPcResponse
{
    Header header;
    CmdStatus status;
};
static ComputerInterfacePacket *ComputerInterfacePacket::ParsePacket(CharBuffer inputBuffer)
{
    Header header = Header(inputBuffer);
    ComputerInterfacePacket *pkt;
    switch (header.cmd)
    {
    case rstPkt:

        break;
    case setMem:
        break;
    case getMem:
        break;
    case dbSetReg:
        break;
    case dbGetReg:
        break;
    case dbFlags:
        break;
    case dbSetPC:
        break;
    case dbGetPC:
        break;
    case dbPause:
        break;
    case dbStep:
        break;
    case dbGetBP:
        break;
    case dbTogBP:
        break;
    case dbTogDB:
        break;
    default:
        break;
    }
}
class ComIf : BufferedUart
{
private:
public:
    ComIf(UART_HandleTypeDef *Core) : BufferedUart(Core)
    {
    }
    bool packetReady();
    ComputerInterfacePacket getPacket();
    virtual void send(Header header, uint8_t *data);
};

ComIf *interface;

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
