#include "simpleNFCDevice.h"
#include "nfc-internal.h"

// CC2541 only have one NFC device (NP532)
static struct nfc_context current_nfc_context;
static struct nfc_device current_nfc_device;

void nfc_device_init()
{
    nfc_context_new();
    nfc_driver_init();
}

void nfc_context_new()
{

}

void nfc_driver_init()
{
    
}