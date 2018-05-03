#include "simple_beacon_status.h"
#include "osal_snv.h"
#include "simple_beacon_configuration.h"

#define NV_STATUS_ID    0x80 // It is the start id of custom sector.
static SYS_CONFIG bleSysConfig;


static simpleNVFactoryReset(void);


void simpleNVInit()
{
    uint8_t result = 0;
    result = osal_snv_read(NV_STATUS_ID, sizeof(SYS_CONFIG), &bleSysConfig);
    if (result != 0)
    {
        DEBUG_STRING("No Config Stored\r\n");
        simpleNVFactoryReset();
    }
}

static void simpleNVFactoryReset()
{
    bleSysConfig.status = BLE_STATUS_ON_SCAN;
    bleSysConfig.role = BLE_ROLE_NUMBER;
    bleSysConfig.macAddr[B_ADDR_LEN] = 
    bleSysConfig.rssi = 0;
    bleSysConfig.rxGain = 0;
    bleSysConfig.txPower = 0;
    bleSysConfig.bootupBlink = true;
    bleSysConfig.stationIndex = 0;
    bleSysConfig.beaconIndex = 0;
    bleSysConfig.minLeft = DEFAULT_WAKE_TIME_MINS;
    bleSysConfig.keyPressedInScan = false;
    bleSysConfig.onScanAdvTransPeriod = DEFAULT_SCAN_ADV_TRANS_MINS; 
    bleSysConfig.onPeriod = DEFAULT_WAKE_TIME_MINS;
    bleSysConfig.offScanPeriod = SBP_PERIODIC_OFF_SCAN_PERIOD_x00MS; // The scan interval in OFF mode, default 1 hour when power on. Once start adv, change to 5s.
}