#include "key.h"

key_cb_T key_cb[KEY_NUM_MAX] = {{0}};

// 10MS 任务

void key_init(void)
{
    //key1
    _pac3 = 1;
    _papu3 = 1;
    //key2
    _pac6 = 1;
    _papu6 = 1;
    //key3
    _pac5 = 1;
    _papu5 = 1;
    
}
void task_key(void)
{
    u8 i = 0;
    for (i = 0; i < KEY_NUM_MAX; i++)
    {
        if (key_cb[i].timer_interval < 255)
            key_cb[i].timer_interval++;
        if (KEY_IO(i))
        {
            key_cb[i].lock = 0;
            key_cb[i].timer = 0;
            if (key_cb[i].flag_short_press)
            {

                if (key_cb[i].timer_interval < 100)
                {
                    key_cb[i].count_press++;
                }
                else
                {
                    key_cb[i].count_press = 1;
                }
                if (key_cb[i].count_press >= 5)
                {
                    key_cb[i].count_press = 0;
                    key_cb[i].three_press = 1;
                }
                key_cb[i].flag_short_press = 0;
                key_cb[i].short_press = 1;
                key_cb[i].timer_interval = 0;
            }
        }
        else if (!key_cb[i].lock)
        {
            key_cb[i].timer++;
            if (key_cb[i].timer > 2)
            {
                key_cb[i].flag_short_press = 1;
            }
            if (key_cb[i].timer > 200)
            {
                key_cb[i].long_press = 1;
                key_cb[i].flag_short_press = 0;
                key_cb[i].lock = 1;
            }
        }
    }
}