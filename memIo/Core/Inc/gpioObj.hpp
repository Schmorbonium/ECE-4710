#include "stm32f1xx_hal.h"

class GPIO
{
    public:
    GPIO(GPIO_TypeDef* GPIO_PORT,uint16_t pin);
    void toggle();
    void enable();
    void disable();
    private:
    // GPIO_TypeDef hello;
    // struct GPIO_TypeDef* GPIO_PORT;
    GPIO_TypeDef* GPIO_PORT;
    uint16_t pin;
    bool on;
};