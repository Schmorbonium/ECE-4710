#ifndef __COM_IF_PKT__
#define __COM_IF_PKT__

#include "comIf.h"
#include "bufferedUart.hpp"
#include "charBuffer.hpp"

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

typedef uint32_t MemAddr_t;
typedef uint32_t MemVal_t;
// typedef uint32_t MemAddr_t;

class PacketField
{
protected:
    uint8_t data;

public:
    PacketField() {}
    PacketField(uint8_t data);
    PacketField(CharBuffer *que);
    virtual void parseFromQue(CharBuffer *que);
    virtual void appendToQue(CharBuffer *que);
    void setByte(uint8_t flags);
    uint8_t getByte();
};

class FlagField : public PacketField
{
protected:
    FlagField() {}

public:
    FlagField(uint8_t flags);
    FlagField(CharBuffer *que);
    void setFlag(uint8_t index);
    void resetFlag(uint8_t index);
    bool getFlag(uint8_t index);
};

class UnusedField : public PacketField
{
protected:
public:
    UnusedField() : PacketField() {}
    UnusedField(CharBuffer *que);
    virtual void parseFromQue(CharBuffer *que);
    virtual void appendToQue(CharBuffer *que);
};

class FullWordField : public PacketField
{
protected:

public:
    uint32_t data;
    FullWordField() {}
    FullWordField(uint32_t data);
    FullWordField(CharBuffer *que);
    virtual void parseFromQue(CharBuffer *que);
    virtual void appendToQue(CharBuffer *que);
    void setWord(uint32_t Word);
    uint8_t getWord();
};

class Header : public PacketField
{
protected:
    PacketField cmd;
    PacketField dataLen;
    UnusedField unused;
    FlagField flags;

public:
    Header();
    Header(cmdID cmd, uint8_t dataSize, uint8_t flags);
    Header(CharBuffer *que);
    virtual void parseFromQue(CharBuffer *que);
    virtual void appendToQue(CharBuffer *que);

    bool isAResponse();
    bool responseRequested();

    void setIsAResponse(bool value);
    void setResponseRequested(bool value);
};

class MemMap : public FillWordField
{
    
};

class Payload : public FullWordField
{
protected:
    uint16_t dataLen =0;
    FullWordField *data;

public:
    Payload() {}
    Payload(uint8_t length)
    {
        dataLen = length;
        data = new FullWordField[dataLen];
    }

    ~Payload(){
        delete data;
    }

    virtual void parseFromQue(CharBuffer *que)
    {
        for (uint8_t i = 0; i < dataLen; i++)
        {
            data[i] = FullWordField(que);
        }
    }

    virtual void appendToQue(CharBuffer *que)
    {
        for (uint8_t i = 0; i < dataLen; i++)
        {
            data[i].appendToQue(que);
        }
    }
};

class MemOp : public Payload
{
protected:
public:
    MemOp(CharBuffer *que,uint8_t dataLen):Payload(dataLen){
        parseFromQue(que);
    }
    MemAddr_t getStartAddr(){
        return data[0].data;
    }

};

class ComIfPkt
{
protected:
    ComIfPkt() {}
    Header header;
    Payload payload;

public:
    virtual void parseFromQue(CharBuffer *que) {}
    virtual void appendToQue(CharBuffer *que) {}

    static bool checkForFullPkt(CharBuffer *que);
    static bool ParseFullPkt(CharBuffer *que);
};

// struct SetMemMsg
// {
//     Header header;
//     MemAddr address;
//     uint32_t data[];
// };
// struct SetMemResponse
// {
//     Header header;
//     CmdStatus status;
// };

// struct GetMemData
// {
//     Header header;
//     MemAddr address;
//     uint32_t ReadLength;
// };
// struct GetMemResponse
// {
//     const Header header;
//     const CmdStatus status;
//     uint32_t data[];
// };

// struct GetRegData
// {
//     Header header;
//     uint32_t Register;
// };
// struct GetRegResponse
// {
//     Header header;
//     uint32_t RegisterVal;
// };

// struct SetRegData
// {
//     Header header;
//     uint32_t Register;
//     uint32_t value;
// };
// struct SetRegResponse
// {
//     Header header;
//     CmdStatus status;
// };

// struct GetPcData
// {
//     Header header;
// };
// struct GetPcResponse
// {
//     Header header;
//     uint32_t PC;
// };

// struct SetPcData
// {
//     Header header;
//     uint32_t value;
// };
// struct SetPcResponse
// {
//     Header header;
//     CmdStatus status;
// };

// switch ()
// {
// case rstPkt:

//     break;
// case setMem:
//     break;
// case getMem:
//     break;
// case dbSetReg:
//     break;
// case dbGetReg:
//     break;
// case dbFlags:
//     break;
// case dbSetPC:
//     break;
// case dbGetPC:
//     break;
// case dbPause:
//     break;
// case dbStep:
//     break;
// case dbGetBP:
//     break;
// case dbTogBP:
//     break;
// case dbTogDB:
//     break;
// default:
//     break;
// }

#endif //__COM_IF_PKT__