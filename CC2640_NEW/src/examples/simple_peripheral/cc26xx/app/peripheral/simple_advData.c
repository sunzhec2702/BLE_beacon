#include "simple_advData.h"
#include "peripheral_observer.h"
#include "gap.h"

#define DEFAULT_DISCOVERABLE_MODE             GAP_ADTYPE_FLAGS_GENERAL

// GAP - Advertisement data (max size = 31 bytes, though this is
// best kept short to conserve power while advertisting)
static uint8_t advertData[] =
{
  // Flags; this sets the device to use limited discoverable
  // mode (advertises for 30 seconds at a time) instead of general
  // discoverable mode (advertises indefinitely)
  0x02,   // length of this data
  GAP_ADTYPE_FLAGS,
  DEFAULT_DISCOVERABLE_MODE | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
  0x1A,
  GAP_ADTYPE_MANUFACTURER_SPECIFIC,
  /*Apple Pre-Amble*/
  0x4C, // 5
  0x00, // 6
  0x02, // 7
  0x15, // 8
  /*Device UUID (16 Bytes)*/
  0x53, 0x4D, 0x54, // SMT 3 Bytes.
  0x00, // 12 reserved
  0x00, // 13 reserved.

  0xFF, 0xFF, 0xFF, // 14, 15, 16, HW/SW version
  0xFF, // 17 Device Type 3 bytes.

  0xFF, //18

  0xFF, //19 How often the beacon will scan for the station in power on mode.
  0xFF, //20 The period which the device keeps poweron even without scanning any data.
  0xFF, //21 How often the beacon will scan for the station in power off mode.
  0xFF, //22 The Data will be ((SEC_1 << 8) + SEC_2)

  /*Specific Data*/
  0x00, // 23
  0x00, // 24, Station Index
  /*Major Value (2 Bytes)*/
  0x00, // 25 for min left
  0x00, // 26 for index 
  /*Minor Value (2 Bytes)*/
  0x00, // 27 FlagByte. bit7 rapid, bit6 low_bat, bit5 Comms.
  0x00, // 28 Battery Value

  0xCD //29  /*Measured Power*/

};

// GAP - SCAN RSP data (max size = 31 bytes)
static uint8_t scanRspData[] =
{
  // complete name
  0x1,   // length of this data
  GAP_ADTYPE_LOCAL_NAME_COMPLETE,
  /*
  'S',
  'i',
  'm',
  'p',
  'l',
  'e',
  'B',
  'L',
  'E',
  'P',
  'e',
  'r',
  'i',
  'p',
  'h',
  'e',
  'r',
  'a',
  'l',
  */
  /*
  // connection interval range
  0x05,   // length of this data
  GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE,
  LO_UINT16(DEFAULT_DESIRED_MIN_CONN_INTERVAL),   // 100ms
  HI_UINT16(DEFAULT_DESIRED_MIN_CONN_INTERVAL),
  LO_UINT16(DEFAULT_DESIRED_MAX_CONN_INTERVAL),   // 1s
  HI_UINT16(DEFAULT_DESIRED_MAX_CONN_INTERVAL),
  // Tx power level
  0x02,   // length of this data
  GAP_ADTYPE_POWER_LEVEL,
  0       // 0dBm
  */
};

void applyAdvData()
{
    GAPRole_SetParameter(GAPROLE_ADVERT_DATA, sizeof(advertData), advertData);
}

void applyResData()
{
    GAPRole_SetParameter(GAPROLE_SCAN_RSP_DATA, sizeof(scanRspData), scanRspData);
}

uint8_t* getAdvData()
{
    return advertData;
}

uint8_t* getResData()
{
    return scanRspData;
}

void updateRapidBit(uint8_t enable)
{
    if (enable)
        advertData[ADV_FLAG_BYTE] |= (0x1 << ADV_FLAG_RAPID_BIT);
    else
        advertData[ADV_FLAG_BYTE] &= ~(0x1 << ADV_FLAG_RAPID_BIT);
}

void updateComBit(uint8_t enable)
{
    if (enable)
        advertData[ADV_FLAG_BYTE] |= (0x01 << ADV_FLAG_COMMS_BIT);
    else
        advertData[ADV_FLAG_BYTE] &= ~(0x01 << ADV_FLAG_COMMS_BIT);
}