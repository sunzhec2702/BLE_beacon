#include "simple_beacon_status.h"
#include "osal_snv.h"
#include "simple_advControl.h"

#define NV_STATUS_ID    0x80 // It is the start id of custom sector.
#define BLE_MAC_ADDR    0x500012E8
SYS_CONFIG bleSysConfig;


static void simpleNVFactoryReset(void);

void retriveMacAddress()
{
    uint8_t macCRC = 0x00;
    for (uint8_t i = 0; i < B_ADDR_LEN; i++)
    {
        bleSysConfig.macAddr[i] = *(uint8_t *)(BLE_MAC_ADDR + B_ADDR_LEN - 1 - i) & 0xFF;
        macCRC = (macCRC + bleSysConfig.macAddr[i]) & 0xFF;
    }
    bleSysConfig.macAddrCRC = (macCRC + 0xBF) & 0xFF;
}

void simpleBleStatusInit()
{
    uint8_t result = 0;
    result = osal_snv_read(NV_STATUS_ID, sizeof(SYS_CONFIG), &bleSysConfig);
    if (result != 0)
    {
        DEBUG_STRING("No Config Stored\r\n");
        simpleNVFactoryReset();
    }
    retriveMacAddress();
    updateAdvMac(bleSysConfig.macAddr ,bleSysConfig.macAddrCRC);
}

static void simpleNVFactoryReset()
{
    bleSysConfig.status = BLE_STATUS_ON_SCAN;
    bleSysConfig.role = BLE_ROLE_NUMBER;
    bleSysConfig.rssi = 0;
    bleSysConfig.rxGain = 0;
    bleSysConfig.txPower = 0;
    bleSysConfig.bootUpBlink = true;
    bleSysConfig.stationIndex = 0;
    bleSysConfig.beaconIndex = 0;
    bleSysConfig.wakeUpSecLeft = DEFAULT_WAKE_TIME_SECOND;

    bleSysConfig.onScanAdvTransPeriod = DEFAULT_SCAN_ADV_TRANS_MINS; 
    bleSysConfig.onPeriod = DEFAULT_WAKE_TIME_MINS;
    bleSysConfig.offScanPeriod = DEFAULT_OFF_SCAN_PERIOD_x00MS; // The scan interval in OFF mode, default 1 hour when power on. Once start adv, change to 5s.
}