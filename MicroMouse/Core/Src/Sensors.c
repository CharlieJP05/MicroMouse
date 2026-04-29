#include "Sensors.h"
#include "main.h"
#include <string.h>
/* Use the CubeMX-generated TIM5 (`htim5`) as the microsecond timebase.
   TIM5 is configured in the `.ioc` so generated code will provide `htim5`
   and `MX_TIM5_Init()`; here we reference the generated handle.
*/

extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef  htim4;
extern I2C_HandleTypeDef  hi2c1;
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
/* Local echo pin alias (kept here so IOC-generated headers remain untouched) */
#ifndef US_ECHO_Pin
#define US_ECHO_Pin GPIO_PIN_11
#define US_ECHO_GPIO_Port GPIOA
#endif

// IMU registers
#define SIZE_I2C_BUFFER   14
#define SIZE_UART_TX_BUFFER 100
static const uint8_t OUT_TEMP_L     = 0x20;
static const uint8_t LSM6DSO_ADDRESS = 0x6A << 1;
static const uint8_t CTRL1_XL       = 0x10;
static const uint8_t CTRL2_G        = 0x11;

//IMU buffers & results variables
static uint8_t i2c_buffer[SIZE_I2C_BUFFER];
static uint8_t uart_tx_buffer[SIZE_UART_TX_BUFFER];

float acceleration[3];
float angular_vel[3];
float angle[3]          = {0.0f, 0.0f, 0.0f};
float temperature;
volatile uint8_t i2c_sample_complete = 0;
//Encoder variables
float    velocityR = 0.0f;
float    velocityL = 0.0f;
int32_t  positionR = 0;
int32_t  positionL = 0;
int32_t  rollover_counterR = 0;
int32_t  rollover_counterL = 0;
// PID variables
float controlL = 0.0f;
float controlR = 0.0f;
static uint8_t pid_enabled = 0;
static uint8_t startup_count = 0;
static int32_t lastCNT_R = 0;
static int32_t lastCNT_L = 0;
// remember: add new funcs to h, any inputs are needed there too.
void Sensors_init(void)
{
    /* start TIM5 timebase provided by generated code */
    HAL_TIM_Base_Start(&htim5);
    __HAL_TIM_SET_COUNTER(&htim5, 0);
    // IMU
    IMU_initialise();   // IMU setup now lives here too
}

