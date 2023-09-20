// #ifndef __COM_IF_PKT__
// #define __COM_IF_PKT__

// #include "comIf.h"
// #include "bufferedUart.hpp"
// #include "charBuffer.hpp"

// enum cmdID
// {
//     rstPkt = 0x1,
//     setMem = 0x2,
//     getMem = 0x3,
//     dbSetReg = 0x11,
//     dbGetReg = 0x12,
//     dbFlags = 0x13,
//     dbSetPC = 0x14,
//     dbGetPC = 0x15,
//     dbPause = 0x16,
//     dbStep = 0x17,
//     dbGetBP = 0x18,
//     dbTogBP = 0x19,
//     dbTogDB = 0x1A
// };

// enum StatusEnum
// {
//     noFault = 0x1,
//     parseFault = 0x2,
//     memFault = 0x3,
// };

// typedef uint32_t MemAddr_t;
// typedef uint32_t MemVal_t;

// class PacketField
// {
// protected:
// public:
//     PacketField() {}
//     virtual void parseFromQue(CharBuffer *que){}
//     virtual void appendToQue(CharBuffer *que){}
// };
// class uint8_field : PacketField
// {
// public:
//     uint8_t data;
//     uint8_field(uint8_t data) : PacketField(), data(data) {}
//     uint8_field(CharBuffer *que){parseFromQue(que);}
//     virtual void parseFromQue(CharBuffer *que){data = que->pop();}
//     virtual void appendToQue(CharBuffer *que){que->append(data);}
// };

// class uint16_field : PacketField
// {
// public:
//     uint16_t data;
//     uint16_field(uint16_t data) : PacketField(), data(data) {}
//     uint16_field(CharBuffer *que){parseFromQue(que);}
//     virtual void parseFromQue(CharBuffer *que){
//         data = 
//             ((uint16_t)que->pop() << 8 ) | 
//             ((uint16_t)que->pop() << 0 );
//         }
//     virtual void appendToQue(CharBuffer *que){
//         que->append((uint8_t)((data >> 8) & 0xFF));
//         que->append((uint8_t)((data >> 0) & 0xFF));
//     }
// };

// class uint32_field : public PacketField
// {
// protected:
// public:
//     uint32_t data;
//     uint32_field(uint32_t data) : PacketField(), data(data) {}
//     uint32_field(CharBuffer *que){parseFromQue(que);}
//     virtual void parseFromQue(CharBuffer *que){
//         data = 
//             ((uint32_t)que->pop() << 24 ) | 
//             ((uint32_t)que->pop() << 16 ) | 
//             ((uint32_t)que->pop() << 8  ) | 
//             ((uint32_t)que->pop() << 0  );
//         }
//     virtual void appendToQue(CharBuffer *que){
//         que->append((uint8_t)((data >> 24) & 0xFF));
//         que->append((uint8_t)((data >> 16) & 0xFF));
//         que->append((uint8_t)((data >> 8 ) & 0xFF));
//         que->append((uint8_t)((data >> 0 ) & 0xFF));
//     }
// };
// class StringField : public PacketField
// {
// protected:
//     uint16_field len;
//     char* string;
// public:
//     StringField(char* string, uint16_t strLeng) :len(strLeng) {
//         string = new char[len.data];
//         for (uint16_t i = 0; i < len.data; i++)
//         {
//             this->string[i] = string[i];
//         }
//     }

//     StringField(CharBuffer *que):len(que){
        
//         for (uint16_t i = 0; i < len.data; i++)
//         {
//             string[i] = que->pop();
//         }        
//     }

//     ~StringField(){
//         delete string;
//     }

//     virtual void parseFromQue(CharBuffer *que){
//         len = uint16_field(que);
//         for (uint16_t i = 0; i < len.data; i++)
//         {
//             string[i] = que->pop();
//         }        
//     }

//     virtual void appendToQue(CharBuffer *que){
//         len.appendToQue(que);
//         for (uint16_t i = 0; i < len.data; i++)
//         {
//             que->append(string[i]);
//         }
//     }
// };
// class FlagField : public uint8_field
// {
// public:
//     FlagField(uint8_t flags): uint8_field(flags) {}
//     FlagField(CharBuffer *que): uint8_field(que) {}
//     void setFlag(uint8_t index);
//     void resetFlag(uint8_t index);
//     bool getFlag(uint8_t index);
// };

// class UnusedField16 : public PacketField
// {
// protected:
// public:
//     UnusedField16(CharBuffer *que){}
//     virtual void parseFromQue(CharBuffer *que){
//         que->pop();
//     }
//     virtual void appendToQue(CharBuffer *que){
//         que->append(0);
//     }
// };


// class Header : public PacketField
// {
// protected:
//     PacketField cmd;
//     PacketField dataLen;
//     UnusedField unused;
//     FlagField flags;

// public:
//     Header();
//     Header(cmdID cmd, uint8_t dataSize, uint8_t flags);
//     Header(CharBuffer *que);
//     virtual void parseFromQue(CharBuffer *que);
//     virtual void appendToQue(CharBuffer *que);

//     bool isAResponse();
//     bool responseRequested();

//     void setIsAResponse(bool value);
//     void setResponseRequested(bool value);
// };

// class MemMap : public FullWordField
// {
    
// };
// class StatusFeild : public PacketField
// {
//     protected:
//     StatusEnum status;
//     char *msg;
//     uint8_t msgLen;

//     public:

//     StatusFeild(StatusEnum _status,char* msg,uint8_t len){
//         msgLen = len;
//         msg = new char[len];
//         status = _status;
//     }

//     StatusFeild(CharBuffer *buf){

//     }

//     ~StatusFeild(){
//         delete msg;
//     }

// };
// class Payload : public PacketField
// {
// protected:
//     uint16_t dataLen =0;
//     FullWordField *HeapData;
// public:
//     Payload() {}
//     Payload(uint8_t length)
//     {
//         dataLen = length;
//         HeapData = new FullWordField[dataLen];
//     }

//     ~Payload(){
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
//     LedOp(CharBuffer *que) :Payload(1)
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
//     MemOp(CharBuffer *que,uint8_t dataLen):Payload(dataLen){
//         parseFromQue(que);
//     }
//     MemAddr_t getStartAddr(){
//         return HeapData[0].data;
//     }
// };

// class ComIfPkt
// {
// protected:
//     ComIfPkt() {}
//     Header header;
//     Payload *payload;

// public:
//     virtual void parseFromQue(CharBuffer *que) {}
//     virtual void appendToQue(CharBuffer *que) {}

//     static bool checkForFullPkt(CharBuffer *que);
//     static bool ParseFullPkt(CharBuffer *que);
// };

// class MemoryOp: ComIfPkt
// {
// };

// class LedOp: ComIfPkt
// {
//     LedOp(CharBuffer* que){
//         parseFromQue(que);
//     }
//     virtual void parseFromQue(CharBuffer *que) {
//         header.parseFromQue(que);
//         payload = new Payload(1);
//         payload->parseFromQue(que);
//         payload->getWord()
//     }

// };


// #endif //__COM_IF_PKT__