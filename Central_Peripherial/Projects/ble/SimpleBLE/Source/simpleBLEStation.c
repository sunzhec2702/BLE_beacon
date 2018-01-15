#include "simpleBLEStation.h"
#include "simpleBLEPeripheral.h"
#include "simpleBLECentral.h"
#include "npi.h"

#if defined(PLUS_BROADCASTER)
#include "peripheralBroadcaster.h"
#else
#include "peripheral.h"
#endif

#if (PRESET_ROLE == BLE_PRE_ROLE_STATION)
uint8 advertData_iBeacon[] = 
{
  0x02, // length of this data, 0
  GAP_ADTYPE_FLAGS, // 1
  GAP_ADTYPE_FLAGS_GENERAL | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED, // 2
  0x1A, // length of this data 26byte, 3
  GAP_ADTYPE_MANUFACTURER_SPECIFIC, // 4
  /*Apple Pre-Amble*/
  0x4C, // 5
  0x00, // 6
  0x02, // 7
  0x15, // 8
  /*Device UUID (16 Bytes)*/
  0x53, 0x4D, 0x54, // SMT 3 Bytes.
  0x00, // 12 reserved
  0x00, // 13 reserved.
  MAJOR_HW_VERSION, MAJOR_SW_VERSION, MINOR_SW_VERSION, // 14, 15, 16, HW/SW version
  BLE_STATION_ADV, // 17 Device Type 3 bytes.
  0x00, //18
  0x00, //19
  0x00, //20
  0x00, //21
  0x00, //22
  /*Specific Data*/
  0x00, // 23
  0x00, // 24, Station Index
  /*Major Value (2 Bytes)*/
  0x00, // 25 for min left
  0x00, // 26 for index 
  /*Minor Value (2 Bytes)*/
  0x00, // 27 FlagByte. bit7 rapid bit6 low_bat
  0x00, // 28 Battery Value
  0xCD //29  /*Measured Power*/
};

#define PREDATASIZE 4
#define STATION_ADV_SCAN_INTERVAL   2000

extern uint8 advertData_iBeacon[];
extern SYS_CONFIG sys_config;
extern uint8 simpleBLETaskId;


static uint8 *stationConfig = NULL;
static uint16 configDataLen = 0;
static uint16 cmdDataLen = 0;
static uint16 receiveCmdDataLen = 0;
static BLE_SERIAL_CONFIG_CMD_TYPE configCmdType = BLE_SERIAL_CONFIG_CMD_NUM;

// Command Format
// 0xDE, 0xAD, CMD_TYPE, DATA_LEN, DATA, 0xBE, 0xEF.
static uint8 startFrame[] = {0xDE, 0xAD};
static uint8 endFrame[] = {0xBE, 0xEF};

BLE_SERIAL_CONFIG_STATUS serialConfigParser(uint8 *data, uint16 dataLen)
{
    uint16 index = 0;
    BLE_SERIAL_CONFIG_STATUS status = BLE_SERIAL_CONFIG_SUCCESS;
    for (index = 0; index < dataLen; index++)
    {
        if (configDataLen == 0)
        {
            if (data[index] != startFrame[0])
            {
                goto config_error;
            }
            configDataLen++;
        }
        else if (configDataLen == 1)
        {
            if (data[index] != startFrame[1])
            {
                goto config_error;
            }
            configDataLen++;
        }
        else if (configDataLen == 2)
        {
            // CMD_TYPE;
            if (data[index] >= BLE_SERIAL_CONFIG_CMD_NUM)
            {
                goto config_error;
            }
            configCmdType = data[index];
            configDataLen++;
        }
        else if (configDataLen == 3)
        {
            cmdDataLen = data[index];
            stationConfig = osal_mem_alloc(cmdDataLen);
            if (stationConfig == NULL)
            {
                goto config_error;
            }
            configDataLen++;
        }
        else if (configDataLen == (PREDATASIZE + cmdDataLen))
        {
            if (data[index] != endFrame[0])
            {
                goto config_error;
            }
            configDataLen++;
        }
        else if (configDataLen == (PREDATASIZE + cmdDataLen + 1))
        {
            if (data[index] != endFrame[1])
            {
                goto config_error;
            }
            configDataLen++;
            if (serialConfigProcess(configCmdType, stationConfig, cmdDataLen) == FALSE)
            {
                goto config_error;
            }
            DEBUG_PRINT("Config Success\r\n");
            goto config_success;
        }
        else
        {
            stationConfig[receiveCmdDataLen++] = data[index];
            configDataLen++;
        }
    }
return BLE_SERIAL_CONFIG_CONTINUE;

config_error:
    DEBUG_PRINT("Config Error\r\n");
    status = BLE_SERIAL_CONFIG_FAILED;
config_success:
    if (stationConfig != NULL)
    {
        osal_mem_free(stationConfig);
        configDataLen = 0;
        receiveCmdDataLen = 0;
        cmdDataLen = 0;
        configCmdType = BLE_SERIAL_CONFIG_CMD_NUM;
    }
    serialConfigSendAck(status);
    return status;
}

