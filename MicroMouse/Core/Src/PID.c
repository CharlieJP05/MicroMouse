/*
 * PID.c
 *
 *  Created on: Apr 29, 2026
 *      Author: jacob.h
 */

#include "PID.h"
#include "main.h"
extern TIM_HandleTypeDef htim5;
static PID_Values movePID;
static PID_Values turnPID;
void PID_init()
{
	
	  create_PID(1,0.001,0.001,1000,&movePID);
	  create_PID(1,0,0,3,&turnPID);
}

void update(int positionR, int positionL, float theta)
{
	float wh = PID(positionR,&movePID);
	float wh2 = PID(positionL,&movePID);
	TIM12Move(wh);
	TIM8Move(wh2);


//	float tCON = PID(theta,&turnPID);
//	TIM12Move(tCON);
//	TIM8Move(-tCON);

}

void TIM12Move(float amount)
{

	if(amount < 0 ){
		TIM12->CCR1 = abs((int)amount);
		TIM12->CCR2 = 0;
	}
	if(amount > 0 ){
		TIM12->CCR2 = abs((int)amount);
		TIM12->CCR1 = 0;
	}


}
void TIM8Move(float amount)
{

	if(amount > 0 ){
		TIM8->CCR3 = abs((int)amount);
		TIM8->CCR4 = 0;
	}
	if(amount < 0 ){
		TIM8->CCR4 = abs((int)amount);
		TIM8->CCR3 = 0;
	}


}

void turn(float amount)
{

}


DT_out get_dt(float last_time)
{
	uint32_t now = __HAL_TIM_GET_COUNTER(&htim5);

	uint32_t delta_us = (now >= last_time)
						? (now - last_time)
						: (0xFFFFFFFF - last_time + now); // handle overflow

	last_time = now;

	float dt = delta_us / 1000000.0f; // convert to seconds
	DT_out dto;
	dto.dt = dt;
	dto.now = now;
	return dto;
}

void create_PID(float Kp, float Ki, float Kd, float target,PID_Values*PIDValues)
{

	PIDValues ->p = Kp;
	PIDValues ->i = Ki;
	PIDValues ->d = Kd;
	PIDValues ->target = target;
}
float PID(float current, PID_Values *values)
{
	DT_out dto = get_dt(values->last_time);
	float dt = dto.dt;
	values -> last_time = dto.now;
    float error = values->target - current;

    float integral = error + values->integral;
    values -> integral = integral;

    float derivative = (error - values->last_error) / dt;
    values->last_error = error;

    float control = values->p * error + values->i * integral + values->d * derivative;
    return control;
    //:---
}
