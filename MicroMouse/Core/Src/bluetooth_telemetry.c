/*
 * bluetooth_telemetry.c
 *
 *  Created on: Feb 7, 2026
 *      Author: charlie
 */

#include "bluetooth_telemetry.h"
#include <string.h>

uint8_t telemetry_enabled = 1;
static UART_HandleTypeDef *hbt_uart;

void Telemetry_Init(UART_HandleTypeDef *huart)
{
    hbt_uart = huart;
    if (telemetry_enabled)
    {
        // Optional: start UART RX interrupt if needed
        uint8_t dummy;
        HAL_UART_Receive_IT(hbt_uart, &dummy, 1);
    }
}

void Telemetry_Task(void)
{
    if (!telemetry_enabled) return;

    const char *msg = "Robot running\n";
    HAL_UART_Transmit(hbt_uart, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

void Telemetry_Send(const char *msg)
{
    if (!telemetry_enabled) return;

    HAL_UART_Transmit(hbt_uart, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}
