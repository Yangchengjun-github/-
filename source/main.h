#ifndef _MAIN_H_
#define _MAIN_H_

typedef char s8;
typedef unsigned char u8;
typedef int s16;
typedef unsigned int u16;

#include "HT66F0181.h"
#include "app.h"
#include "key.h"
// #include "init.h"
#include "led.h"
#include "task.h"
#include "adc.h"
#include "buzzer.h"
#include "HT8_Simulation_UART.h"
#define CH_VOL 0
#define CH_TEM 1





#define HEAT_OVERTIME (100*60*2.5)
typedef enum
{
    SYSTEM_POWOFF = 0,
    SYSTEM_POWON,
} system_status_T;


typedef enum
{
    MODE_HALT,      //????
    MODE_CONTINUE,  //??????
    MDDE_PULSED,    //??????

}mode_t;
typedef enum
{
    lock_disable,
    lock_enable,
} system_lock_T;

typedef enum
{
    HEAT_LEVEL_1 = 0,
    HEAT_LEVEL_2,
    HEAT_LEVEL_3,
} heat_level_T;

typedef enum
{
    UI_LED_OFF = 0,
    UI_LED_NORMAL,
    UI_LED_ALARM,
    UI_LED_ALARM_LONG,

   
} ui_led_T;

typedef enum
{
    // BAT_PER100,
    // BAT_PER66,
    // BAT_PER33,
    // BAT_PER20,
    // BAT_PER10,
    // BAT_PER0,

    BAT_PER0,
    BAT_PER10,
    BAT_PER20,
    BAT_PER33,
    BAT_PER66,
    BAT_PER100,
} bat_percent_T;
typedef struct 
{
    system_status_T system_status;
    heat_level_T heat_level;
    system_lock_T system_lock;
    ui_led_T ui_led_mode;
    unsigned int adc_result[2];
    unsigned int bat_filter;
    bat_percent_T bat_percent;
    unsigned int sleep_timer;
    unsigned long  timer_autoShutdown;
    unsigned long  timer_disable;
    unsigned char heat_sw;
    unsigned char temperature_ok;
    unsigned long heat_timer;
    unsigned char ntc_err;
    unsigned char voltage_err;
    unsigned char ntc_high;
    unsigned char bat_history_max;
    unsigned char bat_history_min;
    mode_t mode;
    unsigned int timer_pulsed;
    unsigned int alarm_timer;
    unsigned int limit_timer;
    enum
    {
        step1 = 0,
        step2,
        step3,
    }run_step;

} sys_arg_T;

typedef struct 
{
    unsigned char cmd_powon : 1;
    unsigned char cmd_powoff : 1;
    unsigned char cmd_levelAdj : 1;
  
    unsigned char cmd_beep_long : 1;
    unsigned char cmd_beep_short1 : 1;
    unsigned char cmd_beep_short2 : 1;
    unsigned char cmd_beep_short3 : 1;
    unsigned char cmd_beep_two : 1;
    unsigned char cmd_beep_three : 1;
    unsigned char cmd_beep_three_long : 1;
    unsigned char cmd_cntdown_reset : 1;

    unsigned char cmd_ui_off : 1;
    unsigned char cmd_ui_on : 1;   
    unsigned char cmd_ui_alarm : 1;
    unsigned char cmd_ui_alarm_long : 1;

} sys_cmd_T;

typedef struct 
{
    unsigned char period_1ms : 1;
    unsigned char period_10ms : 1;
    unsigned char period_100ms : 1;
    unsigned char period_1s : 1;
    
} sys_clk_T;

extern  sys_arg_T sys_arg;
extern  sys_cmd_T sys_cmd;
extern  sys_clk_T sys_clk;



void valve_off();

void valve_out();

void valve_out_pwm();
#endif

