#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

void Sensors_init(void);
float US_Read(void);
void IR_Read(void);
void IMU_Read(void);
void ENC_Read(void);

#endif // SENSORS_H