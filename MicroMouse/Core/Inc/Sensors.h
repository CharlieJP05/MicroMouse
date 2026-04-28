#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

void Sensors_init(void);
float US_Read(void);
void IR_Read(void);

void IMU_initialise(void);
void IMU_Read(uint8_t *i2c_buffer_pointer);
extern float acceleration[3];   // milli-g
extern float angular_vel[3];    // degrees per second
extern float angle[3];          // integrated degrees
extern float temperature;       // degrees C
extern volatile uint8_t i2c_sample_complete;

void ENC_Read(void);

extern float velocityR;
extern float velocityL;
extern int32_t positionR;
extern int32_t positionL;
extern int32_t rollover_counterR;
extern int32_t rollover_counterL;

#endif // SENSORS_H
