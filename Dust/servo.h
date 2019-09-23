
/*
 * SERVO WORKS ON PWM WITH 50Hz FREQUENCY
 * In this file all timers(TIMER0,TIMER1,TIMER2) Initializating
 * All timers are working in FAST PWM mode
 * Timer0 value must exits between 1 to 9 (according to setting)
 * Timer1 value must exits between 19500 to 17500 and F_CPU become 1000000(according to setting)
 * Timer2 value must exits between 3 to 19 (according to setting)
 */

#include <avr/io.h>
#include <util/delay.h>

void TimerInit(uint8_t a);
void SetOutput(uint8_t b, uint8_t duty);

/*
 * Timer Initializing
 * A = Timer value (TIMER0 =1,Timer1 =2,Timer =3)
 */
void TimerInit(uint8_t a) {
  if (a == 1) {
    // Fast PWM mode; Prescaler 256; Non-inverted PWM
    TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (0 << CS00) |
             (0 << CS01) | (1 << CS02);
    // Set OC0 PIN as output. It is  PB3 on ATmega16/ATmega32
    DDRB |= (1 << PB3);
  } else if (a == 2) {

    TCCR1A |= 1 << WGM11 | 1 << COM1A1 | 1 << COM1A0;
    TCCR1B |= 1 << WGM13 | 1 << WGM12 | 1 << CS10;
    ICR1 = 19999;
    // Set OC1 PIN as output. It is  PD5 on ATmega16/ATmega32
    DDRD |= (1 << PD5);
  } else if (a == 3) {
    // Fast PWM mode; Prescaler 128; Non-inverted PWM
    TCCR2 |= (1 << WGM20) | (1 << COM01) | (1 << WGM21) | (1 << CS22) |
             (0 << CS21) | (1 << CS20);
    // Set OC2 PIN as output. It is  PD7 on ATmega16/ATmega32
    DDRD |= (1 << PD7);
  }
}

/*
 * Set OCR with timer value
 * Duty = Required duty cycle for InitPWM
 * B    = Timer value (TIMER0 =1,Timer1 =2,Timer =3)
 */
void SetOutput(uint8_t b, uint8_t duty) {
  if (b == 1) {
    OCR0 = duty;
  } else if (b == 2) {
    OCR1A = duty;
  } else if (b == 3) {
    OCR2 = duty;
  }
}
