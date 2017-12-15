#include "nfcApplication.h"
#include "nfc.h"

#define DEFAULT_TARGET_ROLE_TIMEOUT 2000

static uint8 nfcAppID;
static nfc_device *pnd;
static nfc_context *context;

void nfcAppInit(uint8 task_id)
{
    nfcAppID = task_id;
    // Just init and
    nfc_init(&context);
    pnd = nfc_open(context, NULL);
    // We should not close, or we will lose the pnd pointer.
    //nfc_close(pnd);
    nfcWorkAsTarget(0);
}

void nfcWorkAsInitiator(uint16 timeout)
{
    nfc_target nt;
    uint8_t abtRx[MAX_FRAME_LEN];
    uint8_t abtTx[] = "Hello World!";
    if (nfc_initiator_init(pnd) < 0)
    {
        nfc_close(pnd);
        nfc_exit(context);
    }
    if (nfc_initiator_select_dep_target(pnd, NDM_PASSIVE, NBR_212, NULL, &nt, 1000) < 0)
    {
        //No target found, do nothing.

        //nfc_perror(pnd, "nfc_initiator_select_dep_target");
        //nfc_close(pnd);
        //nfc_exit(context);
        //exit(EXIT_FAILURE);
    }
    else
    {
        // Found target
        //print_nfc_target(&nt, false);
        //printf("Sending: %s\n", abtTx);
        int res;
        if ((res = nfc_initiator_transceive_bytes(pnd, abtTx, sizeof(abtTx), abtRx, sizeof(abtRx), 0)) < 0)
        {
            // Handle trans fail.
            //nfc_perror(pnd, "nfc_initiator_transceive_bytes");
            //nfc_close(pnd);
            //nfc_exit(context);
            //exit(EXIT_FAILURE);
        }

        abtRx[res] = 0;
        //printf("Received: %s\n", abtRx);

        if (nfc_initiator_deselect_target(pnd) < 0)
        {
            // We cannot close the pnd, or we will lost pnd.
            //nfc_perror(pnd, "nfc_initiator_deselect_target");
            //nfc_close(pnd);
            //nfc_exit(context);
            //exit(EXIT_FAILURE);
        }
    }
}

void nfcWorkAsTarget(uint16 timeout)
{
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
        //printf("Unable to open NFC device.\n");
        nfc_exit(context);
    }
    //printf("NFC device: %s opened\n", nfc_device_get_name(pnd));
    //signal(SIGINT, stop_dep_communication);
    //printf("NFC device will now act as: ");
    //print_nfc_target(&nt, false);
    // 2000 is the timeout
    if ((szRx = nfc_target_init(pnd, &nt, abtRx, sizeof(abtRx), timeout)) < 0)
    {
        nfc_close(pnd);
        nfc_exit(context);
    }
}

void nfcWorkAsCard()
{
}

uint16 nfcAppProcessEvent(uint8 task_id, uint16 events)
{
    return 0;
}