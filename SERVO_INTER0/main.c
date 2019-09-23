#include "servo.h"

int main(void) {
  TimerInit(3);
  while (1) {
    for (int i = 3; i <= 19; i++) {
      SetOutput(3, i);
      _delay_ms(60);
    }
  }
  return 0;
}
