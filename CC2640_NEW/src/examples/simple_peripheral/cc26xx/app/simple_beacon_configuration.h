#ifndef __SIMPLE_BEACON_CONFIGURATION_H
#define __SIMPLE_BEACON_CONFIGURATION_H
#include "simple_beacon_status.h"
extern SYS_CONFIG bleSysConfig;

#define SBP_PERIODIC_EVT_PERIOD         1000 // 1s for release
//#define SBP_PERIODIC_EVT_PERIOD         1 // 1ms for debug

#define MAC_CRC_KEY                     0xBF

// General
#define DEFAULT_BOOT_UP_BLINK           true
#define DEFAULT_WAKE_TIME_MINS          (1 * 60) //1 Hours
#define DEFAULT_WAKE_TIME_SECOND        (DEFAULT_WAKE_TIME_MINS * 60)

// Interval
#define DEFAULT_SCAN_ADV_TRANS_MINS     20 //8bits
#define DEFAULT_OFF_SCAN_PERIOD_MIN     60 //Only 16 bits, max 109 Mins.
#define DEFAULT_OFF_SCAN_PERIOD_x00MS   (DEFAULT_OFF_SCAN_PERIOD_MIN * 60 * 10)

#define DEFAULT_ADVERTISING_INTERVAL    (160 * 20) //100ms * 20 = 2s
#define RAPID_ADVERTISING_INTERVAL      (160 * 2) //100ms * 2 = 200ms

// Beacon Status
#define RAPID_STATE_PERIOD              (2000) //2s
#define COMMS_STATE_PERIOD              (15000) //15s

// LED
#define LED_BLINK_ON_PERIOD         (60) //ms
#define LED_BLINK_OFF_PERIOD        (150) //ms
// #define LED_BLINK_RAPID_OFF_PERIOD  (150) //ms
#define LED_BLINK_COMMUNICATE_ON_PERIOD (200)
#define LED_BLINK_COMMUNICATE_OFF_PERIOD (800)

// Vibra Sensor
#define VIBRA_SENSOR_CHECK_PERIOD   (1 * 60 * 1000) //1 min

// Adv Power
#define DEF_TX_POWER        HCI_EXT_TX_POWER_MINUS_6_DBM
#define MAX_TX_POWER        HCI_EXT_TX_POWER_2_DBM

// Touch Recrod
#define MAC_RECORD_UPDATE_SEC_PERIOD    30 // 60 sec
#define ADD_MAC_SUCCESS_BLINK_PERIOD    2000 // 2s





// Advertise Config
// Limited discoverable mode advertises for 30.72s, and then stops
// General discoverable mode advertises indefinitely
#define DEFAULT_DISCOVERABLE_MODE             GAP_ADTYPE_FLAGS_GENERAL

// Minimum connection interval (units of 1.25ms, 80=100ms) if automatic
// parameter update request is enabled
#define DEFAULT_DESIRED_MIN_CONN_INTERVAL     120

// Maximum connection interval (units of 1.25ms, 800=1000ms) if automatic
// parameter update request is enabled
#define DEFAULT_DESIRED_MAX_CONN_INTERVAL     320


// Slave latency to use if automatic parameter update request is enabled
#define DEFAULT_DESIRED_SLAVE_LATENCY         0

// Supervision timeout value (units of 10ms, 1000=10s) if automatic parameter
// update request is enabled
#define DEFAULT_DESIRED_CONN_TIMEOUT          500

// Whether to enable automatic parameter update request when a connection is
// formed
#define DEFAULT_ENABLE_UPDATE_REQUEST         TRUE

// Connection Pause Peripheral time value (in seconds)
#define DEFAULT_CONN_PAUSE_PERIPHERAL         6

#endif

