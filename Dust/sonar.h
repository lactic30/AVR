#ifndef SONAR_H_
#define SONAR_H_

#include "lcd.h"
#include <avr/interrupt.h>

/*********************PIN CONFIGURATION******************************/
#define TRIG_DDRD DDRD
#define TRIG_PORT PORTD
#define TRIG_PIN PIND
#define TRIG_BIT PD0

#define ECHO_DDRD DDRD
#define ECHO_PORT PORTD
#define ECHO_PIN PIND
#define ECHO_BIT PD1

/****************OTHER PARAMETER**********************************/
// 343 meters per second in dry air at room temperature (~20C)
#define SPEED_OF_SOUND 343
#define MAX_SONAR_RANGE 10
#define DELAY_BETWEEN_TEST 500
#define TIMER_MAX 65535 // 255

/**********************ERRORDEFINATION*************************************/

#define TRIG_ERROR -1
#define ECHO_ERROR -2

/***************************DELAY DEFINATION*****************************/

#define CYCLES_PER_US (F_CPU / 1000000) // instructions per microsecond
#define CYCLES_PER_MS (F_CPU / 1000)    // instructions per millisecond

/******************************************************************/
#define SONAR_TIMEOUT ((F_CPU * MAX_SONAR_RANGE) / SPEED_OF_SOUND)

#define TRIG_INPUT_MODE() TRIG_DDRD &= ~(1 << TRIG_BIT)
#define TRIG_OUTPUT_MODE() TRIG_DDRD |= (1 << TRIG_BIT)
#define TRIG_LOW() TRIG_PORT &= ~(1 << TRIG_BIT)
#define TRIG_HIGH() TRIG_PORT |= (1 << TRIG_BIT)

#define ECHO_INPUT_MODE() ECHO_DDRD &= ~(1 << ECHO_BIT)
#define ECHO_OUTPUT_MODE() ECHO_DDRD |= (1 << ECHO_BIT)
#define ECHO_LOW() ECHO_PORT &= ~(1 << ECHO_BIT)
#define ECHO_HIGH() ECHO_PORT |= (1 << ECHO_BIT)

#define CONVERT_TO_CM ((10000 * 2) / SPEED_OF_SOUND) // simply 58

/*********************************************************************/
/** ...- . . .-. --- -... --- -
 * @brief   Initiate Ports for Trigger and Echo pins
 * @param   void
 * @return  none
 */
void init_sonar();

/**  ...- . . .-. --- -... --- -
 * @brief   Send 10us pulse on Ultrasonic Trigger pin
 * @param   void
 * @return  none
 */
void trigger_sonar();

/**  ...- . . .-. --- -... --- -
 * @brief   Calculate and store echo time and return distance
 * @param   void
 * @return  unsigned int
 * Usage    int foo = read_sonar();
 */
int read_sonar(void);
/******************************FUNCTION THE END*******************************/
/***********************FUNCTIONS DEFINATIONS************************/

volatile uint32_t overFlowCounter = 0;
volatile uint32_t trig_counter = 0;
volatile uint32_t no_of_ticks = 0;

void init_sonar() {
  TRIG_OUTPUT_MODE(); // Set Trigger pin as output
  ECHO_INPUT_MODE();  // Set Echo pin as input
}

void trigger_sonar() {
  TRIG_LOW();    // Clear pin before setting it high
  _delay_us(1);  // Clear to zero and give time for electronics to set
  TRIG_HIGH();   // Set pin high
  _delay_us(15); // Send high pulse for minimum 15us
  TRIG_LOW();    // Clear pin
  _delay_us(1);
}

ISR(TIMER1_OVF_vect) { // Timer1 overflow interrupt
  overFlowCounter++;
  TCNT1 = 0;
}
int read_sonar(void) {
  int dist_in_cm = 0;
  init_sonar();    // Setup pins and ports
  trigger_sonar(); // send a 15us high pulse

  while (!(ECHO_PIN & (1 << ECHO_BIT))) { // while echo pin is still low
    trig_counter++;
    uint32_t max_response_time = SONAR_TIMEOUT;
    if (trig_counter > max_response_time) { // SONAR_TIMEOUT
      return TRIG_ERROR;
    }
  }

  TCNT1 = 0;             // reset timer
  TCCR1B |= (1 << CS10); // start 16 bit timer with no prescaler
  TIMSK |= (1 << TOIE1); // enable overflow interrupt on timer1
  overFlowCounter = 0;   // reset overflow counter
  sei();                 // enable global interrupts

  while ((ECHO_PIN & (1 << ECHO_BIT))) { // while echo pin is still high
    if (((overFlowCounter * TIMER_MAX) + TCNT1) > SONAR_TIMEOUT) {
      return ECHO_ERROR; // No echo within sonar range
    }
  }
  TCCR1B = 0x00; // stop 16 bit timer with no prescaler
  cli();         // disable global interrupts
  no_of_ticks = ((overFlowCounter * TIMER_MAX) + TCNT1); // counter count
  dist_in_cm =
      (no_of_ticks / (CONVERT_TO_CM * CYCLES_PER_US)); // distance in cm
  return (dist_in_cm);
}
/*****************************************************************************/
#endif /* SONAR_H_ */
