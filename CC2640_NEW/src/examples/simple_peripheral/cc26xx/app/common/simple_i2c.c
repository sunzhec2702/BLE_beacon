#include "simple_i2c.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/* Externs */
extern const I2C_Config I2C_config[];

/* Used to check status and initialization */
static int I2C_count = 1;

/* Default I2C parameters structure */
const I2C_Params I2C_defaultParams = {
    I2C_MODE_BLOCKING,  /* transferMode */
    NULL,               /* transferCallbackFxn */
    I2C_100kHz,         /* bitRate */
    (uintptr_t) NULL    /* custom */
};

/*
 *  ======== I2C_cancel ========
 */
void I2C_cancel(I2C_Handle handle)
{
    handle->fxnTablePtr->cancelFxn(handle);
}

/*
 *  ======== I2C_close ========
 */
void I2C_close(I2C_Handle handle)
{
    handle->fxnTablePtr->closeFxn(handle);
}

/*
 *  ======== I2C_control ========
 */
int I2C_control(I2C_Handle handle, unsigned int cmd, void *arg)
{
    return (handle->fxnTablePtr->controlFxn(handle, cmd, arg));
}

/*
 *  ======== I2C_init ========
 */
void I2C_init(void)
{
    if (I2C_count == -1) {
        /* Call each driver's init function */
        for (I2C_count = 0; I2C_config[I2C_count].fxnTablePtr != NULL; I2C_count++) {
            I2C_config[I2C_count].fxnTablePtr->initFxn((I2C_Handle)&(I2C_config[I2C_count]));
        }
    }
}

/*
 *  ======== I2C_open ========
 */
I2C_Handle I2C_open(unsigned int index, I2C_Params *params)
{
    I2C_Handle handle;

    if (index >= I2C_count) {
        return (NULL);
    }

    /* If params are NULL use defaults. */
    if (params == NULL) {
        params = (I2C_Params *) &I2C_defaultParams;
    }

    /* Get handle for this driver instance */
    handle = (I2C_Handle)&(I2C_config[index]);

    return (handle->fxnTablePtr->openFxn(handle, params));
}

/*
 *  ======== I2C_Params_init =======
 */
void I2C_Params_init(I2C_Params *params)
{
    *params = I2C_defaultParams;
}

/*
 *  ======== I2C_transfer ========
 */
bool I2C_transfer(I2C_Handle handle, I2C_Transaction *transaction)
{
    return (handle->fxnTablePtr->transferFxn(handle, transaction));
}
