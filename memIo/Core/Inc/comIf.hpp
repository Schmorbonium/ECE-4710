#include "stm32f1xx_hal.h"

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

class encoder{

};

class decoder{


};

class PktField{
    public:
    char* encode();
    void decode(char*);
    protected:
    virtual bool SetNextField();
    uint16_t length;
    uint16_t place;
    bool terminal;
    PktField* next;
};

class Header:public PktField{
    bool SetNextField();
};

class ResetData:public PktField{
    bool SetNextField();
};

class SetMemData:public PktField{
    bool SetNextField();
};

class GetMemData:public PktField{
    bool SetNextField();
};

class GetRegData:public PktField{
    bool SetNextField();
};

class SetRegData:public PktField{
    bool SetNextField();
};

class GetPcData:public PktField{
    bool SetNextField();
};

class SetPcData:public PktField{
    bool SetNextField();
};

template<class T>
class pktNode{

}



