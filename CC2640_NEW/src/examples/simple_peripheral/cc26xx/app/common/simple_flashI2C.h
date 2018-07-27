#ifndef __SIMPLE_FLASH_I2C_H
#define __SIMPLE_FLASH_I2C_H
#include "simple_i2c.h"

/*********************************************************************
 * CONSTANTS
 */
#define FLASH_I2C_0     0
#define FLASH_I2C_1     1
#define FLASH_I2C_NONE  -1

void i2cFlashInit(void);
bool i2cFlashOpen(uint8_t targetSlaveAddr);
void i2cFlashClose(void);
bool flashI2CWriteReg(uint8_t addr, uint8_t *pBuf, uint8_t nBytes);
bool flashI2CReadReg(uint8_t addr, uint8_t *pBuf, uint8_t nBytes);
bool flashI2CWriteRead(uint8_t *wdata, uint8_t wlen, uint8_t *rdata, uint8_t rlen);

#endif
