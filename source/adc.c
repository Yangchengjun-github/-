#include "adc.h"

const unsigned int point_charging[] = {8300 ,};
//unsigned int filter_ad(unsigned int ad)
//{
//    static unsigned int history,ret;
//    if(history == )
//    ret = history*0.2 + ad*0.8;
//    history = ad;
//    return ret;
//
//}

void adc_init()
{
    // 配置adc管脚PB0
    _pbs01 = 1;
    _pbs00 = 1;
    // 配置adc管脚PB1
    _pbs03 = 1;
    _pbs02 = 1;
    //设置ADC时钟
    _sacks2 = 0;
    _sacks1 = 1;
    _sacks0 = 1;
    //adc结果对齐方式
    _adrfs = 1;
    //adc参考电压 VDD
    _savrs1 = 0;
    _savrs0 = 1;
    //使能adc
    _adcen = 1;

   
}
u16 adc_conversion(u8 ADC_Channel)
{
    switch(ADC_Channel)
    {
        case 0x00:
            _sacs0 = 0;
            _sacs1 = 0;
            _sacs2 = 0;
            _sacs3 = 0;
        break;
    case 0x01:
        _sacs0 = 1;
        _sacs1 = 0;
        _sacs2 = 0;
        _sacs3 = 0;
        break;
    default:
        break;

    }
    _start = 0;
    _start = 1;
    _start = 0;
    while (1 == _adbz)
        ;


        /* get the AD conversion value */
          

    return (_sadoh << 8) | _sadol ;
} /* end of ADC_SelectChannel(u8 ADC_Channel) */

unsigned long filter(unsigned int ad)
{
    static unsigned char i;
    static unsigned long sum;
    static unsigned long sum_history;
    sum += ad;
    i++;
    if(i == 128)
    {
        i = 0;
        sum = sum >> 7;
        sum_history = sum;
    }
    else
    {
        return sum_history;
    }
    return sum;

}
void task_ntc_voltage(void)
{
 
    static unsigned char filter_ntc_err = 0;
    static unsigned char filter_voltage_err = 0;

    sys_arg.adc_result[CH_VOL] = adc_conversion(CH_VOL);
    sys_arg.adc_result[CH_TEM] = adc_conversion(CH_TEM);

    if((sys_arg.adc_result[CH_TEM] < TH_TEMP_SHORT) || (sys_arg.adc_result[CH_TEM] > TH_TEMP_OPEN))
    {
        filter_ntc_err++;
        if(filter_ntc_err > 10)
        {
            sys_arg.ntc_err = 1;
        
        }
    }
    else
    {
        filter_ntc_err = 0;
        sys_arg.ntc_err = 0;
    }

    if(sys_arg.adc_result[CH_TEM] < TH_TEMP_HIGH)
    {
        sys_arg.ntc_high = 1;
    }
    else
    {
        sys_arg.ntc_high = 0;
    }


    if((sys_arg.adc_result[CH_VOL] > TH_VOLTAGE_HIGH) || (sys_arg.adc_result[CH_VOL] < TH_VOLTAGE_LOW))
    {
        filter_voltage_err++;
        if(filter_voltage_err > 10)
        {
           sys_arg.voltage_err = 1;
        }
    }
    else
    {
        filter_voltage_err = 0;
        sys_arg.voltage_err = 0;
    }

   
}