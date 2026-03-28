// IO.h
#ifndef IO_H
#define IO_H

//#include ???

// // Public types and constants
// typedef struct {
//     int32_t value;
// } MyStruct;

// #define MY_CONST 42


void BUTTONS_Read(void);
void VR_Read(void);
void LED_Write(void);
void Log(const char *msg);


#endif