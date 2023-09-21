#ifndef __COM_IF_PKT__
#define __COM_IF_PKT__

#include "comIf.h"
#include "bufferedUart.hpp"
#include "charBuffer.hpp"

enum cmdID
{
    noOp = 0x0,
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

enum StatusEnum
{
    noFault = 0x1,
    parseFault = 0x2,
    memFault = 0x3,
};

typedef uint32_t MemAddr_t;
typedef uint32_t MemVal_t;

typedef uint8_t HeaderFlagSet;
enum HeaderFlag
{
    noFlags = 0x0,
    isAResponse = 0x1,
    responseRequested = 0x2,
    isCool = 0x4
};

// ------------------------ Primitive fields ---------------------------------- 
class PacketField
{
protected:
public:
    PacketField() {}
    virtual void parseFromQue(CharBuffer *que) {}
    virtual void appendToQue(CharBuffer *que) {}
};
class uint8_field : public PacketField
{
public:
    uint8_t data;
    uint8_field(uint8_t data) : PacketField(), data(data) {}
    uint8_field(CharBuffer *que) { parseFromQue(que); }
    virtual void parseFromQue(CharBuffer *que) { data = que->pop(); }
    virtual void appendToQue(CharBuffer *que) { que->append(data); }
};

class uint16_field : public PacketField
{
public:
    uint16_t data;
    uint16_field(uint16_t data) : PacketField(), data(data) {}
    uint16_field(CharBuffer *que) { parseFromQue(que); }
    virtual void parseFromQue(CharBuffer *que)
    {
        data =
            ((uint16_t)que->pop() << 8) |
            ((uint16_t)que->pop() << 0);
    }
    virtual void appendToQue(CharBuffer *que)
    {
        que->append((uint8_t)((data >> 8) & 0xFF));
        que->append((uint8_t)((data >> 0) & 0xFF));
    }
};
class UnusedField8 : public PacketField
{
protected:
public:
    UnusedField8() {}
    UnusedField8(CharBuffer *que) {}
    virtual void parseFromQue(CharBuffer *que)
    {
        que->pop();
    }
    virtual void appendToQue(CharBuffer *que)
    {
        que->append(0);
    }
};
class uint32_field : public PacketField
{
protected:
public:
    uint32_t data;
    uint32_field(uint32_t data) : PacketField(), data(data) {}
    uint32_field(CharBuffer *que) { parseFromQue(que); }
    virtual void parseFromQue(CharBuffer *que)
    {
        data =
            ((uint32_t)que->pop() << 24) |
            ((uint32_t)que->pop() << 16) |
            ((uint32_t)que->pop() << 8) |
            ((uint32_t)que->pop() << 0);
    }
    virtual void appendToQue(CharBuffer *que)
    {
        que->append((uint8_t)((data >> 24) & 0xFF));
        que->append((uint8_t)((data >> 16) & 0xFF));
        que->append((uint8_t)((data >> 8) & 0xFF));
        que->append((uint8_t)((data >> 0) & 0xFF));
    }
};

// ------------------------ Complex fields ---------------------------------- 
class StringField : public PacketField
{
protected:
    uint16_field len;
    char *string;

public:
    StringField(char *string, uint16_t strLeng) : len(strLeng)
    {
        string = new char[len.data];
        for (uint16_t i = 0; i < len.data; i++)
        {
            this->string[i] = string[i];
        }
    }

    StringField(CharBuffer *que) : len(que)
    {
        for (uint16_t i = 0; i < len.data; i++)
        {
            string[i] = que->pop();
        }
    }

    ~StringField()
    {
        delete string;
    }

    virtual void parseFromQue(CharBuffer *que)
    {
        len = uint16_field(que);
        for (uint16_t i = 0; i < len.data; i++)
        {
            string[i] = que->pop();
        }
    }

    virtual void appendToQue(CharBuffer *que)
    {
        len.appendToQue(que);
        for (uint16_t i = 0; i < len.data; i++)
        {
            que->append(string[i]);
        }
    }
};
class FlagField : public uint8_field
{
public:
    FlagField(uint8_t flags) : uint8_field(flags) {}
    FlagField(CharBuffer *que) : uint8_field(que) {}
    void setFlag(uint8_t index) { data |= (1 << index); }
    void resetFlag(uint8_t index) { data &= ~(1 << index); }
    bool getFlag(uint8_t index) { return data & (1 << index); };
};
class Header : public PacketField
{
protected:
    uint8_field cmd;
    uint8_field dataLen;
    UnusedField8 unused;
    FlagField flags;

public:
    Header(cmdID cmd, uint8_t dataSize, HeaderFlagSet flags) : cmd(cmd),
                                                         dataLen(dataSize),
                                                         flags(flags) {}
    Header(CharBuffer *que);
    virtual void parseFromQue(CharBuffer *que);
    virtual void appendToQue(CharBuffer *que);

