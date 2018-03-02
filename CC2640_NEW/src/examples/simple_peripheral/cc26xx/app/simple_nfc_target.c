#include "simple_nfc_target.h"
#include <nfc/nfc.h>

extern nfc_device *pnd;
extern nfc_context *context;

#define MAX_FRAME_LEN 264

void nfcWorkAsTarget(uint16_t timeout)
{
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
    if (pnd == NULL)
    {
        uartEmulatorWriteString("Unable to open NFC device.\r\n");
        nfc_exit(context);
    }
    uartEmulatorWriteString("NFC device will now act as Target\r\n");
    uartEmulatorWriteString("Waiting for initiator request...\r\n");
    if ((szRx = nfc_target_init(pnd, &nt, abtRx, sizeof(abtRx), 0)) < 0)
    {
        uartEmulatorWriteString("nfc_target_init\r\n");
        nfc_close(pnd);
        nfc_exit(context);
    }

    uartEmulatorWriteString("Initiator request received. Waiting for data...\r\n");
    if ((szRx = nfc_target_receive_bytes(pnd, abtRx, sizeof(abtRx), 0)) < 0)
    {
        uartEmulatorWriteString("nfc_target_receive_bytes\r\n");
        nfc_close(pnd);
        nfc_exit(context);
    }
    abtRx[(size_t)szRx] = '\0';
    uartEmulatorWriteString("Received: ");
    uartEmulatorWriteString(abtRx);
    uartEmulatorWriteString("\r\n");
    uartEmulatorWriteString("Sending: ");
    uartEmulatorWriteString(abtTx);
    uartEmulatorWriteString("\r\n");
    if (nfc_target_send_bytes(pnd, abtTx, sizeof(abtTx), 0) < 0)
    {
        nfc_perror(pnd, "nfc_target_send_bytes");
        nfc_close(pnd);
        nfc_exit(context);
    }
    uartEmulatorWriteString("Data sent.\r\n");
    nfc_close(pnd);
    nfc_exit(context);
}
