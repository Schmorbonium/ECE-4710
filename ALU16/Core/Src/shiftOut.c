#include "shiftOut.h"
#include <stdlib.h>

// This file implements a mm5486n package to run a 4 digit 4 segment display 
//  Copyright Schmorbonium 2023 
//  Author Isaac Christensen



uint32_t* segD;
uint16_t* segVal;
uint8_t* shiftOutClk = 0; // Even Is clock high, odd is shiftOutClk low.
uint32_t activeWrite; 
uint8_t currentWord =0;
uint8_t currentBit  =0;
uint8_t depth = 0;
// data is sent on low clock

char segTable[16] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A
    0x7C, // B
    0x39, // C
    0x5E, // D
    0x79, // E
    0x71  // F
};

uint32_t toSegD(uint16_t value);

void setupSegD(){
    for(int i =0;i<depth;i++){
        segD[i] = toSegD(segVal[i]);
    }
}


void init_shiftOut(uint8_t newDepth, uint8_t* GlobalshiftOutClk){
    depth = newDepth;
    segD = malloc(sizeof(uint32_t)*depth);
    segVal = malloc(sizeof(uint16_t)*depth);
    shiftOutClk = GlobalshiftOutClk;
    currentBit = 0;

    for(int i = 0; i<depth;i++){    
        segVal[i] = 1111;
    }
    
    setupSegD();
}


uint32_t toSegD(uint16_t value){
    uint32_t segData = 0;
    for(int i =0;i<4;i++){
        uint8_t val = (value >> (i * 4))&0xF;
        segData |= segTable[val];
        if(i == 3){
            break;
        }
        segData = segData << 8;
    }
    return segData;
}

void sendData(uint8_t index, uint16_t data){
    segVal[index] = data;
    setupSegD();
}

void segTick(){ 
    if(*shiftOutClk){ 
        // activeWrite
        // --------------- Clock High -------------------------- 
        currentBit++;
        if(currentBit > 32){
            currentBit = 0;
            // End of chip, se we start the next chip write
            currentWord++;
            if(currentWord >= depth){
                // if we hit our chip depth, we restart. and write to the lock pin. 
                currentWord = 0;
                HAL_GPIO_WritePin(lockWrite_GPIO_Port,lockWrite_Pin,GPIO_PIN_SET);
            }
            activeWrite = segD[currentWord];
        }

    }else{
        // --------------- Clock low -------------------------- 
        if(currentWord == 0 && currentBit == 0){
            //  we want to set the lock to zero so new data is not pushed on to the displays during display.
            HAL_GPIO_WritePin(lockWrite_GPIO_Port,lockWrite_Pin,GPIO_PIN_RESET);
        }
        if(activeWrite&0x1){
            HAL_GPIO_WritePin(dataWrite_GPIO_Port,dataWrite_Pin,GPIO_PIN_SET);
        }else{
            HAL_GPIO_WritePin(dataWrite_GPIO_Port,dataWrite_Pin,GPIO_PIN_RESET);
        }
        // Aline the next bit of data
        activeWrite = activeWrite>>1;
    }
}
