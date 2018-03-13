#include "simple_nfc_initiator.h"
#include <nfc/nfc.h>

static nfc_device *pnd;
static nfc_context *context;
#define MAX_FRAME_LEN   264

int nfcWorkAsInitiator(uint16_t timeout, nfc_device *curPnd, nfc_context *curContext)
{
    pnd = curPnd;
    context = curContext;

    nfc_target nt;
    uint8_t abtRx[MAX_FRAME_LEN];
    uint8_t abtTx[] = "Hello World!";

    if (context == NULL)
    {
        DEBUG_STRING("context is NULL\r\n");
        return NFC_ERROR;
    }
    if (pnd == NULL)
    {
        DEBUG_STRING("pnd is NULL\r\n");
        nfc_exit(context);
        return NFC_ERROR;
    }

    if (nfc_initiator_init(pnd) < 0)
    {
        DEBUG_STRING("nfc_initiator_init failed\r\n");
        nfc_close(pnd);
        nfc_exit(context);
        return NFC_ERROR;
    }

    if (nfc_initiator_select_dep_target(pnd, NDM_PASSIVE, NBR_212, NULL, &nt, 1000) < 0)
    {
        DEBUG_STRING("nfc_initiator_select_dep_target failed\r\n");
        nfc_close(pnd);
        nfc_exit(context);
        return NFC_ERROR;
    }
    //print_nfc_target(&nt, false);

    DEBUG_STRING("Sending: ");
    DEBUG_STRING(abtTx);
    DEBUG_STRING("\r\n");
    int res;
    if ((res = nfc_initiator_transceive_bytes(pnd, abtTx, sizeof(abtTx), abtRx, sizeof(abtRx), 0)) < 0)
    {
        DEBUG_STRING("nfc_initiator_transceive_bytes failed\r\n");
        nfc_close(pnd);
        nfc_exit(context);
        return NFC_ERROR;
    }

    abtRx[res] = 0;
    DEBUG_STRING("Received: ");
    DEBUG_STRING(abtRx);
    DEBUG_STRING("\r\n");

    if (nfc_initiator_deselect_target(pnd) < 0)
    {
        DEBUG_STRING("nfc_initiator_deselect_target failed, but it's ok\r\n");
        return NFC_SUCCESS;
        /*
        nfc_close(pnd);
        nfc_exit(context);
        return NFC_ERROR;
        */
    }
    return NFC_SUCCESS;
    /*
    nfc_close(pnd);
    nfc_exit(context);
    */
}