#include "simple_nfc_target.h"
#include <nfc/nfc.h>

static nfc_device *pnd;
static nfc_context *context;

#define MAX_FRAME_LEN 128
#define DEFAULT_TARGET_TIMEOUT  2000

int nfcWorkAsTarget(uint16_t timeout, nfc_device *curPnd, nfc_context *curContext)
{
    pnd = curPnd;
    context = curContext;
    uint8_t abtRx[MAX_FRAME_LEN];
    int szRx;
    uint8_t abtTx[] = "Hello Mars!";
    nfc_target nt = {
        .nm = {
            .nmt = NMT_DEP,
            .nbr = NBR_UNDEFINED},
        .nti = {
            .ndi = {
                .abtNFCID3 = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xff, 0x00, 0x00},
                .szGB = 4,
                .abtGB = {0x12, 0x34, 0x56, 0x78},
                .ndm = NDM_UNDEFINED,
                /* These bytes are not used by nfc_target_init: the chip will provide them automatically to the initiator */
                .btDID = 0x00,
                .btBS = 0x00,
                .btBR = 0x00,
                .btTO = 0x00,
                .btPP = 0x01,
            },
        },
    };
    if (context == NULL)
    {
        DEBUG_STRING("Unable to init libnfc (malloc)");
        return NFC_ERROR;
    }
    if (pnd == NULL)
    {
        DEBUG_STRING("Unable to open NFC device.\r\n");
        nfc_exit(context);
        return NFC_ERROR;
    }
    DEBUG_STRING("NFC device will now act as Target\r\n");
    DEBUG_STRING("Waiting for initiator request...\r\n");
    if ((szRx = nfc_target_init(pnd, &nt, abtRx, sizeof(abtRx), timeout)) < 0)
    {
        DEBUG_STRING("nfc_target_init_failed\r\n");
        nfc_close(pnd);
        nfc_exit(context);
        return NFC_ERROR;
    }

    DEBUG_STRING("Initiator request received. Waiting for data...\r\n");
    if ((szRx = nfc_target_receive_bytes(pnd, abtRx, sizeof(abtRx), timeout)) < 0)
    {
        DEBUG_STRING("nfc_target_receive_bytes\r\n");
        nfc_close(pnd);
        nfc_exit(context);
        return NFC_ERROR;
    }
    abtRx[(size_t)szRx] = '\0';
    DEBUG_STRING("Received: ");
    DEBUG_STRING(abtRx);
    DEBUG_STRING("\r\n");
    DEBUG_STRING("Sending: ");
    DEBUG_STRING(abtTx);
    DEBUG_STRING("\r\n");
    if (nfc_target_send_bytes(pnd, abtTx, sizeof(abtTx), 0) < 0)
    {
        nfc_perror(pnd, "nfc_target_send_bytes");
        nfc_close(pnd);
        nfc_exit(context);
        return NFC_ERROR;
    }
    DEBUG_STRING("Data sent.\r\n");
    return NFC_SUCCESS;
    nfc_close(pnd);
    nfc_exit(context);
}
