

 #include "main.h"
#include "string.h"
sys_arg_T sys_arg = {0};
sys_cmd_T sys_cmd = {0};
sys_clk_T sys_clk = {0};

void driver_init(u16 ccra, u16 ccrp);
void valve_off();
void valve_out();
void valve_out_pwm();


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
    driver_init(50,2);
    valve_off();
    memset(&sys_arg, 0, sizeof(sys_arg_T));
    memset(&sys_cmd, 0, sizeof(sys_cmd_T));
    memset(&sys_clk, 0, sizeof(sys_clk_T));
    memset(key_cb, 0, sizeof(key_cb));
    sys_arg.system_status = SYSTEM_POWOFF;
    sys_cmd.cmd_ui_off = 1;
    buzzer_status = BEEP_IDLE;
    MOTOR_POWOFF;
    VALVE_POWOFF;
    //  GCC_DELAY(2000);			//wait system stable

    // system loop
    while (1)
    {
         GCC_CLRWDT();
         task_run();       
    }
}

void driver_init(u16 ccra, u16 ccrp)
{
    //valve
    _stm1 = 1;
    _stm0 = 0;
    _stio1 = 1;
    _stio0 = 0; // Select STM PWM Output Mode
    //_t0cp = 1;
    _stpau = 0;
    _pac0 = 0;
    _pa0 = 0;

    _pas00 = 1;
    _pas01 = 1;

    _stck2 = 0;
    _stck1 = 0;
    _stck0 = 1;

    _stcclr = 1;

    _stoc = 1;  // active high
    _stpol = 0; // no inverted
    _stdpx = 0;

    _stmal = ccra & 0x00ff; //
    _stmah = ccra >> 8;     //

    _strp2 = (ccrp >> 2) & 0x01;
    _strp1 = (ccrp >> 1) & 0x01;
    _strp0 = ccrp & 0x01;

    _ston = 0; // enable STM

    // motor
    _pbc2 = 0;
    _pb2 = 0;
}

void valve_off()
{
    _pac0 = 0;
    _pa0 = 0;
    _pas00 = 0;
    _pas01 = 0;
    _ston = 0;
}
void valve_out()
{
    _pac0 = 0;
    _pa0 = 1;
    _pas00 = 0;
    _pas01 = 0;
    _ston = 0;
}
void valve_out_pwm()
{
    _pac0 = 0;
    _pa0 = 0;
    _pas00 = 1;
    _pas01 = 1;
    _ston = 1;
}
