#include "nfcApplication.h"
#include "nfc.h"

static uint8 nfcAppID;
static nfc_device *pnd;
static nfc_context *context;

void nfcAppInit(uint8 task_id)
{
    nfcAppID = task_id;
    nfc_init(&context);
    pnd = nfc_open(context, NULL);
}

uint16 nfcAppProcessEvent(uint8 task_id, uint16 events)
{
    return 0;
}