#ifndef __SIMPLE_NFC_H
#define __SIMPLE_NFC_H

void simpleNFCcreateTask(void);
void nfcKeyCallback(uint8_t keyStatus);
void controlNfcTasks(bool enable);
#endif
