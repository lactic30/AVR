#include "lcd.h"

int main(void) {
  DDRD = 0xFF;

  /* Replace with your application code */
  Lcd4_Init();
  _delay_ms(900);
  Lcd4_Clear();

  while (1) {

    Lcd4_Set_Cursor(1, 0);
    Lcd4_Write_String("ASTUTGEN");
    Lcd4_Set_Cursor(2, 0);
    Lcd4_Write_String("STHAN");
    _delay_ms(1000);
    Lcd4_Clear();
    Lcd4_Set_Cursor(1, 0);
    Lcd4_Write_String("ALPHA");
    Lcd4_Set_Cursor(2, 0);
    Lcd4_Write_String("DUSTBIN v 0.0");
    _delay_ms(1000);
    Lcd4_Clear();
  }
}
