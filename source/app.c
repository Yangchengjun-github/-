#include "app.h"


void task_app(void)
{
    static u16 timer_alarm = 0;
    static u16 timer_pulse = 0;
    static u16 timer_continue = 0;
    /* ---------------------------------- 开机键长按 ---------------------------------- */
    if(key_cb[KEY_ONOFF].long_press)
    {
        key_cb[KEY_ONOFF].long_press = 0;

    }
/* ---------------------------------- 开机键短按 ---------------------------------- */
    if (key_cb[KEY_ONOFF].short_press)
    {
        key_cb[KEY_ONOFF].short_press = 0;
        sys_cmd.cmd_beep_short1 = 1;
        switch (sys_arg.system_status)
        {
        case SYSTEM_POWOFF:
            if (sys_arg.ntc_err || sys_arg.ntc_high || sys_arg.voltage_err)
            {
                sys_cmd.cmd_powoff = 1;
                sys_cmd.cmd_beep_three = 1;
                sys_cmd.cmd_ui_alarm = 1;
            }
            else
            {
                sys_cmd.cmd_powon = 1;
            }
            break;
        case SYSTEM_POWON:
            sys_cmd.cmd_powoff = 1;        
            break;
        }
    }

/* ----------------------------------- 连续键短按 ---------------------------------- */
    if (key_cb[KEY_CONTINUE].short_press)
    {
        
        key_cb[KEY_CONTINUE].short_press = 0;
        
        sys_cmd.cmd_cntdown_reset = 1;
        switch (sys_arg.system_status)
        {
        case SYSTEM_POWOFF:
            break;
        case SYSTEM_POWON:
            sys_cmd.cmd_beep_short1 = 1;
            if(sys_arg.mode == MODE_CONTINUE)
            {
                sys_arg.mode = MODE_HALT;
            }
            else
            {
                sys_arg.mode = MODE_CONTINUE;
            }
            break;
        }
    }
/* ---------------------------------- 脉冲键短按 --------------------------------- */
    if (key_cb[KEY_PULSE].short_press)
    {
        
        key_cb[KEY_PULSE].short_press = 0;
        
        sys_cmd.cmd_cntdown_reset = 1;
        switch (sys_arg.system_status)
        {
        case SYSTEM_POWOFF:
            break;
        case SYSTEM_POWON:
            sys_cmd.cmd_beep_short1 = 1;
            if(sys_arg.mode == MDDE_PULSED)
            {
                sys_arg.mode = MODE_HALT;
            }
            else
            {
                sys_arg.mode = MDDE_PULSED;
            }
            break;
        }
    }

    /* ------------------------------- 开关机状态切换时执行一次 ------------------------------- */
    if (sys_cmd.cmd_powoff)
    {
        sys_cmd.cmd_powoff = 0;
        sys_arg.temperature_ok = 0;
        sys_arg.timer_autoShutdown = 0;
        sys_arg.system_status = SYSTEM_POWOFF;
        sys_cmd.cmd_ui_off = 1;
        
    }
    if (sys_cmd.cmd_powon)
    {
        sys_cmd.cmd_powon = 0;
        sys_arg.timer_autoShutdown = 0;
        sys_arg.system_status = SYSTEM_POWON;
        sys_cmd.cmd_ui_on = 1;
    }

    if(sys_cmd.cmd_cntdown_reset)
    {
        sys_cmd.cmd_cntdown_reset = 0;
        sys_arg.timer_autoShutdown = 0;
    }

    switch(sys_arg.system_status)
    {
    case SYSTEM_POWON:

        if (sys_arg.mode == MODE_HALT)
        {
            sys_arg.timer_autoShutdown = 0;
        }

        if(sys_arg.timer_autoShutdown == (20*60 -30))  //TODO 疑似内存范围出错
        {
            sys_arg.timer_autoShutdown = 0;
            sys_cmd.cmd_powoff = 1;        //自动关机
        }
        if(sys_arg.timer_autoShutdown == (18*60 -30))  //转红色闪烁
        {

            sys_arg.run_step = step3;
        }
        if (sys_arg.timer_autoShutdown == (17*60 -30))  //转红色
        {
            sys_arg.run_step = step2;
        }
        if (sys_arg.timer_autoShutdown < 3)
        {
            sys_arg.run_step = step1; 
        }

        if(sys_arg.run_step == step3)
        {
            timer_alarm++;
            if(timer_alarm > 10000 /10)
            {
                timer_alarm = 0;
                sys_cmd.cmd_beep_long = 1;
            }
        }
        else
        {
            timer_alarm = 0;
        }
        if( sys_arg.mode == MDDE_PULSED)
        {
            
            if(timer_pulse++ == 0)
            {
                valve_out();
            }
            if(timer_pulse == 3)
            {
                valve_out_pwm();

            }
            if(timer_pulse == 28)
            {
                valve_off();
            }
            if(timer_pulse == 60)
            {
                timer_pulse = 0;
            }
        }
        else
        {
            timer_pulse = 0;
        }

        if( sys_arg.mode == MODE_CONTINUE)
        {
            if (timer_continue++ == 0)
            {
                valve_out();
            }
            if (timer_continue == 7)
            {
                valve_out_pwm();
                
            }

            if(timer_continue > 10)  //防止溢出
            {
                timer_continue = 10;
            }
            
        }
        else
        {
            timer_continue = 0;
        }
        


        switch(sys_arg.mode)
        {
        case MODE_HALT:
            valve_off();
            MOTOR_POWOFF;
           // VALVE_POWOFF;
            break;
        case MODE_CONTINUE:
            MOTOR_POWON;
          //  VALVE_POWON;
            break;
        case MDDE_PULSED:
            MOTOR_POWON;
            // sys_arg.timer_pulsed++;
            // if(sys_arg.timer_pulsed <= 500 / 10)
            // {
            //     VALVE_POWON;
            // }
            // else if (sys_arg.timer_pulsed <= 1000 / 10)
            // {
            //     VALVE_POWOFF;
            // }
            // else
            // {
            //     sys_arg.timer_pulsed = 0;
            // }
            break;
        default:
            break;
        }
        if(sys_arg.ntc_err || sys_arg.ntc_high || sys_arg.voltage_err  )
        {
            sys_cmd.cmd_powoff = 1;
            sys_cmd.cmd_beep_three = 1;
            sys_cmd.cmd_ui_alarm = 1;
        }

        break;
    case SYSTEM_POWOFF:
        timer_pulse = 0;
        timer_continue = 0;
        MOTOR_POWOFF;
        VALVE_POWOFF;
        sys_arg.mode = MODE_HALT;
        sys_arg.timer_autoShutdown = 0;

        break;
    
    }
#if (LIMIT == 1)
    if(sys_arg.limit_timer >=  65535)
    {
        sys_arg.limit_timer = 65535;
        sys_cmd.cmd_powoff = 1;
    }
#endif 
}