#include "nfcApplication.h"
#include "nfc.h"

#define DEFAULT_TARGET_ROLE_TIMEOUT 2000
#define MAX_FRAME_LEN (264)
#define SAK_ISO14443_4_COMPLIANT 0x20

#define DEFAULT_TIMEOUT_TARGET 10000
#define DEFAULT_TIMEOUT_INITATOR 4000
#define DEFAULT_DEP_TIMES       4
static uint8 abtRx[MAX_FRAME_LEN];
static int szRx;

static uint8 nfcAppID;
static nfc_device *pnd;
static nfc_context *context;
static bool enterDEP = FALSE;

static uint16 randomRole;
static uint8 depTimes = DEFAULT_DEP_TIMES;

uint8 getNFCAppID()
{
    return nfcAppID;
}

void nfcAppInit(uint8 task_id)
{
    nfcAppID = task_id;
    // Just init, no return value.
    nfc_init(&context);
    pnd = nfc_open(context, NULL);
    // Here we open the NFC.
    osal_start_timerEx(nfcAppID, NFC_START_EVT, 1000);
}

int nfcWorkAsInitiator(uint16 timeout)
{
    nfc_target nt;
    uint8 abtRx[MAX_FRAME_LEN];
    uint8 abtTx[] = "Hello World!";
    if (pnd == NULL)
    {
        NFC_UART_DEBUG_STRING("Initiator: pnd == NULL \r\n");
        return -1;
    }
    if (nfc_initiator_init(pnd) < 0)
    {
        //nfc_close(pnd);
        return -1;
    }
    if (nfc_initiator_select_dep_target(pnd, NDM_PASSIVE, NBR_212, NULL, &nt, timeout) < 0)
    {
        NFC_UART_DEBUG_STRING("Initiator: timeout\r\n");
        return -1;
    }
    else
    {
        int res;
        if ((res = nfc_initiator_transceive_bytes(pnd, abtTx, sizeof(abtTx), abtRx, sizeof(abtRx), 0)) < 0)
        {
            NFC_UART_DEBUG_STRING("Initiator: transceive fail\r\n");
            return -1;
        }
        abtRx[res] = 0;
        NFC_UART_DEBUG(abtRx, res+1);
        NFC_UART_DEBUG_STRING("\r\n");
        if (nfc_initiator_deselect_target(pnd) < 0)
        {
            NFC_UART_DEBUG_STRING("Initiator: deselect fail\r\n");
            //return -1;
        }
    }
    return 0;
}

int nfcWorkAsTarget(uint16 timeout)
{
    uint8  abtTx[] = "Hello Mars!";
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
        NFC_UART_DEBUG_STRING("Target: PND == NULL\r\n");
        return -1;
    }

    if ((szRx = nfc_target_init(pnd, &nt, abtRx, sizeof(abtRx), timeout)) < 0)
    {
        NFC_UART_DEBUG_STRING("Target: timeout\r\n");
        return -1;
    }
    else
    {
        if ((szRx = nfc_target_receive_bytes(pnd, abtRx, sizeof(abtRx), 0)) < 0)
        {
            NFC_UART_DEBUG_STRING("Target: receive fail\r\n");
            return -1;
        }
        abtRx[(size_t)szRx] = '\0';
        NFC_UART_DEBUG(abtRx, szRx + 1);
        if (nfc_target_send_bytes(pnd, abtTx, sizeof(abtTx), 0) < 0)
        {
            NFC_UART_DEBUG_STRING("Target: send fail\r\n");
            return -1;
        }
    }
    return 0;
}

