#include "charBuffer.hpp"
#include "stm32f1xx_it.h"

class BufferedUart
{
private:
    CharBuffer TxQue;
    CharBuffer RxQue;
    UART_HandleTypeDef* Uart;
public:
    virtual void UartHandler();
    virtual void newData();
    void Send();
    uint8_t dataAvailable();
};

class BufferedUart
{
private:
    CharBuffer TxQue;
    CharBuffer RxQue;

public:
    virtual void UartHandler();
    virtual void newData();
    void Send();
    uint8_t dataAvailable();
};