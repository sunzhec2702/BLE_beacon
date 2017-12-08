#include "simpleNFCDevice.h"
#include "nfc-internal.h"
#include "pn532_uart.h"
#include "pn53x.h"
#include "../simpleble.h"

#define NFC_NAME "DarrenNFC"

static struct pn53x_data nfc_chip_data;
static struct pn532_uart_data nfc_uart_data;

// CC2541 only have one NFC device (NP532)
static nfc_context nfc_context_instance =
    {
        .allow_autoscan = TRUE,
        .allow_intrusive_scan = TRUE,
};
static nfc_device nfc_device_instance =
    {
        .bCrc = FALSE,
        .bPar = FALSE,
        .bEasyFraming = FALSE,
        .bInfiniteSelect = FALSE,
        .bAutoIso14443_4 = FALSE,
        .last_error = 0,
        .name = NFC_NAME,
        .driver_data = &nfc_uart_data,
        .driver = &pn532_uart_driver,
        .context = &nfc_context_instance,
        .chip_data = &nfc_chip_data,
};

static struct nfc_device* nfc_dev_ptr = &nfc_device_instance;
static struct nfc_context* nfc_con_ptr = &nfc_context_instance;

void nfc_init()
{
    nfc_context_init();
    nfc_device_init();
}

void nfc_context_init()
{
}

void nfc_device_init()
{
    pn53x_data_new(nfc_dev_ptr, &pn532_uart_io);
    CHIP_DATA(nfc_dev_ptr)->type = PN532;
    CHIP_DATA(nfc_dev_ptr)->power_mode = LOWVBAT;
    CHIP_DATA(nfc_dev_ptr)->timer_correction = 48;
    // DRIVER_DATA(nfc_dev_ptr)->abort_flag = false;
    // Check communication using "Diagnose" command, with "Communication test" (0x00)
    if (pn53x_check_communication(nfc_dev_ptr) < 0)
    {
        return;
    }
    pn53x_init(nfc_dev_ptr);
}
