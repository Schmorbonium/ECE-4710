#ifndef __COM_IF__
#define __COM_IF__
#include "stm32f1xx_hal.h"


#ifdef __cplusplus
extern "C" {
#endif

/// @brief Initializes The computer interface on the given UART connection
/// @param Core Pointer to the HAL Uart Handle
void CompIfInit(UART_HandleTypeDef* Core);

/// @brief This method handles the Uart interrupt for this interface 
void CompIfUartInterruptHAndler();

/// @brief This Method handles all of the computer interface's work that can be completed synchonously.
void CompIfSyncHandler();

#ifdef __cplusplus
}
#endif

#endif /* __COM_IF__ */
