#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include"macros.h"
volatile uint8_t current_speed=0;
volatile uint8_t current_timer=0;
volatile int check=0;
volatile int hour=0;
volatile int timer=0;
volatile int minute=0;
volatile int second=0;
volatile int count=0;
volatile int timer_en=0;

ISR(INT0_vect)
{
	CLEAR_BIT(MCUCR,SE);
}
ISR(TIMER2_OVF_vect)
{
	count++;
	if(count==4)
	{
		second++;
		if(second==60)
		{
			second=0;
			minute++;
		}
		if(minute==60)
		{
			minute=0;
			second=0;
			hour++;
		}
		count=0;
	}
}
void timer2_init(void)
{
	TCNT2=0;
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	SET_BIT(TIMSK,TOIE2);
	SREG|=(1<<7);
}
void timer2_disable(void)
{
	CLEAR_BIT(TCCR2,CS20);
	CLEAR_BIT(TCCR2,CS21);
	CLEAR_BIT(TCCR2,CS22);
	CLEAR_BIT(TIMSK,TOIE2);
}
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

 void sleep_init(void)
 {
	 SET_BIT(MCUCR,SM1);
 }

 void INT0_init(void)
 {
	 SET_BIT(MCUCR,ISC01);
	 SET_BIT(GICR,INT0);
	 SET_BIT(SREG,7);
	 CLEAR_BIT(DDRD,PD2);
	 SET_BIT(PORTD,PD2);
 }

int main(void)
{
	DDRA=0x00;
	PORTA|=0XFF;
	seven_seg_init();
	timer0_pause_init();
//	INT0_init();
	sleep_init();
	while(1)
	{
		current_timer=timer-second;

		PORTD=0;
		SET_BIT(PORTD,PD0);
		if(current_speed==0)
		{
			PORTC=127;
		}
		else
		{
		PORTC=current_speed;
		if(current_speed==1)
		{
			SET_BIT(PORTC,PC7);
		}
		}
		_delay_ms(20);
		PORTD=0;
		SET_BIT(PORTD,PD1);
		if(check==1)
		{
			PORTC=current_timer;
			if(current_timer==2||current_timer==3||current_timer==5||current_timer==6||current_timer==8||current_timer==9)
			{
				CLEAR_BIT(PORTC,PC7);
			}
			else
				SET_BIT(PORTC,PC7);
		_delay_ms(20);
		}
		if(check==0)
		{
			PORTC=127;
			_delay_ms(20);
		}
		if(timer-second==0&&check==1)
		{
			motor_stop_init();
			timer2_disable();
			check=0;
			current_speed=0;
			current_timer=0;
			timer=0;
			second=0;
		}
		if(!(PINA&(1<<PA2)))
		{
			if(CHECK_IF_CLEAR(PORTB,PB1)))
			{
				_delay_ms(250);
				motor_start_init();
				if(timer>0)
				{
					timer2_init();
				}
				else
				{
					timer2_disable();
					second=0;
				}
			}
			else if(CHECK_IF_SET(PORTB,PB1))
			{
				_delay_ms(250);
				motor_stop_init();
				timer2_disable();
			}
		}
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
		if(!(PINA&(1<<PA6)))  //timer setting
		{
			if(timer<9)
			{
			_delay_ms(250);
			timer++;
			check=1;
			}
			else
			{
				timer=0;
			_delay_ms(250);
			check=0;
			}

		}


	}

}



