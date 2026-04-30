/*
 * PID.c
 *
 *  Created on: Apr 29, 2026
 *      Author: jacob.h
 */

#include "PID.h"
#include "main.h"
float theta; //temp

static PID_Values turningPID;
void PID_init()
{
	
	  create_PID(1,0,0,100,&turningPID);
}

void update()
{
	int wh = PID(theta,turningPID);
	TIM12Move(wh);

}

void TIM12Move(int amount)
{

	if(amount > 0 ){
		TIM12->CCR1 = abs(amount);
	}
	if(amount < 0 ){
		TIM12->CCR2 = abs(amount);
	}


}
void TIM8Move(float amount)
{

	if(amount > 0 ){
		TIM8->CCR3 = abs(amount);
	}
	if(amount < 0 ){
		TIM8->CCR4 = abs(amount);
	}


}

void turn(float amount)
{

}


DT_out get_dt(float last_time)
{
	uint32_t now = 0;

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
int PID(float current, PID_Values values)
{
	DT_out dto = get_dt(values.last_time);
	float dt = dto.dt;
	values.last_time = dto.now;
    float error = values.target - current;

    static float integral = 0;
    static float prev_error = 0;

    float derivative = (error - prev_error) / dt;

    prev_error = error;

    int control = values.p * error + values.i * integral + values.d * derivative;
    return control;
}
