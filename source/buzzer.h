#ifndef _BUZZER_H
#define _BUZZER_H

#include "main.h"

#define TIME_TASK_BUZZER_CALL 10


#define BEEP_ON   _pton = 1

#define BEEP_OFF  _pton = 0

#define BEEP_LED_ON _pton = 1;

#define BEEP_LED_OFF _pton = 0;
typedef enum
{
    BEEP_IDLE,
    BEEP_LONG,
    BEEP_SHORT1,
    BEEP_SHORT2,
    BEEP_SHORT3,
    BEEP_TWO,
    BEEP_THREE,
    BEEP_THREE_LONG,
} T_buzzer_status;
extern T_buzzer_status buzzer_status;
void task_buzzer(void);
void buzzer_init(u16 ccra, u16 ccrp);
#endif

