#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRA &= ~(0xFE);
  PORTA |= 0xFF;
  /* Replace with your application code */
  while (1) {
    if (PINA== 0xFF) {
      DDRB = 0xFF;
      PORTB = 0xFF;

    } else {
      PORTB = 0x00;
    }
  }
  return 0;
}