bool serialConfigProcess(BLE_SERIAL_CONFIG_CMD_TYPE cmdType, uint8 *config, uint16 configLen)
{
    switch (configCmdType)
    {
        // Reboot to change to role.
        case BLE_SERIAL_CONFIG_CMD_ROLE_CHANGE:
        if (configLen != 1 || config[0] >= BLE_STATUS_STATION_STATUS_NUM)
        {
            return FALSE;
        }
        switch (config[0])
        {
            case BLE_STATUS_STATION_SCAN:
            if (sys_config.status == BLE_STATUS_STATION_ADV)
            {
                osal_start_timerEx(simpleBLETaskId, SBP_SCAN_ADV_TRANS_EVT, STATION_ADV_SCAN_INTERVAL);
                return TRUE;
            }
            break;
            case BLE_STATUS_STATION_ADV:
            if (sys_config.status == BLE_STATUS_STATION_SCAN)
            {
                osal_start_timerEx(simpleBLETaskId, SBP_SCAN_ADV_TRANS_EVT, STATION_ADV_SCAN_INTERVAL);
                return TRUE;
            }
            break;
        }
        break;
        // Change the advertise data.
        case BLE_SERIAL_CONFIG_CMD_ADV_DATA:
        if (configLen != sizeof(advertData_iBeacon) || sys_config.status == BLE_STATUS_STATION_SCAN)
        {
            return FALSE;
        }
        osal_memcpy(advertData_iBeacon, config, sizeof(advertData_iBeacon));
        GAPRole_SetParameter(GAPROLE_ADVERT_DATA, sizeof(advertData_iBeacon), advertData_iBeacon);
        return TRUE;
        break;

        // Change the advertise interval
        case BLE_SERIAL_CONFIG_CMD_ADV_INTERVAL:
        if (configLen != 1 || sys_config.status == BLE_STATUS_STATION_SCAN)
        {
            return FALSE;
        }
        sys_config.stationAdvInterval = config[0];
        simpleBLE_WriteAllDataToFlash();
        if (sys_config.stationAdvInterval == 0xFF)
        {
            advertise_control(FALSE);
            return TRUE;
        }
        uint8 initial_advertising_enable;
        GAPRole_GetParameter(GAPROLE_ADVERT_ENABLED, &initial_advertising_enable);
        if (initial_advertising_enable == TRUE)
        {
            advertise_control(FALSE);
            simpleBLE_Delay_1ms(500);
        }
        {
            GAP_SetParamValue(TGAP_LIM_DISC_ADV_INT_MIN, ADV_INTERVAL_x00MS_TO_TICK(sys_config.stationAdvInterval));
            GAP_SetParamValue(TGAP_LIM_DISC_ADV_INT_MAX, ADV_INTERVAL_x00MS_TO_TICK(sys_config.stationAdvInterval));
            GAP_SetParamValue(TGAP_GEN_DISC_ADV_INT_MIN, ADV_INTERVAL_x00MS_TO_TICK(sys_config.stationAdvInterval));
            GAP_SetParamValue(TGAP_GEN_DISC_ADV_INT_MAX, ADV_INTERVAL_x00MS_TO_TICK(sys_config.stationAdvInterval));
        }
        advertise_control(TRUE);
        return TRUE;
        break;
        case BLE_SERIAL_CONFIG_CMD_GET_STATUS:
        if (configLen != 1)
        {
            return FALSE;
        }
        BLE_SERIAL_GET_INFO_TYPE get_type = config[0];
        switch (get_type)
        {
            case BLE_SERIAL_GET_ROLE:
            sendWithFrameBuffer((uint8 *)&sys_config.status, 1);
            break;
            case BLE_SERIAL_GET_ADV_DATA:
            sendWithFrameBuffer(advertData_iBeacon, sizeof(advertData_iBeacon));
            break;
            case BLE_SERIAL_GET_ADV_INTERVAL:
            sendWithFrameBuffer((uint8 *)&sys_config.stationAdvInterval, 1);
            break;
            case BLE_SERIAL_GET_MAC:
            uint8 *mac_addr = (uint8*)osal_mem_alloc(MAC_ADDR_CHAR_LEN);
            if (mac_addr == NULL)
            {
                return FALSE;
            }
            GAPRole_GetParameter(GAPROLE_BD_ADDR, mac_addr);
            osal_revmemcpy(sys_config.mac_addr, mac_addr, MAC_ADDR_CHAR_LEN);
            sendWithFrameBuffer(sys_config.mac_addr, MAC_ADDR_CHAR_LEN);
            osal_mem_free(mac_addr);
            return TRUE;
            default:
            return FALSE;
        }
        return TRUE;
        break;
        default:
        break;
    }
    return FALSE;
}

