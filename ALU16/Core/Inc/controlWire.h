#ifndef __CONTROLWIRE
#define __CONTROLWIRE

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f1xx_hal.h"
#include "main.h"

// This file implements a CD74HCT165E package to read 8 bit of parallel data
//  Copyright Schmorbonium 2023 
//  Author Isaac Christensen

void updateControlWires();



#ifdef __cplusplus
}
#endif

#endif /* CONTROLWIRE */