float US_Read(void)
{
    const uint32_t timeout_us = 30000; // ~30 ms timeout
    const float sound_cm_per_us = 0.0343f;
    const uint32_t min_pulse_us = 100; // ~2 cm; anything shorter is noise
    uint32_t pulse = 0;

    // Make sure echo is low before triggering
    __HAL_TIM_SET_COUNTER(&htim5, 0);
    while (HAL_GPIO_ReadPin(US_ECHO_GPIO_Port, US_ECHO_Pin) == GPIO_PIN_SET) {
        if (__HAL_TIM_GET_COUNTER(&htim5) >= timeout_us) return -1.0f;
    }

    // Send 10us trigger pulse
    HAL_GPIO_WritePin(US_TRIG_GPIO_Port, US_TRIG_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COUNTER(&htim5, 0);
    while (__HAL_TIM_GET_COUNTER(&htim5) < 10) {} // 10 us high
    HAL_GPIO_WritePin(US_TRIG_GPIO_Port, US_TRIG_Pin, GPIO_PIN_RESET);

    // Wait for rising edge on echo
    __HAL_TIM_SET_COUNTER(&htim5, 0);
    while (HAL_GPIO_ReadPin(US_ECHO_GPIO_Port, US_ECHO_Pin) == GPIO_PIN_RESET) {
        if (__HAL_TIM_GET_COUNTER(&htim5) >= timeout_us) return -1.0f;
    }

    // Measure echo high pulse
    __HAL_TIM_SET_COUNTER(&htim5, 0);
    while (HAL_GPIO_ReadPin(US_ECHO_GPIO_Port, US_ECHO_Pin) == GPIO_PIN_SET) {
        if (__HAL_TIM_GET_COUNTER(&htim5) >= timeout_us) return -1.0f;
    }
    pulse = __HAL_TIM_GET_COUNTER(&htim5);

    if (pulse < min_pulse_us) return -1.0f; // reject spurious short blips

    return (pulse * sound_cm_per_us) * 0.5f; // distance in cm
}

void IR_Read(void)  // TODO: implement with desired outputs
{
}
// IMU
void IMU_initialise(void)
{
    i2c_buffer[0] = 0b10000000;

    if (HAL_I2C_Mem_Write(&hi2c1, LSM6DSO_ADDRESS, CTRL1_XL, 1,
                           i2c_buffer, 1, HAL_MAX_DELAY) != HAL_OK)
        strcpy((char*)uart_tx_buffer, "Error Tx \n");
    else
        strcpy((char*)uart_tx_buffer, "Acc sample rate set! \n");
    HAL_UART_Transmit(&huart2, uart_tx_buffer,
                      strlen((char*)uart_tx_buffer), HAL_MAX_DELAY);

    if (HAL_I2C_Mem_Write(&hi2c1, LSM6DSO_ADDRESS, CTRL2_G, 1,
                           i2c_buffer, 1, HAL_MAX_DELAY) != HAL_OK)
        strcpy((char*)uart_tx_buffer, "Error Tx \n");
    else
        strcpy((char*)uart_tx_buffer, "Gyro sample rate set! \n");
    HAL_UART_Transmit(&huart2, uart_tx_buffer,
                      strlen((char*)uart_tx_buffer), HAL_MAX_DELAY);

    HAL_TIM_Base_Start_IT(&htim4);  // start 20ms sampling timer
}

void IMU_Read(uint8_t *i2c_buffer_pointer)
{
    while (i2c_sample_complete == 0) {}
    i2c_sample_complete = 0;

    int16_t temp;

    temp = ((int16_t)i2c_buffer_pointer[1] << 8) | i2c_buffer_pointer[0];
    temperature = ((float)temp) / 256.0f + 25.0f;

    temp = ((int16_t)i2c_buffer_pointer[3] << 8) | i2c_buffer_pointer[2];
    angular_vel[0] = (float)temp * 0.00875f;

    temp = ((int16_t)i2c_buffer_pointer[5] << 8) | i2c_buffer_pointer[4];
    angular_vel[1] = (float)temp * 0.00875f;

    temp = ((int16_t)i2c_buffer_pointer[7] << 8) | i2c_buffer_pointer[6];
    angular_vel[2] = (float)temp * 0.00875f;

    temp = ((int16_t)i2c_buffer_pointer[9]  << 8) | i2c_buffer_pointer[8];
    acceleration[0] = (float)temp * 0.061f;

    temp = ((int16_t)i2c_buffer_pointer[11] << 8) | i2c_buffer_pointer[10];
    acceleration[1] = (float)temp * 0.061f;

    temp = ((int16_t)i2c_buffer_pointer[13] << 8) | i2c_buffer_pointer[12];
    acceleration[2] = (float)temp * 0.061f;

    angle[0] += angular_vel[0] * 0.02f;
    angle[1] += angular_vel[1] * 0.02f;
    angle[2] += angular_vel[2] * 0.02f;
}

void ENC_Read(void) // TODO: implement
{
}
// ═══════════════════════════════════════════════════════════
//  HAL callbacks  (only one definition allowed per project)
// ═══════════════════════════════════════════════════════════
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	{

		static int32_t preposR;
		static int32_t preposL;

		if(htim == &htim6)
		{
			 positionR = htim2.Instance->CNT; // copy CNT into global variable
			 // finds full amount of rotational ticks
			 positionR = -(positionR + (rollover_counterR * 48));

			 velocityR = (positionR - preposR) * 20; //calculates angular velocity
			 preposR = positionR;	//stores current position in variable

			 positionL = htim3.Instance->CNT; // copy CNT into global variable
			 // finds full amount of rotational ticks
			 positionL = positionL + (rollover_counterL * 48);

			 velocityL = (positionL - preposL) * 20; //calculates angular velocity
			 preposL = positionL;	//stores current position in variable

		}

		if(htim == &htim2)
		{
			if(htim2.Instance->CNT < 24) // if CNT is less than half of ARR (48)
			{
				rollover_counterR +=1;	// increment counter
			}
			if(htim2.Instance->CNT > 24) // if CNT is more than half of ARR (48)
			{
				rollover_counterR -=1;	// decrement counter
			}
			positionR = -(htim2.Instance->CNT + (rollover_counterR * 48));	// absolute position calculated
		}
		if(htim == &htim3)
		{
			if(htim3.Instance->CNT < 24) // if CNT is less than half of ARR (48)
			{
				rollover_counterL +=1;	// increment counter
			}
			if(htim3.Instance->CNT > 24) // if CNT is more than half of ARR (48)
			{
				rollover_counterL -=1;	// decrement counter
			}
			positionL = htim3.Instance->CNT + (rollover_counterL * 48);	// absolute position calculated
		}
	}


void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    i2c_sample_complete = 1;
}






