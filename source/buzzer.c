#include "buzzer.h"


T_buzzer_status buzzer_status = BEEP_IDLE;
void buzzer_init(u16 ccra,u16 ccrp)
{
    BEEP_OFF;
    _ptpau = 0;
    //fsys /4
    _ptck0  = 0;
    _ptck1  = 0;
    _ptck2  = 0;
    //工作模式
    _ptm1 = 1;
    _ptm0 = 0;
    //输出模式
    _ptio1 = 1;
    _ptio0 = 0;
    
    //IO配置
    _pa7 = 0;
    _pac7 = 0;

    _pas16 = 0;
    _pas17 = 1;
    //输出极性
    _ptoc = 0;
    _ptpol = 0;
    //设置比较值
    _ptmal = ccra & 0x00ff;
    _ptmah = ccra >> 8; 
    //设置周期
    _ptmrpl = ccrp & 0x00ff;
    _ptmrph = ccrp >> 8;

    _ptcclr = 1;
    //使能
    _pton = 0;


}

void task_buzzer(void)
{
    
    static u16 timer = 0;
    static u16 timer_task = 0;
    switch (buzzer_status)
    {
    case BEEP_THREE:
        if (timer)
        {
            BEEP_LED_ON;
            timer--;
        }
        else
        {
            BEEP_LED_OFF;
        }
        break;
    default:
        if (timer)
        {
            BEEP_ON;
            timer--;
        }
        else
        {
            BEEP_OFF;
        }
        break;
    }

    if (1 && sys_cmd.cmd_beep_long)
    {
        sys_cmd.cmd_beep_long = 0;
        BEEP_ON;
        buzzer_status = BEEP_LONG;
        
        timer = 1000 / TIME_TASK_BUZZER_CALL;
    }

    if (1 && sys_cmd.cmd_beep_short1)
    {
        sys_cmd.cmd_beep_short1 = 0;
        BEEP_ON;
        buzzer_status = BEEP_SHORT1;
        
        timer = 150 / TIME_TASK_BUZZER_CALL;
    }

    if (1 && sys_cmd.cmd_beep_short2)
    {
        sys_cmd.cmd_beep_short2 = 0;
        BEEP_ON;
        buzzer_status = BEEP_SHORT2;
        timer = 300 / TIME_TASK_BUZZER_CALL;
    }

    if (1 && sys_cmd.cmd_beep_short3)
    {
        
        sys_cmd.cmd_beep_short3 = 0;
        BEEP_ON;
        buzzer_status = BEEP_SHORT3;
        timer = 450 / TIME_TASK_BUZZER_CALL;
    }

    if (1 && sys_cmd.cmd_beep_two)
    {
        sys_cmd.cmd_beep_two = 0;
        BEEP_ON;
        buzzer_status = BEEP_TWO;
        
        timer_task = 0;
    }

    if (1 && sys_cmd.cmd_beep_three)
    {
        sys_cmd.cmd_beep_three = 0;
        BEEP_ON;
        buzzer_status = BEEP_THREE;
        
        timer_task = 0;
    }

    timer_task++;

    switch(buzzer_status)
    {
    case BEEP_IDLE:
        timer = 0;
        break;
    case BEEP_LONG:
    case BEEP_SHORT1:
    case BEEP_SHORT2:
    case BEEP_SHORT3:
        if(timer == 0)
            buzzer_status = BEEP_IDLE;
        break;
    case BEEP_TWO:
        if(timer_task <= 150/TIME_TASK_BUZZER_CALL)
        {
            timer = 1;
        }
        else if (timer_task <= 300 / TIME_TASK_BUZZER_CALL)
        {
            timer = 0;
        }
        else if (timer_task <= 450/ TIME_TASK_BUZZER_CALL)
        {
            timer = 1;
        }
        else
        {
            timer = 0;
            buzzer_status = BEEP_IDLE;
        }
        break;
    case BEEP_THREE:
        if (timer_task <= 150 / TIME_TASK_BUZZER_CALL)
        {
            BEEP_ON;
            timer = 1;
        }
        else if (timer_task <= 300 / TIME_TASK_BUZZER_CALL)
        {
            timer = 0;
        }
        else if (timer_task <= 450 / TIME_TASK_BUZZER_CALL)
        {
            BEEP_ON;
            timer = 1;
        }
        else if (timer_task <= 600 / TIME_TASK_BUZZER_CALL)
        {
            timer = 0;
        }
        else if (timer_task <= 750 / TIME_TASK_BUZZER_CALL)
        {
            BEEP_ON;
            timer = 1;
        }
        else
        {
            timer = 0;
            buzzer_status = BEEP_IDLE;
        }
        break;
    }
}




