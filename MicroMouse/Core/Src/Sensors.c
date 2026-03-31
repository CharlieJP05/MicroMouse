#include "Sensors.h"
#include "main.h"

/* Use the CubeMX-generated TIM5 (`htim5`) as the microsecond timebase.
   TIM5 is configured in the `.ioc` so generated code will provide `htim5`
   and `MX_TIM5_Init()`; here we reference the generated handle.
*/

extern TIM_HandleTypeDef htim5;
/* Local echo pin alias (kept here so IOC-generated headers remain untouched) */
#ifndef US_ECHO_Pin
#define US_ECHO_Pin GPIO_PIN_11
#define US_ECHO_GPIO_Port GPIOA
#endif
// remember: add new funcs to h, any inputs are needed there too.
void Sensors_init(void)
{
    /* start TIM5 timebase provided by generated code */
    HAL_TIM_Base_Start(&htim5);
    __HAL_TIM_SET_COUNTER(&htim5, 0);
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

void IMU_Read(void) // TODO: implement with desired outputs
{
}

void ENC_Read(void) // TODO: implement
{
}
