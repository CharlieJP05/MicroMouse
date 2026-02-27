/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : encoder.c
  * @brief          : Generic encoder sensor driver.
  *
  * Provides initialisation, reading, and tick-accumulation for quadrature
  * encoders wired to STM32 timers in encoder mode.  Because pin selection
  * is handled entirely through the GPIO alternate-function configuration
  * supplied by the caller, this module imposes no constraint on which
  * physical pins are used.
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

/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

/* Private defines -----------------------------------------------------------*/

/** Full 16-bit counter period used for wrap-around arithmetic. */
#define ENCODER_COUNTER_MAX  0xFFFFU

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Initialise an encoder instance and start timer encoder mode.
 */
HAL_StatusTypeDef Encoder_Init(Encoder_t *enc, TIM_HandleTypeDef *htim)
{
    HAL_StatusTypeDef status;

    enc->htim  = htim;
    enc->count = 0;

    /* Start the timer's encoder interface on both channels. */
    status = HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
    if (status == HAL_OK)
    {
        /* Capture the initial counter value so the first Encoder_Update()
         * call computes a delta of zero. */
        enc->last = (uint16_t)__HAL_TIM_GET_COUNTER(htim);
    }

    return status;
}

/**
 * @brief  Read the current raw 16-bit counter value.
 */
uint16_t Encoder_GetRaw(const Encoder_t *enc)
{
    return (uint16_t)__HAL_TIM_GET_COUNTER(enc->htim);
}

/**
 * @brief  Update the accumulated signed tick count.
 *
 * Handles counter wrap-around by interpreting the 16-bit delta as a
 * signed value: deltas larger than half the counter range are treated
 * as negative (backward) motion.
 */
void Encoder_Update(Encoder_t *enc)
{
    uint16_t current = (uint16_t)__HAL_TIM_GET_COUNTER(enc->htim);
    int16_t  delta   = (int16_t)(current - (uint16_t)enc->last);

    enc->count += (int32_t)delta;
    enc->last   = current;
}

/**
 * @brief  Return the accumulated signed tick count.
 */
int32_t Encoder_GetCount(const Encoder_t *enc)
{
    return enc->count;
}

/**
 * @brief  Reset the accumulated tick count to zero.
 *
 * Also resets the hardware counter and the internal snapshot so that
 * the next Encoder_Update() call starts from a clean baseline.
 */
void Encoder_Reset(Encoder_t *enc)
{
    __HAL_TIM_SET_COUNTER(enc->htim, 0U);
    enc->last  = 0U;
    enc->count = 0;
}
