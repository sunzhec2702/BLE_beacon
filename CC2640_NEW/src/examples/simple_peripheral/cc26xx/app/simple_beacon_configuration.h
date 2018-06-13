#ifndef __SIMPLE_BEACON_CONFIGURATION_H
#define __SIMPLE_BEACON_CONFIGURATION_H

#define DEFAULT_BOOT_UP_BLINK           true
#define DEFAULT_WAKE_TIME_MINS          60 //8bits
#define DEFAULT_SCAN_ADV_TRANS_MINS     20 //8bits
#define DEFAULT_OFF_SCAN_PERIOD_MIN     60 //Only 16 bits, max 109 Mins.
#define DEFAULT_OFF_SCAN_PERIOD_x00MS   (DEFAULT_OFF_SCAN_PERIOD_MIN * 60 * 10)

#define DEFAULT_ADVERTISING_INTERVAL    (160 * 20) //100ms * 20 = 2s
#define RAPID_ADVERTISING_INTERVAL      (160 * 2) //100ms * 2 = 200ms

#define RAPID_STATE_PERIOD              (10000) //10s
#define COMMS_STATE_PERIOD              (10000) //10s

#endif

