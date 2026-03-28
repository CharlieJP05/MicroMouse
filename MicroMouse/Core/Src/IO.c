#include "IO.h"
#include "main.h"
#include <string.h>
// remember: add new funcs to h, any inputs are needed there too.
extern UART_HandleTypeDef huart2;

void BUTTONS_Read(void) // TODO: implement
{
}

void VR_Read(void) // TODO: implement
{
}

void LED_Write(void) // TODO: implement
{
}

void Log(const char *msg) // print a message over UART
{
    if (!msg) return;
    HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
}