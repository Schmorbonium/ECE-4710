#include "charBuffer.hpp"
#include "stm32f1xx_it.h"

class BufferedUart
{
private:
    bool listening;
    bool sending;
    CharBuffer TxQue;
    CharBuffer RxQue;
    UART_HandleTypeDef* uart;
    void startSending();
    void stopSending();
public:
    BufferedUart(UART_HandleTypeDef* Core);
    virtual void uartHandler();
    void startListening();
    void stopListening();
    void send(uint8_t* buf, uint16_t length);
    void takeFromInbox(uint8_t* buf, uint16_t size);
    uint16_t getInputSize();
    uint16_t getOutputSize();
};