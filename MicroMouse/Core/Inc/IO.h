#ifndef IO_H
#define IO_H

#include <stdint.h>

void IO_init(void);
void BUTTONS_Read(void);
void VR_Read(void);
void LED_Write(void);
void Log(const char *msg);
void LogPos(float x, float y);

#endif // IO_H