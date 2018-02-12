#ifndef __SIMPLE_KEY_H
#define __SIMPLE_KEY_H
#include <stdint.h>

#define KEY_SELECT            0x0001
#define KEY_UP                0x0002
#define KEY_DOWN              0x0004
#define KEY_LEFT              0x0008
#define KEY_RIGHT             0x0010

#if (BOARD_TYPE == PRODUCT_BOARD)
#define KEY_PRESSED           1
#define KEY_RELEASED          0
#elif (BOARD_TYPE == DEVELOP_BOARD)
#define KEY_PRESSED           0
#define KEY_RELEASED          1
#endif

#endif