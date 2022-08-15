#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include"macros.h"
volatile uint8_t current_speed=0;
volatile uint8_t current_timer=0;
volatile int check=0;

void timer0_init(unsigned int set_value)
{
	SET_BIT(DDRB,PB3);
	TCNT0=0;
	OCR0=set_value;
	SET_BIT(TCCR0,WGM00);
    SET_BIT(TCCR0,COM01);
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,CS00);
//	we used timer 0 for PWM as follows :
//			  1-phase correction mode by setting WGM00 and clearing WGM01
//			  2-no prescaler set CS00
//			  3-non-inverting pwm by setting on compare match
}
void timer0_pause_init(void)
{
	SET_BIT(DDRB,PB3);
	TCNT0=0;
	CLEAR_BIT(TCCR0,CS00);
//	we used timer 0 for PWM as follows :
//			  1-phase correction mode by setting WGM00 and clearing WGM01
//			  2-no prescaler set CS00
//			  3-non-inverting pwm by setting on compare match
}

void motor_start_init(void)
{
	SET_BIT(DDRB,PB0);
	SET_BIT(DDRB,PB1);
	SET_BIT(PORTB,PB1);
	CLEAR_BIT(PORTB,PB0);
//	Pin 4 and 5 in port c is used to control the motor:
//	1-PINC4 is cleared and PINC5 IS SET to allow clockwise movement
//
}
 void motor_stop_init(void)
 {
	 CLEAR_BIT(PORTB,PB0);
	 CLEAR_BIT(PORTB,PB1);
 }

 void seven_seg_init(void)
 {
	 DDRC=0xFF;
	 SET_BIT(DDRD,PD0);
	 SET_BIT(DDRD,PD1);
	 SET_BIT(PORTD,PD0);
	 SET_BIT(PORTD,PD1);
	 PORTC=0;

 }


int main(void)
{
	DDRA=0x00;
	PORTA|=0XFF;
	seven_seg_init();
	timer0_pause_init();
	while(1)
	{
		PORTC=current_speed;
		if(!(PINA&(1<<PA2)))
		{
			if(CHECK_IF_CLEAR(PORTB,PB1)))
			{
			motor_start_init();
			}
			else if(CHECK_IF_SET(PORTB,PB1))
			{
				motor_stop_init();
				current_speed=0;
			}
		}
		PORTC=current_speed;
		if(!(PINA&(1<<PA3)))  //speed 1
		{
			timer0_init(128);
			current_speed=1;
		}
		if(!(PINA&(1<<PA4)))  //speed 2
		{
			timer0_init(64);
			current_speed=2;
		}
		if(!(PINA&(1<<PA5)))  //speed 3
		{
			timer0_init(5);
			current_speed=3;
		}




	}

}



