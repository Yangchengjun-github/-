#include "led.h"

struct
{
    unsigned int const period_breath;
    unsigned int timer;
    unsigned char output;
    unsigned char dir;
    enum
    {
        breath0 = 0,
        breath1,
        breath2,
        breath3,
        breath4,

    } state;

} breath_CB =
    {
        2500,
        0,
        0,
        1,

};

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
    _pa0 = 1;
    _pac0 = 0;
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
        LED1_ON;
        LED2_OFF;
        LED3_OFF;
        LED4_OFF;
        LED5_OFF;
        LED6_OFF;
        break;
    case UI_LED_ALARM:
        timer++;
        if (timer == 1)
        {
            LED1_ON;
        }
        else if (timer == 15)
        {
            LED1_OFF;
        }  
        else if (timer == 30)
        {
            LED1_ON;
        }
        else if (timer == 45)
        {
            LED1_OFF;
        }
        else if (timer == 60)
        {
            LED1_ON;
        }
        else if (timer == 75)
        {
            LED1_OFF;
            timer = 0;
            sys_arg.ui_led_mode = UI_LED_OFF;
        }

        break;
    case UI_LED_NORMAL: 
        timer_blink++;
        switch(sys_arg.mode)
        {
        case MODE_CONTINUE:
            LED3_OFF;
            LED4_ON;
            switch (sys_arg.run_step)
            {
            case step1:
                LED5_OFF;
                break;
            case step2:
                LED6_OFF;
                break;
            case step3:
                LED6_OFF;
                break;
            }
            if (timer_blink < 500 / 10)  
            {
                switch(sys_arg.run_step)
                {
                    case step1:
                        LED6_OFF;
                        break;
                    case step2:
                        LED5_ON;
                        break;
                    case step3:
                        LED5_OFF;
                        break;
                }
                
            }
            else if (timer_blink < 1000 / 10)
            {
                switch (sys_arg.run_step)
                {
                case step1:
                    LED6_ON;
                    break;
                case step2:
                case step3:
                    LED5_ON;
                    break;
                }
            }
            else
            {
                timer_blink = 0;
            }
            break;
        case MODE_HALT:
            LED4_ON;
            LED6_ON;
            break;
        case MDDE_PULSED:
            LED6_ON;
            LED5_OFF;
            switch(sys_arg.run_step)
            {
                case step1:
                    LED3_OFF;
                    break;
                case step2:
                    LED4_OFF;
                    break;
                case step3:
                    LED4_OFF;
                    break;
            }
            if(timer_blink < 500/10)
            {
                switch(sys_arg.run_step)
                {
                    case step1:
                        LED4_OFF;
                        break;
                    case step2:
                        LED3_ON;
                        break;
                    case step3:
                        LED3_OFF;
                        break;
                }
            }
            else if(timer_blink < 1000/10)
            {
                switch (sys_arg.run_step)
                {
                case step1:
                    LED4_ON;
                    break;
                case step2:
                case step3:
                    LED3_ON;
                    break;
                }
            }
            else
            {
                timer_blink = 0;
            }
            break;
        }
        LED1_ON;
        break;
    default:
        break;
    }
}


void breath(void)
{
    if(breath_CB.state == breath0)
    {
        breath_CB.timer = 0;
        return;
    }
    breath_CB.timer++;
    if(breath_CB.timer >= 2500)//breath_CB.period_breath)
    {
        breath_CB.timer = 0;
        breath_CB.dir = !breath_CB.dir;
    }
    if (breath_CB.timer % 15 > breath_CB.timer / 100 )
    {
        breath_CB.output = breath_CB.dir ? 1 : 0;
    }
    else
    {
        breath_CB.output = breath_CB.dir ? 0 : 1;
    }
    // if (breath_CB.output)
    // {
    //     LED1_ON;
    // }
    // else
    // {
    //     LED1_OFF;
    // }
    //     LED2_OFF;
    //     LED3_OFF;
    switch(breath_CB.state)
    {
    case breath1 :
        if(breath_CB.output)
        {
            LED1_ON;
        }
        else
        {
            LED1_OFF;
        }

        LED2_OFF;
        LED3_OFF;
        break;
    case breath2:
        if (breath_CB.output)
        {
            LED2_ON;
        }
        else
        {
            LED2_OFF;
        }

        LED1_ON;
        LED3_OFF;
        break;
    case breath3:
        if (breath_CB.output)
        {
            LED3_ON;
        }
        else
        {
            LED3_OFF;
        }

        LED1_ON;
        LED2_ON;
        break;
    case breath4:
        LED1_ON;
        LED2_ON;
        LED3_ON;
        break;
    default :
    	break;
    }

}