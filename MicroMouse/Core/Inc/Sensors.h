#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

float US_Read(void);
void IR_Read(void);
void IMU_Read(void);
void ENC_Read(void);

#endif // SENSORS_H