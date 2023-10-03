// vim: set ai et ts=4 sw=4:

// change for your MCU
#include "stm32f1xx_hal.h"

#include "max7219.h"

typedef enum {
    REG_NO_OP           = 0x00,
    REG_DIGIT_0         = 0x01,
    REG_DIGIT_1         = 0x02,
    REG_DIGIT_2         = 0x03,
    REG_DIGIT_3         = 0x04,
    REG_DIGIT_4         = 0x05,
    REG_DIGIT_5         = 0x06,
    REG_DIGIT_6         = 0x07,
    REG_DIGIT_7         = 0x08,
    REG_DECODE_MODE     = 0x09,
    REG_INTENSITY       = 0x0A,
    REG_SCAN_LIMIT      = 0x0B,
    REG_SHUTDOWN        = 0x0C,
    REG_DISPLAY_TEST    = 0x0F,
} MAX7219_REGISTERS;

void max7219_Init() {
    max7219_TurnOff();
    max7219_SendData(REG_SCAN_LIMIT, NUMBER_OF_DIGITS - 1);
    max7219_SendData(REG_DECODE_MODE, 0x00); // decode off
    max7219_Clean();
}

void max7219_SetIntensivity(uint8_t intensivity) {
    if (intensivity > 0x0F)
        return;

    max7219_SendData(REG_INTENSITY, intensivity);
}

void max7219_Clean() {
    for (int i = 1; i < 9; i++)
        max7219_SendData(i, MAX7219_SYM_BLANK);
}

void max7219_SendData(uint8_t addr, uint8_t data) {
    HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &addr, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_SET);
}

void max7219_TurnOn(void) {
    max7219_SendData(REG_SHUTDOWN, 0x01);
}

void max7219_TurnOff(void) {
    max7219_SendData(REG_SHUTDOWN, 0x00);
}