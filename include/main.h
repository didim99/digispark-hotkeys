#ifndef _MAIN_H_
#define _MAIN_H_

#include <Arduino.h>
#include <DigiKeyboard.h>

#define MOD_ALL         MOD_CONTROL_LEFT | MOD_SHIFT_LEFT | MOD_ALT_LEFT | MOD_GUI_LEFT

#define BTN_GND         PB0
#define BTN_PIN         PB2
#define BTN_ACT         LOW
#define BTN_INACT       HIGH

#define TRIG_DELAY      20
#define CLICK_DELAY     200
#define DELAY_SHORT     500
#define DELAY_MEDIUM    1500
#define DELAY_LONG      5000

#define NO_EVENTS       0
#define SINGLE_CLICK    4
#define DOUBLE_CLICK    5
#define TRIPLE_CLICK    6
#define HOLD_SHORT      7
#define HOLD_MEDIUM     8
#define HOLD_LONG       9

typedef uint8_t trigger_t;
typedef uint8_t event_t;

typedef struct {
    uint32_t lastTime;
    uint32_t pressTime;
    uint8_t lastState;
    uint8_t currState;
    trigger_t trig;
} btnState;

typedef struct {
    uint32_t lastTime;
    uint8_t counter;
} btnEvent;

void buttonRead();
event_t buttonEvent();

#endif /* _MAIN_H_ */
