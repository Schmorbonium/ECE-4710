// This file implements a CD74HCT165E package to read 8 bit of parallel data
//  Copyright Schmorbonium 2023 
//  Author Daniel Nelson
//  Editor Isaac Christensen (moved it out of main) 
#include "controlWire.h"
#include "main.h"
#include <stdlib.h>
#include "shiftIn.h"

#define OP_ADD 0
#define OP_SUB 1
#define OP_AND 2
#define OP_OR 3
#define OP_XOR 4
#define OP_SHL 5
#define OP_SHRA 6
#define OP_SHRL 7

// extern uint8_t overrideOutput = 0;
extern uint8_t overRideOut;
extern uint16_t overRideVal;

void setOpState(uint8_t state) {
  //turn off all buffers
  HAL_GPIO_WritePin(bufAddEn_GPIO_Port, bufAddEn_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(bufNorEn_GPIO_Port, bufNorEn_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(bufOrEn_GPIO_Port, bufOrEn_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(bufXorEn_GPIO_Port, bufXorEn_Pin, GPIO_PIN_SET);
  
  //enable non-inverted input buffers
  HAL_GPIO_WritePin(invA_GPIO_Port, invA_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(invB_GPIO_Port, invB_Pin, GPIO_PIN_RESET);
  //set specific buffers based on state
  overRideOut = 0;
  switch (state) {
  case OP_ADD:
    HAL_GPIO_WritePin(bufAddEn_GPIO_Port, bufAddEn_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(carryIn_GPIO_Port, carryIn_Pin, GPIO_PIN_RESET); // Disable Carry In
    // Carry in has no default for performance reasons.
    break;
  case OP_SUB:
    HAL_GPIO_WritePin(bufAddEn_GPIO_Port, bufAddEn_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(invB_GPIO_Port, invB_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(carryIn_GPIO_Port, carryIn_Pin, GPIO_PIN_SET); // Enable Carry In
    break;
  case OP_AND:
    HAL_GPIO_WritePin(bufNorEn_GPIO_Port, bufNorEn_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(invA_GPIO_Port, invA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(invB_GPIO_Port, invB_Pin, GPIO_PIN_SET);
    break;
  case OP_OR:
    HAL_GPIO_WritePin(bufOrEn_GPIO_Port, bufOrEn_Pin, GPIO_PIN_RESET);
    break;
  case OP_XOR:
    HAL_GPIO_WritePin(bufXorEn_GPIO_Port, bufXorEn_Pin, GPIO_PIN_RESET);
    break;
  case OP_SHL:
    overRideOut = 1;
    {
      uint16_t valA = getParData(2);
      uint16_t valB = getParData(1);
      overRideVal = valA << ((signed)valB);
    }
    break;
  case OP_SHRA:
    overRideOut = 1;
    {
      uint16_t valA = getParData(2);
      uint16_t valB = getParData(1);
      overRideVal = ((signed)valA) >> ((signed)valB);
    }
    //TODO
    break;
  case OP_SHRL:
    overRideOut = 1;
    {
      uint16_t valA = getParData(2);
      uint16_t valB = getParData(1);
      overRideVal = valA >> ((signed)valB);
    }
    //TODO
    break;
  }
}

void updateControlWires(){
    uint8_t opState = (HAL_GPIO_ReadPin(ctrlCin_GPIO_Port, ctrlCin_Pin) << 2)
      | (HAL_GPIO_ReadPin(ctrlBin_GPIO_Port, ctrlBin_Pin) << 1)
      | (HAL_GPIO_ReadPin(ctrlAin_GPIO_Port, ctrlAin_Pin));
    setOpState(opState);
}
