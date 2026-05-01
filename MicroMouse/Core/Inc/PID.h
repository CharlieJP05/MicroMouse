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
    float last_error ;
    float last_time ;
}PID_Values;

typedef struct
{
	float dt;
	float now;
}DT_out;


void create_PID(float Kp, float Ki, float Kd, float target,PID_Values* PIDValues);
float PID(float current, PID_Values* values);
DT_out get_dt(float last_time);
void TIM12Move(float amount);
void TIM8Move(float amount);
int update(int positionR, int PositionL, float theta,vector target,int turnAngle);
void SetTarget(int target);
int turn(int angle);
#endif /* INC_PID_H_ */
