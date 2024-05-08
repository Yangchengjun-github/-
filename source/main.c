

 #include "main.h"
#include "string.h"
sys_arg_T sys_arg = {0};
sys_cmd_T sys_cmd = {0};
sys_clk_T sys_clk = {0};


void other_init();

void fun(void)
{
    LED3_TOGGLE;
}
void main()
{
    #if (DEBUG == 1)
    SIMULATION_UART_INIT();		//simulation uart initialization,set baud rate 9600(Fsys=8MHz)
    #endif
    buzzer_init(500, 1000);	//buzzer initialization,set frequency 1KHz
    adc_init(); //adc initialization
    timebase_init(); //time base initialization
    led_init(); //led initialization
    key_init(); //key initialization
    other_init();
    memset(&sys_arg, 0, sizeof(sys_arg_T));
    memset(&sys_cmd, 0, sizeof(sys_cmd_T));
    memset(&sys_clk, 0, sizeof(sys_clk_T));
    memset(key_cb, 0, sizeof(key_cb));
    sys_arg.system_status = SYSTEM_POWOFF;
    sys_cmd.cmd_ui_off = 1;
    buzzer_status = BEEP_IDLE;
    MOTOR_POWOFF;
    VALVE_POWOFF;
    //sys_cmd.cmd_powoff = 1;
    //  GCC_DELAY(2000);			//wait system stable

    // system loop
    while (1)
    {
        // sys_arg.adc_result[CH_VOL] = adc_conversion(CH_VOL);
        // UART_SoftWareSendByte(sys_arg.adc_result[CH_VOL] >> 8);
        // UART_SoftWareSendByte(sys_arg.adc_result[CH_VOL]);
        // g_nUART_TX_Data++;						//transmit data+1,it will be transmit next loop
         GCC_CLRWDT();
        // GCC_DELAY(1000);
        // GCC_CLRWDT();
        //_pc1 = ~_pc1; // toggle PC1 output
        //_pc2 = ~_pc2;
         task_run();
        
    }
}


void other_init()
{
    //motol
    _pbc2 = 0;
    _pb2 = 0;
    //valve
    _pac4 = 0;
    _pa4 = 0;
}
