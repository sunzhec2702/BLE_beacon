#include "simple_flashI2C.h"
#include "Board.h"
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/i2c/I2CCC26XX.h>
#include <ti/sysbios/knl/Clock.h>
#include "util.h"

#define ADDR_24C08 0x50 // 7-bit address
#define I2C_TIMEOUT 100 //ms
#define MS_2_TICKS(ms) (((ms)*1000) / Clock_tickPeriod)

/* I2C driver interface */
static I2C_Handle i2cHandle;
static I2C_Params i2cParams;
static Semaphore_Struct mutex;
static Clock_Struct resourceClock;

/* Module state */
static volatile uint8_t slaveAddr;
static uint8_t buffer[32];


void resourceClockCallback(UArg arg)
{
    Semaphore_post(Semaphore_handle(&mutex)); 
}

bool flashI2CWrite(uint8_t *data, uint8_t len)
{
    I2C_Transaction masterTransaction;

    masterTransaction.writeCount = len;
    masterTransaction.writeBuf = data;
    masterTransaction.readCount = 0;
    masterTransaction.readBuf = NULL;
    masterTransaction.slaveAddress = slaveAddr;

    return I2C_transfer(i2cHandle, &masterTransaction) == TRUE;
}

bool flashI2CWriteSingle(uint8_t data)
{
    uint8_t d;
    d = data;
    return flashI2CWrite(&d, 1);
}

bool flashI2CRead(uint8_t *data, uint8_t len)
{
    I2C_Transaction masterTransaction;

    masterTransaction.writeCount = 0;
    masterTransaction.writeBuf = NULL;
    masterTransaction.readCount = len;
    masterTransaction.readBuf = data;
    masterTransaction.slaveAddress = slaveAddr;

    return I2C_transfer(i2cHandle, &masterTransaction) == TRUE;
}

bool flashI2CWriteRead(uint8_t *wdata, uint8_t wlen, uint8_t *rdata, uint8_t rlen)
{
    I2C_Transaction masterTransaction;
    masterTransaction.writeCount = wlen;
    masterTransaction.writeBuf = wdata;
    masterTransaction.readCount = rlen;
    masterTransaction.readBuf = rdata;
    masterTransaction.slaveAddress = slaveAddr;
    return I2C_transfer(i2cHandle, &masterTransaction) == TRUE;
}

/*******************************************************************************
* @fn          S ensorI2C_readReg
*
* @brief       This function implements the I2C protocol to read from a sensor.
*              The sensor must be selected before this routine is called.
*
* @param       addr - which register to read
* @param       pBuf - pointer to buffer to place data
* @param       nBytes - number of bytes to read
*
* @return      TRUE if the required number of bytes are received
******************************************************************************/
bool flashI2CReadReg(uint8_t addr, uint8_t *pBuf, uint8_t nBytes)
{
    return flashI2CWriteRead(&addr, 1, pBuf, nBytes);
}

/*******************************************************************************
* @fn          SensorI2C_writeReg
* @brief       This function implements the I2C protocol to write to a sensor.
*              The sensor must be selected before this routine is called.
*
* @param       addr - which register to write
* @param       pBuf - pointer to buffer containing data to be written
* @param       nBytes - number of bytes to write
*
* @return      TRUE if successful write
*/
bool flashI2CWriteReg(uint8_t addr, uint8_t *pBuf, uint8_t nBytes)
{
    uint8_t i;
    uint8_t *p = buffer;

    /* Copy address and data to local buffer for burst write */
    *p++ = addr;
    for (i = 0; i < nBytes; i++)
    {
        *p++ = *pBuf++;
    }
    nBytes++;

    /* Send data */
    return flashI2CWrite(buffer, nBytes);
}

/*
bool flashI2CSelect(uint8_t newInterface, uint8_t address)
{
    // Acquire I2C resource
    if (!Semaphore_pend(Semaphore_handle(&mutex),MS_2_TICKS(I2C_TIMEOUT)))
    {
        return false;
    }

    // Store new slave address
    slaveAddr = address;

    // Interface changed ?
    if (newInterface != interface)
    {
        // Store new interface
        interface = newInterface;

        // Shut down RTOS driver
        I2C_close(i2cHandle);

        // Sets custom to NULL, selects I2C interface 0
        I2C_Params_init(&i2cParams);

        // Assign I2C data/clock pins according to selected I2C interface 1
        if (interface == FLASH_I2C_1)
        {
            //i2cParams.custom = (uintptr_t)&pinCfg1;
        }

        // Re-open RTOS driver with new bus pin assignment
        i2cHandle = I2C_open(Board_I2C, &i2cParams);
    }

    return i2cHandle != NULL;
}

void flashI2CDeselect(void)
{
    // Release I2C resource
    Semaphore_post(Semaphore_handle(&mutex));
}
*/

void i2cFlashInit()
{
    Semaphore_Params semParamsMutex;
    // Create protection semaphore
    Semaphore_Params_init(&semParamsMutex);
    semParamsMutex.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&mutex, 1, &semParamsMutex);
    Util_constructClock(&resourceClock, resourceClockCallback, 0, 0, false, 0);
    // Initialize I2C bus
    I2C_init();
    I2C_Params_init(&i2cParams);
}

bool i2cFlashOpen(uint8_t targetSlaveAddr)
{
    if (!Semaphore_pend(Semaphore_handle(&mutex), MS_2_TICKS(I2C_TIMEOUT*2)))
        return false;
    if (i2cHandle != NULL)
    {
        DEBUG_STRING("I2C is in use\r\n");
        return false;
    }
    i2cHandle = I2C_open(Board_I2C, &i2cParams);
    slaveAddr = targetSlaveAddr;
    return i2cHandle != NULL;
}

void i2cFlashClose()
{
    if (i2cHandle != NULL)
    {
        I2C_close(i2cHandle);
    }
    slaveAddr = ADDR_24C08;
    i2cHandle = NULL;
    Util_restartClock(&resourceClock, I2C_TIMEOUT);
}