//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	static int32_t preposR;
//	static int32_t preposL;
//	float Kp = 1.0f;
//
//    if (htim == &htim4)
//        HAL_I2C_Mem_Read_DMA(&hi2c1, LSM6DSO_ADDRESS, OUT_TEMP_L,
//                              I2C_MEMADD_SIZE_8BIT, i2c_buffer, SIZE_I2C_BUFFER);
//
//	if(0)//htim == &htim6)
//	{
//		 positionR = htim2.Instance->CNT; // copy CNT into global variable
//		 // finds full amount of rotational ticks
//		 positionR = -(positionR + (rollover_counterR * 48));
//
//		 velocityR = (positionR - preposR) * 20; //calculates angular velocity
//		 preposR = positionR;	//stores current position in variable
//
//		 positionL = htim3.Instance->CNT; // copy CNT into global variable
//		 // finds full amount of rotational ticks
//		 positionL = positionL + (rollover_counterL * 48);
//
//		 velocityL = (positionL - preposL) * 20; //calculates angular velocity
//		 preposL = positionL;	//stores current position in variable
//
//		 // PID controller (only encoders so far)
//		 // starting with simple P
//		 float dt = 0.02f; // time between each time step is 20ms
//
//		 // target is not defined as of now as it should come from movement commands
//		 float targetL = 1000;
//		 float targetR = 1000;
//		 float errorL = targetL - velocityL;
//		 float errorR = targetR - velocityR;
//
//		 static float integralL = 0;
//		 static float integralR = 0;
//		 // adding I
//		 float Ki = 0.1f;
//
//		 integralL += errorL * 0.02f;
//		 integralR += errorR * 0.02f;
//		 // clamp integral to prevent windup
//		 if (integralL >  100.0f) integralL =  100.0f;
//		 if (integralL < -100.0f) integralL = -100.0f;
//		 if (integralR >  100.0f) integralR =  100.0f;
//		 if (integralR < -100.0f) integralR = -100.0f;
//		 // adding D
//		 float Kd = 0.01f;
//
//		 static float prev_errorL = 0;
//		 float derivativeL = (errorL - prev_errorL) / dt;
//		 prev_errorL = errorL;
//		 static float prev_errorR = 0;
//		 float derivativeR = (errorR - prev_errorR) / dt;
//		 prev_errorR = errorR;
//		 // final values
//		 controlL = Kp * errorL + Ki * integralL + Kd * derivativeL;
//		 controlR = Kp * errorR + Ki * integralR + Kd * derivativeR;
//
//	}
