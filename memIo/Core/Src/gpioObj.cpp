#include "gpioObj.hpp"
#include "main.h"
   
GPIO::GPIO(GPIO_TypeDef* GPIO_PORT,uint16_t pin){
    this->GPIO_PORT = GPIO_PORT;
    this->pin = pin;
    this->on = false;
}

void GPIO::toggle(){
    HAL_GPIO_TogglePin(this->GPIO_PORT,this->pin);
    this->on = !this->on;
}
void GPIO::enable(){
    HAL_GPIO_WritePin(this->GPIO_PORT,this->pin,GPIO_PIN_SET);
    this->on = true;
}
void GPIO::disable(){
    HAL_GPIO_WritePin(this->GPIO_PORT,this->pin,GPIO_PIN_RESET);
    this->on = false;
}
