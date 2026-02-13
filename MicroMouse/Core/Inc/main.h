/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define ADC_IR3_Pin GPIO_PIN_0
#define ADC_IR3_GPIO_Port GPIOC
#define ADC_IR4_Pin GPIO_PIN_1
#define ADC_IR4_GPIO_Port GPIOC
#define M1ENC_A_Pin GPIO_PIN_0
#define M1ENC_A_GPIO_Port GPIOA
#define M1ENC_B_Pin GPIO_PIN_1
#define M1ENC_B_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define ADC_IR1_Pin GPIO_PIN_4
#define ADC_IR1_GPIO_Port GPIOA
#define IR4_OUT_Pin GPIO_PIN_5
#define IR4_OUT_GPIO_Port GPIOA
#define M2ENC_A_Pin GPIO_PIN_6
#define M2ENC_A_GPIO_Port GPIOA
#define M2ENC_B_Pin GPIO_PIN_7
#define M2ENC_B_GPIO_Port GPIOA
#define M1_SENSE_Pin GPIO_PIN_4
#define M1_SENSE_GPIO_Port GPIOC
#define M2_SENSE_Pin GPIO_PIN_5
#define M2_SENSE_GPIO_Port GPIOC
#define ADC_IR2_Pin GPIO_PIN_0
#define ADC_IR2_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOB
#define IR1_OUT_Pin GPIO_PIN_12
#define IR1_OUT_GPIO_Port GPIOB
#define IR2_OUT_Pin GPIO_PIN_13
#define IR2_OUT_GPIO_Port GPIOB
#define M1PWM_B_Pin GPIO_PIN_14
#define M1PWM_B_GPIO_Port GPIOB
#define M1PWM_A_Pin GPIO_PIN_15
#define M1PWM_A_GPIO_Port GPIOB
#define IR3_OUT_Pin GPIO_PIN_6
#define IR3_OUT_GPIO_Port GPIOC
#define SWITCH1_Pin GPIO_PIN_7
#define SWITCH1_GPIO_Port GPIOC
#define M2PWM_A_Pin GPIO_PIN_8
#define M2PWM_A_GPIO_Port GPIOC
#define M2PWM_B_Pin GPIO_PIN_9
#define M2PWM_B_GPIO_Port GPIOC
#define BT_MODE_Pin GPIO_PIN_8
#define BT_MODE_GPIO_Port GPIOA
#define SWITCH2_Pin GPIO_PIN_9
#define SWITCH2_GPIO_Port GPIOA
#define LED4_Pin GPIO_PIN_10
#define LED4_GPIO_Port GPIOA
#define US_TRIG_Pin GPIO_PIN_12
#define US_TRIG_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define BT_TX_Pin GPIO_PIN_10
#define BT_TX_GPIO_Port GPIOC
#define BT_RX_Pin GPIO_PIN_11
#define BT_RX_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_5
#define LED3_GPIO_Port GPIOB
#define BT_STATE_Pin GPIO_PIN_6
#define BT_STATE_GPIO_Port GPIOB
#define IMU_SCL_Pin GPIO_PIN_8
#define IMU_SCL_GPIO_Port GPIOB
#define IMU_SDA_Pin GPIO_PIN_9
#define IMU_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
