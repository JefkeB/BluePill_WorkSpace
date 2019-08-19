#include "BluePill.h"

#include "stm32f1xx_hal.h"


//
//
//
void BluePill_LedInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOC_CLK_ENABLE();

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);


	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}


//
//
//
void BluePill_LedToggle()
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
