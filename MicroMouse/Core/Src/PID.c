/*
 * PID.c
 *
 *  Created on: Apr 29, 2026
 *      Author: jacob h
 */

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

float theta; //temp

PID_Values TuringPID;
void PID_init()
{
	
	 TuringPID = create_PID(10,10,10,10);
}

void update()
{
	float wh = PID(theta,TuringPID);
	move(wh);

}

void TIM12Move(float amount)
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

PID_Values create_PID(float Kp, float Ki, float Kd, float target)
{
	PID_Values values;
	values.p = Kp;
	values.i = Ki;
	values.d = Kd;
	values.target = target;
}
float PID(float current, PID_Values values)
{
	DT_out dto = get_dt(values.last_time);
	float dt = dto.dt;
	values.last_time = dto.now;
    float error = values.target - current;

    static float integral = 0;
    static float prev_error = 0;

    float derivative = (error - prev_error) / dt;

    prev_error = error;

    float control = values.p * error + values.i * integral + values.d * derivative;
    return control;
}
