#include "Uart1.h"

#include "stm32f1xx_hal.h"

volatile uint8_t rxITBuf;
volatile uint8_t rxBuf[64];
volatile uint8_t rxIn = 0;
volatile uint8_t rxOut = 0;


extern UART_HandleTypeDef huart1;


//
//
//
int _write(int fd, char *str, int len)
{
	for(int i=0;i<len;i++)
	{
		//__io_putchar((*str++));
		HAL_UART_Transmit(&huart1, (uint8_t *)&str[i], 1, 0xFFFF);
	}
	return len;
}

//
//
//
void Uart1_Start()
{
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&rxITBuf, 1);
}
