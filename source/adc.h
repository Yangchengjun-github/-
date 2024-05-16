#ifndef _ADC_H
#define _ADC_H
#include "main.h"

//
#define TH_TEMP_HIGH  148  //70°
#define TH_TEMP_HIGH1  281   // 50°
#define TH_TEMP_LOW  
#define TH_TEMP_SHORT (10)
#define TH_TEMP_OPEN  (1000)

#define TH_VOLTAGE_HIGH  (0x1e1) //   14 / 6 / 5 * 1024
#define TH_VOLTAGE_LOW  (0x158)  //  10 / 6 / 5 * 1024

void task_ntc_voltage(void);
void adc_init();
u16 adc_conversion(u8 ADC_Channel);

#endif