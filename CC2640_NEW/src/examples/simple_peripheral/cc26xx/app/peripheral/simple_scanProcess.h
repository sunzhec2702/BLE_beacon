#ifndef __SIMPLE_SCAN_PROCESS_H
#define __SIMPLE_SCAN_PROCESS_H

void filterCRC(uint8_t *data);
void filterCMD(uint8_t *data);
void checkSendSource(uint8_t *data);

#endif
