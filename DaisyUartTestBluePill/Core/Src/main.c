/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
  /* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
typedef uint16_t IbcRawHeader;

typedef struct {
    uint8_t attn;
    uint8_t ttl;
    uint8_t len;
    uint8_t id;
    uint8_t data[];
} IbcPacket;

#define IBCP_ATTN_IDX 4
#define IBCP_TTL_IDX 0
#define IBCP_LEN_IDX 13
#define IBCP_ID_IDX 8
#define IBCP_ATTN(packet) ((*packet & 0x00F0) >> IBCP_ATTN_IDX)
#define IBCP_ATTN_THIS_DEVICE(packet) ((IBCP_ATTN(packet) >> THIS_DEV_ATTN_ID) & 0x1)
#define IBCP_TTL(packet) ((*packet & 0x0003) >> IBCP_TTL_IDX)
#define IBCP_LEN(packet) ((*packet & 0xE000) >> IBCP_LEN_IDX)
#define IBCP_ID(packet) ((*packet & 0x1F00) >> IBCP_ID_IDX)

#define IBCP_PKT(attn, ttl, len, id) (((attn & 0xF) << IBCP_ATTN_IDX) | ((ttl & 0x3) << IBCP_TTL_IDX) | ((len & 0x7) << IBCP_LEN_IDX) | ((id & 0x1F) << IBCP_ID_IDX))

//attn idx: 0-3
#define THIS_DEV_ATTN_ID 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t incoming_byte[2];
uint8_t longbuf[100];
uint32_t count = 0;

IbcPacket* checkForPacket(uint8_t* buffer, uint32_t buf_len) {
    if (buf_len < 3 || buf_len - 2 < IBCP_LEN((uint16_t*) buffer)) // -2 to account for header
        return NULL;

    IbcRawHeader* hp = (IbcRawHeader*)buffer;
    IbcPacket* newPacket = (IbcPacket*)malloc(sizeof(IbcPacket) + IBCP_LEN(hp));
    newPacket->attn = IBCP_ATTN(hp);
    newPacket->ttl = IBCP_TTL(hp);
    newPacket->len = IBCP_LEN(hp);
    newPacket->id = IBCP_ID(hp);
    switch (newPacket->len) {
    case 1:
        newPacket->data[0] = buffer[2];
        break;
    case 2:
        newPacket->data[0] = buffer[3];
        newPacket->data[1] = buffer[2];
        break;
    case 3:
        newPacket->data[0] = buffer[4];
        newPacket->data[1] = buffer[3];
        newPacket->data[2] = buffer[2];
        break;
    case 4:
        newPacket->data[0] = buffer[5];
        newPacket->data[1] = buffer[4];
        newPacket->data[2] = buffer[3];
        newPacket->data[3] = buffer[2];
        break;
    }

    return newPacket;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart) {
    // HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    // HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    longbuf[count++] = *incoming_byte;
    IbcPacket* pkt = checkForPacket(longbuf, count);
    if (pkt != NULL) {

        if ((pkt->attn >> THIS_DEV_ATTN_ID) & 0x1) {
            // HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
            // if (pkt->data == 1) {
            //     HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
            // }
            // else if (pkt->data == 2) {
            //     HAL_GPIO_TogglePin(GLED_GPIO_Port, GLED_Pin);
            // }
            uint32_t data;
            switch (pkt->len) {
            case 1:
                data = *((uint8_t*)pkt->data);
                break;
            case 2:
                data = *((uint16_t*)pkt->data);
                break;
            case 4:
                data = *((uint32_t*)pkt->data);
                break;
            }

            switch (data) {
            case 1:
                HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
                break;
            case 2:
                HAL_GPIO_TogglePin(GLED_GPIO_Port, GLED_Pin);
                break;
            }
        }

        // if packet has hops left, forward it
        if (pkt->ttl > 1) {
            *longbuf -= (1 << IBCP_TTL_IDX);
            if (HAL_UART_GetState(&huart1) == HAL_UART_STATE_READY && HAL_UART_Transmit_IT(&huart1, longbuf, count) != HAL_OK) {
                // HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
            }
        }

        // reset index into buffer
        count = 0;
    }
    HAL_UART_Receive_IT(&huart1, incoming_byte, 1);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */
    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    /* USER CODE BEGIN 2 */
      // HAL_UART_RegisterCallback(&huart1, HAL_UART_TX_COMPLETE_CB_ID, &HAL_UART_TxCpltCallback);
      // NVIC_EnableIRQ(USART1_IRQn);
      // HAL_UART_RegisterCallback(&huart1, HAL_UART_RX_COMPLETE_CB_ID, &HAL_UART_RxCpltCallback);


    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    HAL_UART_Receive_IT(&huart1, &incoming_byte, 1);
    // uint32_t lastTick = HAL_GetTick();
    while (1) {
        // char* data = "Hello World\n";
        // if (HAL_GetTick() - lastTick >= 1000) {
        //     HAL_UART_Transmit_IT(&huart1, data, 12);
        //     HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        //     lastTick = HAL_GetTick();
        // }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void) {

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */

    /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GLED_GPIO_Port, GLED_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : LED_Pin */
    GPIO_InitStruct.Pin = LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : GLED_Pin */
    GPIO_InitStruct.Pin = GLED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GLED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
              /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line) {
    /* USER CODE BEGIN 6 */
              /* User can add his own implementation to report the file name and line number,
                 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
                 /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
