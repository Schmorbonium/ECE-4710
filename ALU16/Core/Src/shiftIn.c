#include "shiftIn.h"
#include <stdlib.h>
// This file implements a CD74HCT165E package to read 8 bit of parallel data
//  Copyright Schmorbonium 2023 
//  Author Isaac Christensen



uint8_t* inputData;
uint8_t* dataInClk = 0;  // This value is controlled elsewhere
uint8_t activeRead; 
uint8_t SIcurrentChip =0;
uint8_t SIcurrentBit  =0;
uint8_t shiftInDepth = 0;
// data is read on low clock


void init_shiftIn(uint8_t newDepth, uint8_t* GlobalClk){
    shiftInDepth = newDepth;
    inputData = (uint8_t*)malloc(sizeof(uint8_t)*shiftInDepth);
    dataInClk = GlobalClk;
    SIcurrentBit = 0;
    activeRead = 0;
}

uint16_t getParData(uint8_t index){
    return ((uint16_t)inputData[index*2+1])|((uint16_t)inputData[index*2]<<8);
}

void serialInTick(){ 
    if(*dataInClk){ 
        // activeWrite
        // --------------- Clock High -------------------------- 
        SIcurrentBit++;
        if(SIcurrentBit > 7){
            SIcurrentBit = 0;
            // End of chip, se we start the next chip read
            inputData[SIcurrentChip] = activeRead;
            activeRead = 0;
            SIcurrentChip++;
            if(SIcurrentChip >= shiftInDepth){
                // if we hit our chip shiftInDepth, we restart. and write to the lock pin. 
                SIcurrentChip = 0;
                 HAL_GPIO_WritePin(lockRead_GPIO_Port,lockRead_Pin,GPIO_PIN_RESET);
            }
        }

    }else{
        // --------------- Clock low -------------------------- 
        if(SIcurrentChip == 0 && SIcurrentBit == 0){
            //  we want to set the lock to zero so new data is not pushed on to the displays during display.
            HAL_GPIO_WritePin(lockRead_GPIO_Port,lockRead_Pin,GPIO_PIN_SET);
        }
        uint8_t pinVal = HAL_GPIO_ReadPin(dataRead_GPIO_Port,dataRead_Pin);
        activeRead |= pinVal << (7-SIcurrentBit);
        // Aline the next bit of data
    }
}
