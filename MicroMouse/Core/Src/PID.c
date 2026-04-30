/*
 * PID.c
 *
 *  Created on: Apr 29, 2026
 *      Author: jacob
 */

typedef struct
{
    float p;
    float i;
    float d;
    float target;
    //float current;
    float integral = 0;
    float derivative = 0;
    float last_time = 0;
}PID_Values;

typedef struct
{
	float dt;
	float now;
}DT_out;


void PID_init()
{
	turningpid = creat(target)
}

void update()
{
	wh = PID(current,vlaues)
	MOVE
	PID()
}

void move(float amount)
{

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

void create_PID(float Kp, float Ki, float Kd, float target)
{
	PID_Values values;
	values.p = Kp;
	values.i = Ki;
	values.d = Kd;
	values.target = target;
}
float PID(float current, PID_Values values)
{
	DT_out dto = get_dt(values);
	float dt = dto.dt;
	values.last_time = dto.now;
    float error = target - current;

    static float integral = 0;

    integral += errorL * dt;

    static float prev_error = 0;

    float derivative = (error - prev_error) / dt;

    prev_error = error;

    control = Kp * error + Ki * integral + Kd * derivative;
    return control;
}
