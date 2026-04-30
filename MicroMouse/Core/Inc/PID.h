/*
 * PID.h
 *
 *  Created on: Apr 29, 2026
 *      Author: jacob
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include "main.h"

typedef struct
{
    float p;
    float i;
    float d;
    float target;
    //float current;
    float integral;
    float derivative ;
    float last_time ;
}PID_Values;

typedef struct
{
	float dt;
	float now;
}DT_out;


void create_PID(float Kp, float Ki, float Kd, float target,PID_Values* PIDValues);
int PID(float current, PID_Values values);
DT_out get_dt(float last_time);
void TIM12Move(int amount);
void update();
#endif /* INC_PID_H_ */
