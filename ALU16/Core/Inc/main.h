/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define clkOut_Pin GPIO_PIN_1
#define clkOut_GPIO_Port GPIOA
#define lockRead_Pin GPIO_PIN_2
#define lockRead_GPIO_Port GPIOA
#define lockWrite_Pin GPIO_PIN_3
#define lockWrite_GPIO_Port GPIOA
#define dataRead_Pin GPIO_PIN_4
#define dataRead_GPIO_Port GPIOA
#define dataWrite_Pin GPIO_PIN_5
#define dataWrite_GPIO_Port GPIOA
#define bufAddEn_Pin GPIO_PIN_6
#define bufAddEn_GPIO_Port GPIOA
#define bufNorEn_Pin GPIO_PIN_7
#define bufNorEn_GPIO_Port GPIOA
#define bufOrEn_Pin GPIO_PIN_0
#define bufOrEn_GPIO_Port GPIOB
#define bufXorEn_Pin GPIO_PIN_1
#define bufXorEn_GPIO_Port GPIOB
#define ctrlAin_Pin GPIO_PIN_12
#define ctrlAin_GPIO_Port GPIOB
#define ctrlBin_Pin GPIO_PIN_13
#define ctrlBin_GPIO_Port GPIOB
#define ctrlCin_Pin GPIO_PIN_14
#define ctrlCin_GPIO_Port GPIOB
#define carryIn_Pin GPIO_PIN_15
#define carryIn_GPIO_Port GPIOB
#define invA_Pin GPIO_PIN_11
#define invA_GPIO_Port GPIOA
#define invB_Pin GPIO_PIN_12
#define invB_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
