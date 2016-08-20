#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#define LED0_ON 0x0E
#define LED1_ON 0x0D
#define LED2_ON 0x0B
#define LED3_ON 0x07

#define ICREMENT_SEQUENCE PTAD_PTAD2 == 0 //an input pin to a switch
#define UPPER_LIMIT 4
#define LOWER_LIMIT 255

#define ENABLE_PULL_UP_R_PTA2 PTAPE_PTAPE2 = 1
#define ENABLE_PTB_0_TO_3_AS_OUTPUTS PTBDD =  0x0F
#define START_TIMER_512_MILLIS SRTISC = 0b00000110
#define START_TIMER_8_MILLIS SRTISC = 0b00000001
#define STOP_TIMER SRTISC = 0b00000000
#define SMALLEST_TIMER 8
#define TIMER_STILL_RUNNING SRTISC_RTIF == 0 //done flag is off
#define TIMER_ACKNOWLEDGE SRTISC_RTIACK = 1 //turns off done flag

unsigned char led_sequence[] = {LED0_ON, LED1_ON, LED2_ON, LED3_ON};

void delay_half_second(){
	START_TIMER_512_MILLIS ;
	do{
		__RESET_WATCHDOG();
	}while(TIMER_STILL_RUNNING);
	TIMER_ACKNOWLEDGE;
	STOP_TIMER;
}

void delay_ms(unsigned int time){
	unsigned int cycles = time / SMALLEST_TIMER;
	do{
		START_TIMER_8_MILLIS;
		do{
			__RESET_WATCHDOG();
		}while(TIMER_STILL_RUNNING);
		TIMER_ACKNOWLEDGE;
	}while(--cycles); /* a cycle is done */
	STOP_TIMER;
}


void main(void) {
	unsigned char led_index = 0; /* valid from 0 to 3 */
  EnableInterrupts;

  ENABLE_PTB_0_TO_3_AS_OUTPUTS;
  ENABLE_PULL_UP_R_PTA2;

  for(;;) {

		PTBD = led_sequence[led_index]; /* change the led that is on */
		delay_half_second(); /* leave led on for half a second */

		/* move led_index up or down */
		if(ICREMENT_SEQUENCE){
			led_index++;
			if(led_index == UPPER_LIMIT)
				led_index = 0;
		}else{
			led_index--;
			if(led_index == LOWER_LIMIT)
				led_index = 3;

		}
  }
}
