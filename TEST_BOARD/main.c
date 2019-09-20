/*
 *
 * Created(PORTING DATE): 9/19/2019 18:22:36
 * Author : LACTIC
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  /*  DDRA |= (1 << 4); // DDRA &= ~(1<<4);*/
  DDRC = 0xFF;
  PORTC = 0x00;
  DDRD = 0xFF;
  PORTD = 0x00;
  /* Replace with your application code */
  while (1) {
    PORTC |= 0xFF;
    PORTD |= 0xFF;
    _delay_ms(100);
    PORTC |= 0x00;
    PORTD |= 0x00;
    _delay_ms(100);
  }
}
