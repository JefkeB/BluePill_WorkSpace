/*
 * touch.c
 *
 *  Created on: 2018. 12. 7.
 *      Author: chand
 */
#include "stm32f1xx_hal.h"
#include "touch.h"
#include "i2c.h"
#include "usb_device.h"
#include "usbd_hid_ptp.h"

#define max_point_num 5

#define FT5316_I2C_ID     0x70

#define TOUCH_I2C_ID   FT5316_I2C_ID

extern USBD_HandleTypeDef hUsbDeviceFS;
//extern uint8_t USBD_HID_SendReport (USBD_HandleTypeDef  *pdev, uint8_t *report, uint16_t len);

static uint8_t touchIrq = 0;
static uint16_t oldX[max_point_num]={0,};
static uint16_t oldY[max_point_num]={0,};
static uint8_t p_point_num = 0;


struct __packed touchHid_t {
	uint8_t tip;
	uint8_t num;
	uint16_t x;
	uint16_t y;
	uint8_t width;
	uint8_t height;

};
struct __packed multiTouchHid_t {
	uint8_t report;
	struct touchHid_t touch[max_point_num];
	uint16_t count;
	uint8_t id;
};
struct multiTouchHid_t multiTouch;

void tpd_down(uint16_t x, uint16_t y, uint16_t p)
{
	multiTouch.touch[p].tip = 0x01;
	multiTouch.touch[p].num = p;   //contact id
	multiTouch.touch[p].x = x;
	multiTouch.touch[p].y = y;
	multiTouch.touch[p].width = 0x30; //width of contact
	multiTouch.touch[p].height = 0x30;
	multiTouch.id++;

}
void tpd_up(uint16_t x, uint16_t y, uint16_t p)
{
	multiTouch.touch[multiTouch.id].tip = 0x00;
	multiTouch.touch[multiTouch.id].num = multiTouch.id;
	multiTouch.touch[multiTouch.id].x = x;
	multiTouch.touch[multiTouch.id].y = y;
	multiTouch.touch[multiTouch.id].width = 0x30;
	multiTouch.touch[multiTouch.id].height = 0x30;
	multiTouch.id++;
}

uint8_t buffer[4] = { 0 };
uint16_t prevX= -1;
uint16_t prevY= -1;
int16_t deltaX;
int16_t deltaY;

void touchInput_sync()
{
	multiTouch.report = 0x01;
	multiTouch.count++;
/*
	//for(int i=0;i<max_point_num;i++)
	for(int i=0;i<1;i++)
	{
		printf("%d %d x:%4d  y:%4d\r\n", multiTouch.id, multiTouch.touch[i].tip, multiTouch.touch[i].x, multiTouch.touch[i].y);
	}
*/
/*
	USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&multiTouch, sizeof(struct multiTouchHid_t));
	multiTouch.id=0;
	for(int i=0;i<max_point_num;i++)
	{
		memset(&multiTouch.touch[i], 0x00, sizeof(struct touchHid_t));
	}
*/

	// 0 : button state bit field
	// 1 : signed 8bit X-axis offset since the last position
	// 2 : signed 8bit Y-axis offset since the last position
	// 3 : signed 8bit Wheel offset since the last position
	//uint8_t buffer[4] = { 0 };
	//buffer[1] = 10;
	//static uint16_t old = -1;
	if(prevX == -1)
	{
		prevX = multiTouch.touch[0].x;
		prevY = multiTouch.touch[0].y;
	}
	else
	{
		buffer[1] = 0;
		buffer[2] = 0;

		deltaX = multiTouch.touch[0].x - prevX;
		deltaY = multiTouch.touch[0].y - prevY;

		deltaX *= -1;
		if(deltaX >= 3)
		{
			buffer[1] = deltaX >= 10 ?20:2;
		}
		else
		{
			if(deltaX <= -3)
			{
				buffer[1] = deltaX <= -10?-20:-2;
			}
		}
		prevX = multiTouch.touch[0].x;


		if(deltaY >= 5)
		{
			buffer[2] = -5;
		}
		else
		{
			if(deltaY <= -5)
			{
				buffer[2] = 5;
			}
		}
		prevY = multiTouch.touch[0].y;

		if((buffer[1] != 0) || (buffer[2] != 0))
		{
			USBD_HID_SendReport(&hUsbDeviceFS, buffer, 4);
		}
	}
}


uint8_t *touchPtrGet()
{
	return (uint8_t*)&multiTouch;
}


//interrupt Pen IRQ
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_9)
	{
		touchIrq = 1;
	}
}

void EXTI9_5_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
}

void touchInitGpio()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_8, GPIO_PIN_SET);

	/*Configure GPIO pins : PA10 PA11 */
	GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* RESET Configure GPIO pin : PB8 */
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* INTERRUPT Configure GPIO pin : PB9 */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void touchInit()
{
	touchInitGpio();

	//reset
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(10);


	multiTouch.count = 0;
	multiTouch.id=0;
	for(int i=0;i<max_point_num;i++)
	{
		memset(&multiTouch.touch[i], 0x00, sizeof(struct touchHid_t));
	}
}

void touchProc()
{
	uint8_t point_num;
	uint8_t i;
	uint16_t x[max_point_num];
	uint16_t y[max_point_num];
	uint8_t dat[100];
	if(touchIrq)
	{
		touchIrq=0;

		i2cRead(TOUCH_I2C_ID, 0x00, dat, 33);

		//device mode[6:4]
		//0 Work Mode
		//4 Factory Mode
		if((dat[0] & 0x70) != 0)
			return;

		//Number of Touch points
		point_num =  dat[2] & 0x0f;

		if(point_num > max_point_num)
			point_num = max_point_num;

		for(i = 0; i < point_num; i++)
		{
			//03H [7:6] Event Flag - not used
			// 0 : down
			// 1 : up
			// 2 : contact
			// 3 : reserved
			//05H [7:4] Touch ID
			// [3:0] Touch ID of Touch Point

			//03H [3:0] MSB of Touch X Position in pixels [11:8]
			//04H [7:0] LSB of Touch X Position in pixels [7:0]
			//05H [3:0] MSB of Touch Y Position in pixels [11:8]
			//06H [7:0] LSB of Touch Y Position in pixels [7:0]

			x[i] = (((uint16_t)dat[3+6*i]&0x0F)<<8)|dat[3+6*i+1];
			y[i] = (((uint16_t)dat[3+6*i+2]&0x0F)<<8)|dat[3+6*i+3];
			if(x[i] > 1024)
				x[i] = 1024;
			if(y[i] > 600)
				y[i] = 600;
			x[i] = (x[i]*2048)/1024;// touch range ( 0 ~ 1024 ) to USB HID range (0 ~  2048)
			y[i] = (y[i]*2048)/600; // touch range ( 0 ~ 1024 ) to USB HID range (0 ~  2048)
		}

		if(point_num > 0)
		{
			// pressed
			for(i=0;i<point_num;i++)
			{
				tpd_down(x[i], y[i], i);
				oldX[i] = x[i];
				oldY[i] = y[i];
			}
			//what was pressed in the previous state.
			if(p_point_num > point_num)
			{
				for(i=0;i<p_point_num;i++)
				{
					tpd_up(oldX[i], oldY[i], 0);
				}
			}

			//send data
			touchInput_sync();
		}
		else if(p_point_num>0)
		{
			//release
			for(i=0;i<p_point_num;i++)
			{
				tpd_up(oldX[i], oldY[i], 0);
			}

			//send data
			touchInput_sync();
		}
		p_point_num = point_num;
	}
}
