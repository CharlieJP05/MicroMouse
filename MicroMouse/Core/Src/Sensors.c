#include "Sensors.h"
#include "main.h"

extern TIM_HandleTypeDef htim2;
// remember: add new funcs to h, any inputs are needed there too.
void Sensors_init(void)
{
    HAL_TIM_Base_Start(&htim2); // timer for US sensor
    __HAL_TIM_SET_COUNTER(&htim2, 0);
}

float US_Read(void)
{
    uint32_t pulse = 0;
    const uint32_t timeout_us = 30000;   // ~30 ms at 1 MHz timer
    const float sound_cm_per_us = 0.0343f;

    // Ensure echo is low before triggering
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (HAL_GPIO_ReadPin(US_ECHO_GPIO_Port, US_ECHO_Pin) == GPIO_PIN_SET) {
        if (__HAL_TIM_GET_COUNTER(&htim2) >= timeout_us) return -1.0f;
    }

    // Send 10us trigger pulse
    HAL_GPIO_WritePin(US_TRIG_GPIO_Port, US_TRIG_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (__HAL_TIM_GET_COUNTER(&htim2) < 10) {}
    HAL_GPIO_WritePin(US_TRIG_GPIO_Port, US_TRIG_Pin, GPIO_PIN_RESET);

    // Wait for rising edge on echo
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (HAL_GPIO_ReadPin(US_ECHO_GPIO_Port, US_ECHO_Pin) == GPIO_PIN_RESET) {
        if (__HAL_TIM_GET_COUNTER(&htim2) >= timeout_us) return -1.0f;
    }

    // Measure pulse width while echo is high
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (HAL_GPIO_ReadPin(US_ECHO_GPIO_Port, US_ECHO_Pin) == GPIO_PIN_SET) {
        if (__HAL_TIM_GET_COUNTER(&htim2) >= timeout_us) return -1.0f;
    }
    pulse = __HAL_TIM_GET_COUNTER(&htim2);

    return (pulse * sound_cm_per_us) * 0.5f; // distance in cm
}

void IR_Read(void)  // TODO: implement with desired outputs
{
}

void IMU_Read(void) // TODO: implement with desired outputs
{
}

void ENC_Read(void) // TODO: implement
{
}