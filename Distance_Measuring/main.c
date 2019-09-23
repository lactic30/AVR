/*
 * distance_measuring.c
 *
 * Created (PORTING DATE): 9/22/2019 22:07:31
 * Author : LACTIC
 */
//#include "lcd.h"
#include "sonar.h"

int main(void) {
  int distance_cm = 0;
  DDRD = 0xFD;
  /* Replace with your application code */
  Lcd4_Init();
  _delay_us(500);
  Lcd4_Clear();
  Lcd4_Write_String("HI SYSTEM");
  _delay_ms(500);
  Lcd4_Clear();
  while (1) {
    Lcd4_Clear();
    distance_cm = read_sonar();
    if (distance_cm == TRIG_ERROR) {
      Lcd4_Set_Cursor(1, 0);
      Lcd4_Write_String("TRIG ERROR!!!");
      _delay_ms(500 / 2);
      Lcd4_Clear();
      _delay_ms(500 / 2);
    } else if (distance_cm == ECHO_ERROR) {
      Lcd4_Set_Cursor(1, 0);
      Lcd4_Write_String("ECHO ERROR!!!!");
      _delay_ms(500 / 2);
      Lcd4_Clear();
      _delay_ms(500 / 2);
    } else {

      Lcd4_Set_Cursor(1, 0);
      Lcd4_Write_String("DISTANCE");
      Lcd4_Set_Cursor(2, 0);
      Lcd4_put_int(distance_cm);
      Lcd4_Set_Cursor(2, 9);
      Lcd4_Write_String("cm");
      _delay_ms(500);
    }
  }
}
