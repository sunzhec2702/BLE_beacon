#include "simpleBLEStation.h"
#include "simpleBLECentral.h"

#if (PRESET_ROLE == BLE_PRE_ROLE_STATION)
#define PREDATASIZE 4
#define STATION_ADV_SCAN_INTERVAL   5000


extern SYS_CONFIG sys_config;
extern uint8 simpleBLETaskId;


static uint8 *stationConfig = NULL;
static uint16 configDataLen = 0;
static uint16 cmdDataLen = 0;
static uint16 receiveCmdDataLen = 0;
static BLE_SERIAL_CONFIG_CMD_TYPE configCmdType = BLE_SERIAL_CONFIG_CMD_NUM;

static uint8 startFrame[] = {0xDE, 0xAD};
static uint8 endFrame[] = {0xBE, 0xEF};

BLE_SERIAL_CONFIG_STATUS serialConfigParser(uint8 *data, uint16 dataLen)
{
    DEBUG_VALUE("Got dataLen : ", dataLen, 10);
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
        else if (PREDATASIZE + cmdDataLen)
        {
            if (data[index] != endFrame[0])
            {
                goto config_error;
            }
            configDataLen++;
        }
        else if (PREDATASIZE + cmdDataLen + 1)
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
            break;
        }
        break;
        case BLE_SERIAL_CONFIG_CMD_ADV_DATA:
        break;
        case BLE_SERIAL_CONFIG_CMD_ADV_INTERVAL:
        break;
        case BLE_SERIAL_CONFIG_CMD_GET_STATUS:
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

static uint8 ACK_SUCCESS[] = {0xFF, 0x00, 0xFF};
static uint8 ACK_FAILED[] = {0x00, 0xFF, 0x00};

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

}

void scan_device_info_callback(gapCentralRoleEvent_t *pEvent)
{
  if (simpleBLEFilterSelfBeacon(pEvent->deviceInfo.pEvtData, pEvent->deviceInfo.dataLen) == TRUE)
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
  return FALSE;
}


void key_press_callback(uint8 key_cnt_number)
{
    return;
}

#endif