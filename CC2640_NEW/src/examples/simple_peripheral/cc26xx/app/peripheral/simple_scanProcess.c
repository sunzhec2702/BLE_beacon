#include "simple_scanProcess.h"
#include "util.h"
#include "gap.h"
#include "hci.h"
#include "simple_led.h"
#include "simple_advControl.h"
#include "simple_stateControl.h"
#include "peripheral_observer.h"
#include "simple_peripheral.h"
#include "simple_touchRecord.h"

#include "string.h"
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>

#define COMMS_RSSI_THRES (-40)
#define SCAN_STATUS_TIMEOUT (1000)

static Semaphore_Struct scanStateMutex;
static bool scanningStarted = false;
static bool enableScan = false;
static uint8_t scanTimeLeft = DEFAULT_SCAN_TIME;
static void SimpleBLEPeripheral_scanControl(uint8_t enable);

void scanProcessInit()
{
    Semaphore_Params semParamsMutex;
    // Create protection semaphore
    Semaphore_Params_init(&semParamsMutex);
    semParamsMutex.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&scanStateMutex, 1, &semParamsMutex);
}

void updateScanInterval(uint16_t scanDuration, uint16_t scanInterval, uint16_t scanWindow)
{
    //Setup GAP Observer params
    {
        uint8_t scanRes = DEFAULT_MAX_SCAN_RES;
        GAPRole_SetParameter(GAPROLE_MAX_SCAN_RES, sizeof(uint8_t), &scanRes);
        // Set the GAP Characteristics
        GAP_SetParamValue(TGAP_GEN_DISC_SCAN, scanDuration); //how long to scan (in scan state)
        GAP_SetParamValue(TGAP_LIM_DISC_SCAN, scanDuration);
        //Set scan interval
        GAP_SetParamValue(TGAP_GEN_DISC_SCAN_INT, (scanInterval) / (0.625)); //period for one scan channel
        //Set scan window
        GAP_SetParamValue(TGAP_GEN_DISC_SCAN_WIND, (scanWindow) / (0.625)); //active scanning time within scan interval
    }
}

// We can only enable/disable from here. Or the scan will be always on as default interval.
void scanProcessControl(uint8_t enable)
{
    enableScan = enable;
    SimpleBLEPeripheral_scanControl(enableScan);
}

static void SimpleBLEPeripheral_scanControl(uint8_t enable)
{
    uint8_t status;
    if (enable)
    {
        //Start scanning if not already scanning
        if ((scanningStarted == false))
        {
            status = GAPObserverRole_StartDiscovery(DEFAULT_DISCOVERY_MODE, DEFAULT_DISCOVERY_ACTIVE_SCAN, DEFAULT_DISCOVERY_WHITE_LIST);
            if (status == SUCCESS)
            {
                scanningStarted = true;
                DEBUG_STRING("Scanning On\r\n");
            }
            else
            {
                DEBUG_STRING("Scanning failed\r\n");
            }
        }
    }
    else
    {
        if (scanningStarted == true)
        {
            status = GAPObserverRole_CancelDiscovery();
            if (status == SUCCESS)
            {
                scanningStarted = false;
                DEBUG_STRING("Scanning Off\r\n");
            }
            else
            {
                DEBUG_STRING("Scanning Off Fail\r\n");
            }
            scanTimeLeft = DEFAULT_SCAN_TIME;
        }
    }
    return;
}

void scanDevInfoCB(gapDeviceInfoEvent_t *devInfo)
{
    DEBUG_STRING("DEVINFO_CB\r\n");
    if (devInfo->dataLen != 30)
        return;
    DEBUG_STRING(Util_convertBdAddr2Str(devInfo->addr));
    DEBUG_STRING("\r\n");
    DEBUG_NUMBER(devInfo->rssi);
    DEBUG_STRING("\r\n");
    if (filterBeacon(devInfo->pEvtData))
    {
        if (filterMacCRC(devInfo->pEvtData, devInfo->addr) == true)
        {
            if (filterCommFlag(devInfo->pEvtData))
            {
                DEBUG_STRING("COMMSFLAG\r\n");
                if (devInfo->rssi > COMMS_RSSI_THRES)
                {
                    //static uint16_t targetKeepTime = 0;
                    DEBUG_STRING("Got a pair\r\n");
                    touchRecordGotAPair(devInfo->addr);
                }
            }
        }
    }
}

void scanDoneCB(gapDevDiscEvent_t *data)
{
    if (scanningStarted == false)
    {
        scanTimeLeft = DEFAULT_SCAN_TIME;
        return;
    }
    scanningStarted = false;
    if (scanTimeLeft == 0)
    {
        DEBUG_STRING("scanDone, should no be here\r\n");
        scanTimeLeft = DEFAULT_SCAN_TIME;
    }
    else
    {
        scanTimeLeft--;
        if (enableScan == true)
        {
            SimpleBLEPeripheral_scanControl(true);
        }
    }
}

static uint8_t beaconData[] = {0x4C, 0x00, 0x02, 0x15};
bool filterBeacon(uint8_t *data)
{
    if (memcmp(beaconData, &data[BEACON_START_INDEX], sizeof(beaconData)) == 0)
        return true;
    return false;
}

bool filterCommFlag(uint8_t *data)
{
    if ((data[ADV_FLAG_BYTE] & (0x1 << ADV_FLAG_COMMS_BIT)))
        return true;
    else
        return false;
}

bool filterMacCRC(uint8_t *data, uint8_t *macAddr)
{
    uint8_t crc = 0x00;
    for (uint8_t i = 0; i < B_ADDR_LEN; i++)
    {
        crc += macAddr[i];
    }
    crc += MAC_CRC_KEY;
    if (data[MAC_CRC_ADV_BYTE] == crc)
        return true;
    return false;
}