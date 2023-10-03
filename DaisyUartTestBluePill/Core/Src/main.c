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
#include "ibc.h"
#include "max7219.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define IBCID_PC 0x1
#define IBCID_REG1 0x2
#define IBCID_REG2 0x3
#define ICBID_CLK 0x8

#define IBCATTN_MEM 0x1
#define IBCATTN_CONT 0x2
#define IBCATTN_ALU 0x4
#define IBCATTN_REG 0x8

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void handlePacket(uint8_t id, uint8_t len, uint8_t* data);
uint8_t data[8];
uint8_t dataLen = 0;
uint8_t msgIdx = 0;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void updateData() {
    switch (msgIdx) {
    case 1:
        //send PC to CONT
        // data[0] = 0x23;
        // data[1] = 0x81;
        // data[2] = 0x80;
        // data[3] = 0x00;
        // data[4] = 0x24;
        // data[5] = 0xF0;
        // dataLen = 6;
        data[0] = 0x23;
        data[1] = 0x21;
        data[2] = 0x01;
        dataLen = 3;
        break;
    case 2:
        //send reg1 to regfile
        // data[0] = 0x83;
        // data[1] = 0x82;
        // data[2] = 0x00;
        // data[3] = 0x00;
        // data[4] = 0x33;
        // data[5] = 0x33;
        // dataLen = 6;
        data[0] = 0x83;
        data[1] = 0x21;
        data[2] = 0x01;
        dataLen = 3;
        break;
    case 3:
        //send CLK to all boards
        // data[0] = 0xF3;
        // data[1] = 0x28;
        // data[2] = 0x00;
        // dataLen = 3;
        data[0] = 0xF3;
        data[1] = 0x21;
        data[2] = 0x01;
        dataLen = 3;
        break;
    default:
        //reset - toggle LED
        msgIdx = 0;
        data[0] = 0xF3;
        data[1] = 0x21;
        data[2] = 0x01;
        dataLen = 3;
        break;
    }
}

void initMax() {
    max7219_Init();
    max7219_SetIntensivity(8);
    max7219_TurnOn();
}


void handlePacket(uint8_t id, uint8_t len, uint8_t* data) {
    uint32_t dat;
    switch (len) {
    case 1:
        dat = *data;
        break;
    case 2:
        dat = *((uint16_t*)data);
        break;
        //case 4:
    default:
        dat = *((uint32_t*)data);
        break;
    }
    // switch (id) {
    // case IBCID_PC:
    //     max7219_SendData(8, MAX7219_SYM_8);
    //     max7219_SendData(7, MAX7219_SYM_0);
    //     max7219_SendData(6, MAX7219_SYM_0);
    //     max7219_SendData(5, MAX7219_SYM_0);
    //     max7219_SendData(4, MAX7219_SYM_2);
    //     max7219_SendData(3, MAX7219_SYM_4);
    //     max7219_SendData(2, MAX7219_SYM_F);
    //     max7219_SendData(1, MAX7219_SYM_0);
    //     break;
    // case IBCID_REG1:
    //     max7219_SendData(8, MAX7219_SYM_0);
    //     max7219_SendData(7, MAX7219_SYM_0);
    //     max7219_SendData(6, MAX7219_SYM_0);
    //     max7219_SendData(5, MAX7219_SYM_0);
    //     max7219_SendData(4, MAX7219_SYM_3);
    //     max7219_SendData(3, MAX7219_SYM_3);
    //     max7219_SendData(2, MAX7219_SYM_3);
    //     max7219_SendData(1, MAX7219_SYM_3);
    //     break;
    // case ICBID_CLK:
    //     max7219_SendData(8, MAX7219_SYM_C);
    //     max7219_SendData(7, MAX7219_SYM_L);
    //     max7219_SendData(6, MAX7219_SYM_O);
    //     max7219_SendData(5, MAX7219_SYM_C);
    //     max7219_SendData(4, MAX7219_SYM_DOT);
    //     max7219_SendData(3, MAX7219_SYM_DOT);
    //     max7219_SendData(2, MAX7219_SYM_DOT);
    //     max7219_SendData(1, MAX7219_SYM_DOT);
    //     break;
    // }
    switch (dat) {
    case 1:
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        HAL_GPIO_TogglePin(GLED_GPIO_Port, GLED_Pin);
        break;
    case 2:
        HAL_GPIO_TogglePin(GLED_GPIO_Port, GLED_Pin);
        break;
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    initIbc(&huart1, &handlePacket, 0x1);
    uint32_t lastTick = HAL_GetTick();
    while (1) {
        processIbcInbox();

        if (HAL_GetTick() - lastTick >= 1000) {
            msgIdx++;
            updateData();
            HAL_UART_Transmit_IT(&huart1, data, dataLen);
            // max7219_SendData(1, MAX7219_SYM_1);
            lastTick = HAL_GetTick();
        }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

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
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GLED_GPIO_Port, GLED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
void Error_Handler(void)
{
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
                /* User can add his own implementation to report the file name and line number,
                   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
