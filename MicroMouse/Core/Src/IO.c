#include "IO.h"
#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
// remember: add new funcs to h, any inputs are needed there too.
extern UART_HandleTypeDef huart2;

void IO_init(void)
{

}

void BUTTONS_Read(void)
{

}

void VR_Read(void) // variable resitors
{

}

void LED_Write(void)
{

}

void Log(const char *msg) // print a message over UART
{
    if (!msg) return;
    HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
}
void LogPos(float x, float y)
{
	const int scale = 100;   // 2 decimal places
	int32_t xs = (int32_t)roundf(x * scale);
	int32_t ys = (int32_t)roundf(y * scale);

	long xi = (long)(xs / scale);
	int xf = abs(xs % scale);
	long yi = (long)(ys / scale);
	int yf = abs(ys % scale);

	char buffer[64];
	snprintf(buffer, sizeof(buffer), "%ld.%02d,%ld.%02d\r\n", xi, xf, yi, yf);
	Log(buffer);
}
