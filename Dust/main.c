/*LCD Interfacing
 *LCD_RS PORTD2
 *LCD_EN PORTD3
 *LCD_D4 PORTD4
 *LCD_D5 PORTD5
 *LCD_D6 PORTD6
 *LCD_D7 PORTD7
 */

/*Ultrasonic Interfacing
 *SONIC_TRIG PORTD0
 *SONIC_ECHO PORTD1
 */

/*PIR Interfacing
 *PIR SENSOR PORTA0
 */

/*SERVO Interfacing
 *SERVO SIGNAL PORTB3
 */

/*INDICATION LED
 *DUSTBIN FULL LED PORTB0
 */
#include "servo.h"
#include "sonar.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
  DDRD = 0xFD;         // LCD AND ULTRASONIC
  DDRA &= ~(1 << PA0); // PIR SENSOR
  // DDRB |= (1 << PB0);  // FULL LED
  DDRC = 0xF7;
  int distance_cm = 0;
  /*****************SERVO PINS ALREADY MENTION IN SERVO.h********************/
  Lcd4_Init();
  _delay_us(1000);
  Lcd4_Clear();
  Lcd4_Write_String("HI SYSTEM");
  _delay_ms(500);
  Lcd4_Clear();
  TimerInit(1);
  SetOutput(1, 1);
  while (1) {
    distance_cm = read_sonar();
    Lcd4_Set_Cursor(2, 1);
    Lcd4_put_int(distance_cm);
    if (bit_is_set(PINA, 0)) {
      if (distance_cm <= 4) {
        SetOutput(1, 1);
        Lcd4_Set_Cursor(1, 1);
        Lcd4_Write_String("FULL");
        Lcd4_Set_Cursor(2, 1);
        Lcd4_put_int(distance_cm);
        PORTC = 0xC0;
      } else {
        SetOutput(1, 6);
        PORTC = 0xFF;
        Lcd4_Clear();
      }
    } else if (bit_is_clear(PINA, 0)) {
      SetOutput(1, 1);
      PORTC = 0x00;
      Lcd4_Clear();
    }
  }
  return 0;
}
