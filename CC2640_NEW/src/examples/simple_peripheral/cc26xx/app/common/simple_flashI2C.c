#include "simple_flashI2C.h"
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/i2c/I2CCC26XX.h>

/* -----------------------------------------------------------------------------
*  Constants
* ------------------------------------------------------------------------------
*/
#define I2C_TIMEOUT 500 //ms
/* I2C driver interface */
static I2C_Handle i2cHandle;
static I2C_Params i2cParams;
static Semaphore_Struct mutex;

/* Module state */
static volatile uint8_t interface;
static volatile uint8_t slaveAddr;
static uint8_t buffer[32];

void i2cFlashInit()
{
    Semaphore_Params semParamsMutex;

    // Create protection semaphore
    Semaphore_Params_init(&semParamsMutex);
    semParamsMutex.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&mutex, 1, &semParamsMutex);

    // Initialize I2C bus
    I2C_init();
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
}

bool i2cFlashOpen()
{
    i2cHandle = I2C_open(Board_I2C, &i2cParams);
    // Initialize local variables
    slaveAddr = 0xFF;
    interface = FLASH_I2C_0;
    return i2cHandle != NULL;
}

void i2cFlashClose(void)
{
    if (i2cHandle != NULL)
    {
        I2C_close(i2cHandle);
    }
    i2cHandle = NULL;
}