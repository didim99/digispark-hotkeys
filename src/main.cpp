#include "main.h"

btnState btn;
btnEvent event;

void setup() {
  event.counter = 0;
  event.lastTime = 0;
  btn.lastTime = 0;
  btn.currState = HIGH;
  btn.lastState = HIGH;
  btn.trig = HIGH;

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BTN_GND, OUTPUT);
  digitalWrite(BTN_GND, LOW);
  pinMode(BTN_PIN, INPUT_PULLUP);

  DigiKeyboard.println("HELLO");
}

void loop() {
  buttonRead();
  event_t evt = buttonEvent();  

  switch (evt) {
    case SINGLE_CLICK:
      DigiKeyboard.sendKeyStroke(KEY_1, MOD_ALL);
      break;
    case DOUBLE_CLICK:
      DigiKeyboard.sendKeyStroke(KEY_2, MOD_ALL);
      break;
    case TRIPLE_CLICK:
      DigiKeyboard.sendKeyStroke(KEY_3, MOD_ALL);
      break;
    case HOLD_SHORT:
      DigiKeyboard.sendKeyStroke(KEY_4, MOD_ALL);
      break;
    case HOLD_MEDIUM:
      DigiKeyboard.sendKeyStroke(KEY_5, MOD_ALL);
      break;
    case HOLD_LONG:
      DigiKeyboard.sendKeyStroke(KEY_6, MOD_ALL);
      break;
  }
}

void buttonRead() {
  btn.trig = btn.currState;
  register uint8_t tmpState = digitalRead(BTN_PIN);
  if (btn.currState != tmpState) {
    delay(TRIG_DELAY);
    if (tmpState == digitalRead(BTN_PIN))
      btn.currState = tmpState;
  }

  if (btn.currState != btn.lastState) {
    if (btn.currState == BTN_ACT) {
      btn.lastTime = millis();
      btn.pressTime = 0;
      btn.trig = RISING;
    } else {
      btn.pressTime = millis() - btn.lastTime;
      btn.trig = FALLING;
    }
  }

  btn.lastState = btn.currState;
}

event_t buttonEvent() {
  if (btn.trig == BTN_INACT) {
    int16_t delay = millis() - event.lastTime;
    if (delay < CLICK_DELAY)
      return NO_EVENTS;

    register uint8_t counter = event.counter;
    event.lastTime = 0;
    event.counter = 0;

    switch (counter) {
      case 0:
        return NO_EVENTS;
      case 1:
        return SINGLE_CLICK;
      case 2:
        return DOUBLE_CLICK;
      default:
        return TRIPLE_CLICK;
    }
  }
  
  if (btn.trig != FALLING)
    return NO_EVENTS;

  if (btn.pressTime > DELAY_SHORT) {
    event.lastTime = 0;
    event.counter = 0;

    if (btn.pressTime > DELAY_LONG)
      return HOLD_LONG;
    if (btn.pressTime > DELAY_MEDIUM)
      return HOLD_MEDIUM;
    return HOLD_SHORT;
  }

  event.lastTime = millis();
  event.counter++;

  if (event.counter >= 3) {
    event.counter = 0;
    return TRIPLE_CLICK;
  }
  
  return NO_EVENTS;
}
