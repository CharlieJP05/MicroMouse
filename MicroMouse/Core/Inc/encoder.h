/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : encoder.h
  * @brief          : Header for encoder.c file.
  *                   Generic encoder sensor driver using STM32 timer
  *                   encoder mode. Pin assignment is handled externally
  *                   via GPIO alternate-function configuration, so this
  *                   driver is independent of specific pin numbers.
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

#ifndef __ENCODER_H
#define __ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Exported types ------------------------------------------------------------*/

/**
 * @brief Encoder instance.
 *
 * Wraps a hardware timer configured in encoder mode.  The timer and its
 * associated GPIO pins are configured by the caller before passing the
 * handle to Encoder_Init(), so this driver places no constraints on
 * which physical pins are used.
 */
typedef struct
{
    TIM_HandleTypeDef *htim;   /*!< Pointer to the timer handle used for
                                    quadrature decoding. */
    int32_t           count;   /*!< Accumulated signed tick count. */
    uint16_t          last;    /*!< Raw 16-bit counter value captured on
                                    the previous Encoder_Update() call. */
} Encoder_t;

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief  Initialise an encoder instance.
 *
 * Starts the timer in encoder mode.  The timer peripheral and its GPIO
 * alternate-function pins must already be configured before this
 * function is called.
 *
 * @param  enc   Pointer to the encoder instance to initialise.
 * @param  htim  Pointer to the HAL timer handle (TIM configured in
 *               encoder mode, e.g. TIM2 or TIM3).
 * @retval HAL_OK on success, HAL error code otherwise.
 */
HAL_StatusTypeDef Encoder_Init(Encoder_t *enc, TIM_HandleTypeDef *htim);

/**
 * @brief  Read the current raw counter value from the encoder timer.
 *
 * @param  enc  Pointer to the encoder instance.
 * @retval 16-bit raw counter value (0 – 65535).
 */
uint16_t Encoder_GetRaw(const Encoder_t *enc);

/**
 * @brief  Update the accumulated tick count.
 *
 * Must be called periodically (e.g. in the main loop or a timer ISR)
 * to keep the signed 32-bit @c count accurate across counter wrap-arounds.
 *
 * @param  enc  Pointer to the encoder instance.
 */
void Encoder_Update(Encoder_t *enc);

/**
 * @brief  Return the accumulated signed tick count since last reset.
 *
 * @param  enc  Pointer to the encoder instance.
 * @retval Signed 32-bit tick count.
 */
int32_t Encoder_GetCount(const Encoder_t *enc);

/**
 * @brief  Reset the accumulated tick count to zero.
 *
 * @param  enc  Pointer to the encoder instance.
 */
void Encoder_Reset(Encoder_t *enc);

#ifdef __cplusplus
}
#endif

#endif /* __ENCODER_H */
