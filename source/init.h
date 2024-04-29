#ifndef _INIT_H
#define _INIT_H
#include "main.h"

void peripheral_init(unsigned char config);
void mcu_sleep(void);
unsigned int adc_conversion(unsigned char ch);
#endif