    bool getFlag(HeaderFlag requestedFlag) { return flags.data & requestedFlag; }
    bool getFlags(HeaderFlagSet requestedFlag) { return flags.data & requestedFlag; }

    void overrideFlag(HeaderFlag targetFlag, bool value)
    {
        if (value)
        {
            flags.data |= targetFlag;
        }
        else
        {
            flags.data &= targetFlag;
        }
    }
    void setFlags(HeaderFlagSet flagSet) { flags.data |= flagSet; }
    void resetFlags(HeaderFlagSet flagSet) { flags.data &= flagSet; }
};

class StatusFeild : public PacketField
{
protected:
    uint16_field status;
    StringField msg;

public:
    StatusFeild(StatusEnum status,
                char *msg,
                uint16_t len) : status(status),
                                 msg(msg, len) {}

    StatusFeild(CharBuffer *que): status(que),
                                 msg(que) {}
    virtual void parseFromQue(CharBuffer *que) { 
        status = uint16_field(que);
        msg = StringField(que);
     }
    virtual void appendToQue(CharBuffer *que) { 
        status.appendToQue(que);
        msg.appendToQue(que);
    }

};

// ------------------------ CompletePackets ---------------------------------- 
class ComIfPkt
{
protected:
    Header header;

public:
    ComIfPkt(CharBuffer* que): header(que){}
    ComIfPkt(CharBuffer* que): header(noOp,0,noFlags){}

    virtual void parseFromQue(CharBuffer *que) {}
    virtual void appendToQue(CharBuffer *que) {}

    static bool checkForFullPkt(CharBuffer *que);
    static bool ParseFullPkt(CharBuffer *que);
};










// class Payload : public PacketField
// {
// protected:
//     uint16_t dataLen = 0;
//     FullWordField *HeapData;

// public:
//     Payload() {}
//     Payload(uint8_t length)
//     {
//         dataLen = length;
//         HeapData = new FullWordField[dataLen];
//     }

//     ~Payload()
//     {
//         delete HeapData;
//     }

//     /// @brief This Pulling a packet out of the que implicitly calls whatever action is associated with the packet.
//     /// @param que This is Isaac's amazing char buffer the definitely does not leak memory.
//     virtual void parseFromQue(CharBuffer *que)
//     {
//         for (uint8_t i = 0; i < dataLen; i++)
//         {
//             HeapData[i] = FullWordField(que);
//         }
//     }

//     /// @brief This add this packets data to the end of the sending que
//     /// @param que This is Isaac's amazing char buffer the definitely does not leak memory.
//     virtual void appendToQue(CharBuffer *que)
//     {
//         for (uint8_t i = 0; i < dataLen; i++)
//         {
//             HeapData[i].appendToQue(que);
//         }
//     }
//     /// @brief This Appends a response for this packet to the given que. By default it is simply this header with the response flag set and no data.
//     virtual void appendResponseToQue(CharBuffer *que)
//     {
//     }
// };

// class LedOp : Payload
// {
// protected:
// public:
//     LedOp(CharBuffer *que) : Payload(1)
//     {
//     }

//     virtual void parseFromQue(CharBuffer *que)
//     {
//         for (uint8_t i = 0; i < dataLen; i++)
//         {
//             HeapData[i] = FullWordField(que);
//         }
//     }

//     virtual void appendToQue(CharBuffer *que)
//     {
//         for (uint8_t i = 0; i < dataLen; i++)
//         {
//             HeapData[i].appendToQue(que);
//         }
//     }
// };

// class MemOp : public Payload
// {
// protected:
// public:
//     MemOp(CharBuffer *que, uint8_t dataLen) : Payload(dataLen)
//     {
//         parseFromQue(que);
//     }
//     MemAddr_t getStartAddr()
//     {
//         return HeapData[0].data;
//     }
// };

// class MemoryOp : ComIfPkt
// {
// };

// class LedOp : ComIfPkt
// {
//     LedOp(CharBuffer *que)
//     {
//         parseFromQue(que);
//     }
//     virtual void parseFromQue(CharBuffer *que)
//     {
//         header.parseFromQue(que);
//         payload = new Payload(1);
//         payload->parseFromQue(que);
//         payload->getWord()
//     }
// };

#endif //__COM_IF_PKT__