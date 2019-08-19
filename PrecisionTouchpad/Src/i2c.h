#ifndef __I2C_H__
#define __I2C_H__

extern void i2cInit();
extern uint8_t i2cRead(uint8_t id,uint8_t addr,uint8_t *databuf,uint16_t number);
extern uint8_t i2cWrite(uint8_t id,uint8_t addr,uint8_t *databuf,uint16_t number);
#endif
