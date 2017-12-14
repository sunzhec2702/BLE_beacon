#include "nfcApplication.h"
#include "nfc.h"

static uint8 nfcAppID;
static nfc_device *pnd;
static nfc_context *context;

void nfcAppInit(uint8 task_id)
{
    nfcAppID = task_id;
    nfc_init(&context);

    // nfc_connstring connstrings[MAX_DEVICE_COUNT];
    // size_t szDeviceFound = nfc_list_devices(context, connstrings, MAX_DEVICE_COUNT);
    // Little hack to allow using nfc-dep-initiator & nfc-dep-target from
    // the same machine: if there is more than one readers opened
    // nfc-dep-target will open the second reader
    // (we hope they're always detected in the same order)
    pnd = nfc_open(context, NULL);
}

uint16 nfcAppProcessEvent(uint8 task_id, uint16 events)
{
    return 0;
}