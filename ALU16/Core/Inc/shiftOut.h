// This file implements a mm5486n package to run a 4 digit 4 segment display 
//  Copyright Schmorbonium 2023 
//  Author Isaac Christensen
#ifndef __MM5486N
#define __MM5486N

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "main.h"

#include "shiftOut.h"




void init_shiftOut(uint8_t, uint8_t*);

void sendData(uint8_t, uint16_t);

void segTick();


#ifdef __cplusplus
}
#endif

#endif /* MM5486N */