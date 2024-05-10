#include "led.h"



unsigned int time_blink = 0;
//10MS 任务
void led_init(void)
{
    //LED1
    _pc0 = 1;
    _pcc0 = 0;
    //LED2
    _pc1 = 1;
    _pcc1 = 0;
    //LED3
    _pc2 = 1;
    _pcc2 = 0;
    //LED4
    _pa4 = 1;
    _pac4 = 0;
    //LED5
    _pa1 = 1;
    _pac1 = 0;
    //LED6
    _pa2 = 1;
    _pac2 = 0;
}
void task_led(void)
{
    static unsigned int timer = 0;
    static u16 timer_blink  = 0;



    if (sys_cmd.cmd_ui_alarm == 1)
    {
        timer = 0;
        sys_cmd.cmd_ui_alarm= 0;
        sys_arg.ui_led_mode = UI_LED_ALARM;
    }
    if (sys_cmd.cmd_ui_on == 1)
    {
        timer = 0;
        sys_cmd.cmd_ui_on = 0;
        sys_arg.ui_led_mode = UI_LED_NORMAL;
    }
    if (sys_cmd.cmd_ui_off == 1 && sys_arg.ui_led_mode != UI_LED_ALARM)
    {
        timer = 0;
        sys_cmd.cmd_ui_off = 0;
        sys_arg.ui_led_mode = UI_LED_OFF;
    }



   
    switch (sys_arg.ui_led_mode)
    {
    case UI_LED_OFF:
        LED_RED_POW_ON;
        LED_BLUE_POW_OFF;
        LED_RED_CONT_OFF;
        LED_BLUE_CONT_OFF;
        LED_RED_PULSE_OFF;
        LED_BLUE_PULSE_OFF;

       
        break;
    case UI_LED_ALARM:
        timer++;
        if (timer == 1)
        {
            LED_RED_POW_ON;
        }
        else if (timer == 15)
        {
            LED_RED_POW_OFF;
        }  
        else if (timer == 30)
        {
            LED_RED_POW_ON;
        }
        else if (timer == 45)
        {
            LED_RED_POW_OFF;
        }
        else if (timer == 60)
        {
            LED_RED_POW_ON;
        }
        else if (timer == 75)
        {
            LED_RED_POW_OFF;
            timer = 0;
            sys_arg.ui_led_mode = UI_LED_OFF;
        }

        break;
    case UI_LED_NORMAL: 
        timer_blink++;
        LED_RED_POW_ON;
        switch(sys_arg.mode)
        {
        case MODE_CONTINUE:
            LED_RED_PULSE_OFF;
            LED_BLUE_PULSE_OFF;
            switch (sys_arg.run_step)
            {
            case step1:
                LED_RED_CONT_OFF;
                break;
            case step2:
                LED_BLUE_CONT_OFF;
                break;
            case step3:
                LED_BLUE_CONT_OFF;
                break;
            }
            if (timer_blink < 500 / 10)  
            {
                switch(sys_arg.run_step)
                {
                    case step1:
                        LED_BLUE_CONT_OFF;
                        break;
                    case step2:
                        LED_RED_CONT_ON;
                        break;
                    case step3:
                        LED_RED_CONT_OFF;
                        break;
                }
                
            }
            else if (timer_blink < 1000 / 10)
            {
                switch (sys_arg.run_step)
                {
                case step1:
                    LED_BLUE_CONT_ON;
                    break;
                case step2:
                case step3:
                    LED_RED_CONT_ON;
                    break;
                }
            }
            else
            {
                timer_blink = 0;
            }
            break;
        case MODE_HALT:
            LED_BLUE_CONT_ON;
            LED_BLUE_PULSE_ON;

            LED_RED_CONT_OFF;
            LED_RED_PULSE_OFF;
            break;
        case MDDE_PULSED:
            LED_RED_CONT_OFF;
            LED_BLUE_CONT_OFF;
            switch(sys_arg.run_step)
            {
                case step1:
                    LED_RED_PULSE_OFF;
                    break;
                case step2:
                    LED_BLUE_PULSE_OFF;
                    break;
                case step3:
                    LED_BLUE_PULSE_OFF;
                    break;
            }
            if(timer_blink < 500/10)
            {
                switch(sys_arg.run_step)
                {
                    case step1:
                        LED_BLUE_PULSE_OFF;
                        break;
                    case step2:
                        LED_RED_PULSE_ON;
                        break;
                    case step3:
                        LED_RED_PULSE_OFF;
                        break;
                }
            }
            else if(timer_blink < 1000/10)
            {
                switch (sys_arg.run_step)
                {
                case step1:
                    LED_BLUE_PULSE_ON;
                    break;
                case step2:
                case step3:
                    LED_RED_PULSE_ON;
                    break;
                }
            }
            else
            {
                timer_blink = 0;
            }
            break;
        }
        break;
    default:
        break;
    }
}