void scan_adv_event_callback(uint8 role)
{
    if (role == BLE_ROLE_CENTRAL)
    {
        sys_config.status = BLE_STATUS_STATION_ADV;
    }
    else if (role == BLE_ROLE_PERIPHERAL)
    {
        sys_config.status = BLE_STATUS_STATION_SCAN;
    }
    simpleBLE_SaveAndReset();
}

static uint8 ACK_SUCCESS[] = {0xAB, 0xCD, 0xEF};
static uint8 ACK_FAILED[] = {0xFF, 0xFF, 0xFF};

void serialConfigSendAck(BLE_SERIAL_CONFIG_STATUS status)
{
    switch (status)
    {
    case BLE_SERIAL_CONFIG_SUCCESS:
        NPI_WriteTransport(ACK_SUCCESS, sizeof(ACK_SUCCESS));
        break;
    case BLE_SERIAL_CONFIG_FAILED:
        NPI_WriteTransport(ACK_FAILED, sizeof(ACK_FAILED));
        break;
    case BLE_SERIAL_CONFIG_CONTINUE:
    default:
        break;
    }
}

void sendWithFrameBuffer(uint8 *data, uint16 dataLen)
{
    uint8 *res = (uint8 *)osal_mem_alloc(PREDATASIZE + dataLen);
    if (res == NULL)
    {
        DEBUG_PRINT("FrameBuffer alloc failed\r\n");
    }
    osal_memcpy(res, startFrame, sizeof(startFrame));
    osal_memcpy(&res[sizeof(startFrame)], data, dataLen);
    osal_memcpy(&res[sizeof(startFrame) + dataLen], endFrame, sizeof(endFrame));
    NPI_WriteTransport(res, PREDATASIZE + dataLen);
    osal_mem_free(res);
}

void scan_device_info_callback(gapCentralRoleEvent_t *pEvent)
{
  if (simpleBLEFilterSelfBeacon(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.dataLen) == TRUE &&
        simpleBLEFilterIsSmart(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.dataLen) == TRUE &&
        simpleBLEFilterDeviceType(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.dataLen) == BLE_BEACON)
  {
    static dev_adv_ret_t dev_ret;
    osal_memset(&dev_ret, 0x00, sizeof(dev_adv_ret_t));
    dev_ret.magic[0] = 0xDE;
    dev_ret.magic[1] = 0xAD;
    dev_ret.magic[2] = 0xBE;
    dev_ret.magic[3] = 0xAF;
    dev_ret.addrType = pEvent->deviceInfo.addrType;
    dev_ret.rssi = pEvent->deviceInfo.rssi;
    dev_ret.dataLen = pEvent->deviceInfo.dataLen;
    osal_revmemcpy(dev_ret.addr, pEvent->deviceInfo.addr, B_ADDR_LEN);
    osal_memcpy(dev_ret.data, pEvent->deviceInfo.pEvtData, dev_ret.dataLen);
    NPI_WriteTransport((unsigned char *)&dev_ret, sizeof(dev_adv_ret_t));

#ifdef DEBUG_BOARD
    DEBUG_PRINT((unsigned char *)bdAddr2Str(pEvent->deviceInfo.addr));
    DEBUG_PRINT(" - ");
    NPI_PrintValue("RSSI: ", pEvent->deviceInfo.rssi, 10);
    DEBUG_PRINT(" - ");
    NPI_PrintValue("DataLen: ", pEvent->deviceInfo.dataLen, 10);
    if (simpleBLEFilterSelfBeacon(dev_ret.data, dev_ret.dataLen) == TRUE)
    {
      DEBUG_PRINT(" - ");
      DEBUG_PRINT(" TRUE ");
      if (dev_ret.data[27] == 0x80)
      {
        DEBUG_PRINT(" - ");
        DEBUG_PRINT(" PRESSED ");
      }
    }
    DEBUG_PRINT("\r\n");
#endif
  }
}

bool scan_discovery_callback()
{
  resetScanTimeLeft();
  return TRUE;
}


void key_press_callback_central(uint8 key_cnt_number)
{
  VOID key_cnt_number;
  return;
}

#endif