float US_Read(void)
{
    uint32_t time = 0;

    // Send 10us trigger pulse
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while(__HAL_TIM_GET_COUNTER(&htim2) < 10);   // 10µs
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

    // Wait for echo to go HIGH
    while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET);

    // Start timer
    __HAL_TIM_SET_COUNTER(&htim2, 0);

    // Wait for echo to go LOW
    while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET);

    // Read time
    time = __HAL_TIM_GET_COUNTER(&htim2);

    // Convert to distance (cm)
    return (time * 0.0343f) / 2.0f;
}

void IR_Read(void) // should have a pointer as an input and output to that, [v1,v2,v3,v4]
{

}

void IMU_Read() // should have a pointer as an input and output to that, [v1,v2,v3,v4]
{

}

void ENC_Read() // should ??
{

}