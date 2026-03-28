// Sensors.h
#ifndef SENSORS_H
#define SENSORS_H

//#include ???

// // Public types and constants
// typedef struct {
//     int32_t value;
// } MyStruct;

// #define MY_CONST 42


float US_Read(void);
void IR_Read(void);
void IMU_Read();
void ENC_Read();


#endif