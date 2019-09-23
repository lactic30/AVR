#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRA = 0x00; // PIR SENSOR DIRECTION PORT
  DDRB = 0xFF; // LED OUTPORT DIRECTION PORT
  /* Replace with your application code */
  while (1) {
    PORTB = 0x00;
    if (bit_is_clear(PINA, 0)) {
      PORTB = 0x00;
    } else if (bit_is_set(PINA, 0)) {
      PORTB = 0xFF;
      _delay_ms(100);
      PORTB = 0x00;
    }
  }
  return 0;
}
