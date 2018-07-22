#ifndef __SIMPLE_VIBRA_SENSOR_H_
#define __SIMPLE_VIBRA_SENSOR_H_
#include "board.h"
#include "util.h"

void vibraSensorInit(void);
bool getVibraStatus(void);
void vibraIntControl(bool enable);

#endif
