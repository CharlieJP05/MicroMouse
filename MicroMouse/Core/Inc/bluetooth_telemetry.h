/*
 * bluetooth_telemetry.h
 *
 *  Created on: Feb 7, 2026
 *      Author: charlie
 */

#ifndef INC_BLUETOOTH_TELEMETRY_H_
#define INC_BLUETOOTH_TELEMETRY_H_

#include "main.h"

extern uint8_t telemetry_enabled; // 0 = off, 1 = on

void Telemetry_Init(UART_HandleTypeDef *huart);
void Telemetry_Task(void);
void Telemetry_Send(const char *msg);

#endif /* INC_BLUETOOTH_TELEMETRY_H_ */
