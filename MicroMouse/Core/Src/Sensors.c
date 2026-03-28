#include "Sensors.h"
#include "main.h"

extern TIM_HandleTypeDef htim2;
// remember: add new funcs to h, any inputs are needed there too.
float US_Read(void)
{
    uint32_t time = 0;
    const uint32_t timeout_us = 30000; // ~30 ms at 1 MHz timer

    // Send 10us trigger pulse
    HAL_GPIO_WritePin(US_TRIG_GPIO_Port, US_TRIG_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (__HAL_TIM_GET_COUNTER(&htim2) < 10) {}
    HAL_GPIO_WritePin(US_TRIG_GPIO_Port, US_TRIG_Pin, GPIO_PIN_RESET);

    // Wait for echo HIGH (no named pin defined; uses PA11 in current design)
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET) {
        if (__HAL_TIM_GET_COUNTER(&htim2) > timeout_us) return -1.0f;
    }

    // Measure HIGH pulse width
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET) {
        if (__HAL_TIM_GET_COUNTER(&htim2) > timeout_us) return -1.0f;
    }
    time = __HAL_TIM_GET_COUNTER(&htim2);

    return (time * 0.0343f) / 2.0f; // distance in cm
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