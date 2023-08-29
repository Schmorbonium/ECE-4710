#ifndef __CH74HCT165E
#define __CH74HCT165E

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f1xx_hal.h"
#include "main.h"

// This file implements a CD74HCT165E package to read 8 bit of parallel data
//  Copyright Schmorbonium 2023 
//  Author Isaac Christensen

void init_shiftIn(uint8_t newDepth, uint8_t* GlobalClk);

uint16_t getParData(uint8_t index);

void serialInTick();


#ifdef __cplusplus
}
#endif

#endif /* CH74HCT165E */