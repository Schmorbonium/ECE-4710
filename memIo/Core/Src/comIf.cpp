#include "comIf.h"




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

struct Header
{
    uint8_t cmd;
    uint8_t dataBytes;
    uint8_t unused;
    uint8_t Flags;
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

class comIf : BufferedUart
{
private:
    Header curHeader;
    uint8_t *curData;

public:
    bool packetReady();
    bool getPacket();
    virtual void respond(uint8_t *data, uint8_t dataLength);
    virtual void send(Header header, uint8_t *data, uint8_t dataLength);
};
