/*
 * PID.c
 *
 *  Created on: Apr 29, 2026
 *      Author: jacob
 */
void PID(void)
{
		//PID controller (only encoders so far)
		//starting with simple P
		float dt = 0.02f; // time between each time step is 20ms

		 // target is not defined as of now as it should come from movement commands
		float targetL = 100;
		float targetR = 100;
		float errorL = targetL - velocityL;
	 	float errorR = targetR - velocityR;

		static float integralL = 0;
		static float integralR = 0;
		 // adding I
		float Ki = 0.1f;

		integralL += errorL * 0.02f;
		integralR += errorR * 0.02f;
		 // clamp integral to prevent windup
		if (integralL >  1000.0f) integralL =  1000.0f;
		if (integralL < -1000.0f) integralL = -1000.0f;
		if (integralR >  1000.0f) integralR =  1000.0f;
		if (integralR < -1000.0f) integralR = -1000.0f;
		 // adding D
		float Kd = 0.01f;

		static float prev_errorL = 0;

		float derivativeL = (errorL - prev_errorL) / dt;
		prev_errorL = errorL;
		static float prev_errorR = 0;
		float derivativeR = (errorR - prev_errorR) / dt;
		prev_errorR = errorR;
		 // final values
		controlL = Kp * errorL + Ki * integralL + Kd * derivativeL;
		controlR = Kp * errorR + Ki * integralR + Kd * derivativeR;
}
