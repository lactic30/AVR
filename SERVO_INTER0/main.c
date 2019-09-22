#include "servo.h"

int main(void) {
  TimerInit(1);
  while (1) {
    SetOutput(1, 1);
    _delay_ms(60);
    SetOutput(1, 5);
    _delay_ms(60);
    SetOutput(1, 9);
    _delay_ms(60);
    SetOutput(1, 5);
    _delay_ms(60);
  }
  return 0;
}