int nfcWorkAsCard()
{
    // Example of a Mifare Classic Mini
    // Note that crypto1 is not implemented in this example
    nfc_target nt = {
        .nm = {
            .nmt = NMT_ISO14443A,
            .nbr = NBR_UNDEFINED,
        },
        .nti = {
            .nai = {
                .abtAtqa = {0x00, 0x04},
                .abtUid = {0x08, 0xab, 0xcd, 0xef},
                .btSak = 0x09,
                .szUidLen = 4,
                .szAtsLen = 0,
            },
        },
    };
    //printf("%s will emulate this ISO14443-A tag:\n", argv[0]);
    //print_nfc_target(&nt, true);

    // Switch off NP_EASY_FRAMING if target is not ISO14443-4
    if (nfc_device_set_property_bool(pnd, NP_EASY_FRAMING, (nt.nti.nai.btSak & SAK_ISO14443_4_COMPLIANT)) < 0)
    {
        // Nothing device
        //nfc_perror(pnd, "nfc_target_emulate_tag");
        //nfc_close(pnd);
        //nfc_exit(context);
        //exit(EXIT_FAILURE);
    }
    //printf("NFC device (configured as target) is now emulating the tag, please touch it with a second NFC device (initiator)\n");
    // Need to debug. Use the IRQ for data read instead of waiting reading.
    if (!nfc_target_emulate_tag(pnd, &nt))
    {
        //nfc_perror(pnd, "nfc_target_emulate_tag");
        //nfc_close(pnd);
        //nfc_exit(context);
        //exit(EXIT_FAILURE);
    }
    return 0;
}

void startDEPEvent()
{
    if (pnd != NULL)
    {
        NFC_UART_DEBUG_STRING("NFC_OPEN_DONE\r\n");
    }
    else
    {
        NFC_UART_DEBUG_STRING("NFC_OPEN_FAILED\r\n");
    }
    osal_set_event(nfcAppID, NFC_START_DEP);
}

void stopDEPEvent()
{
    osal_set_event(nfcAppID, NFC_STOP_DEP);
    //nfc_close(pnd);
}

uint16 nfcAppProcessEvent(uint8 task_id, uint16 events)
{
    (void)task_id;
    if (events & NFC_START_EVT)
    {
        //startDEPEvent();
        return events ^ NFC_START_EVT;
    }
    if (events & NFC_START_INITIATOR)
    {
        if (enterDEP == TRUE)
        {
            NFC_UART_DEBUG_STRING("Start Initator\r\n");
            if (nfcWorkAsInitiator(DEFAULT_TIMEOUT_INITATOR) < 0 && (--depTimes > 0))
            {
                osal_start_timerEx(nfcAppID, NFC_START_TARGET, 200);
            }
            if (depTimes <= 0)
            {
                stopDEPEvent();
            }
        }
        return events ^ NFC_START_INITIATOR;
    }
    if (events & NFC_START_TARGET)
    {
        if (enterDEP == TRUE)
        {
            NFC_UART_DEBUG_STRING("Start Target\r\n");
            if (nfcWorkAsTarget(DEFAULT_TIMEOUT_TARGET) < 0 && (--depTimes > 0))
            {
                osal_start_timerEx(nfcAppID, NFC_START_INITIATOR, 200);
            }
            if (depTimes <= 0)
            {
                stopDEPEvent();
            }
        }
        return events ^ NFC_START_TARGET;
    }
    if (events & NFC_START_CARD)
    {
        return events ^ NFC_START_CARD;
    }
    if (events & NFC_START_DEP)
    {
        enterDEP = TRUE;
        depTimes = DEFAULT_DEP_TIMES;
        randomRole = osal_rand() % 2;
        if (randomRole == 0)
        {
            osal_set_event(nfcAppID, NFC_START_INITIATOR);
        }
        else
        {
            osal_set_event(nfcAppID, NFC_START_TARGET);
        }
        return events ^ NFC_START_DEP;
    }
    if (events & NFC_STOP_DEP)
    {
        enterDEP = FALSE;
        osal_stop_timerEx(nfcAppID, NFC_START_INITIATOR|NFC_START_TARGET);
        return events ^ NFC_STOP_DEP;
    }

    if (events & NFC_UART_RECEIVE_TIMEOUT_EVT)
    {
        
        return events ^ NFC_UART_RECEIVE_TIMEOUT_EVT;
    }
    return 0;
}