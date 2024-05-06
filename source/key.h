#ifndef _KEY_H
#define _KEY_H

#include "main.h"

#define KEY_NUM_MAX 3
#define ISCHARGING() (!_pa3)   //pb0 �����0 δ��� 1
#define ISFULL()   (!_pb1)

typedef struct 
{
    unsigned char long_press : 1;
    unsigned char short_press : 1;
    unsigned char three_press : 1;
    unsigned char flag_short_press : 1;
    unsigned char lock : 1;
    unsigned char null : 3;
    unsigned char timer;
    unsigned char timer_interval;
    unsigned char count_press;
} key_cb_T ;
extern key_cb_T key_cb[KEY_NUM_MAX];

enum
{
    KEY_ONOFF = 0,  
    KEY_PULSE,
    KEY_CONTINUE,

};

#define KEY_IO(i)      \
    (          \
    {                  \
        u8 io = 0;     \
        switch (i)     \
        {              \
        case 0:        \
            io = _pa5; \
            break;     \
        case 1:        \
            io = _pa6; \
            break;     \
        case 2:        \
            io =_pa3;    \
            break;     \
        default:       \
            break;     \
        }              \
        io;          \
    } )                 
     
    


void task_key(void);
void key_init(void);

#endif

