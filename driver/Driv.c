#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include"macros.h"

void timer0_init(unsigned int set_value)
{
	TCNT0=0;
	OCR0=set_value;
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);
    SET_BIT(TCCR0,COM01);
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,CS00);
//	we used timer 0 for PWM as follows :
//			  1-phase correction mode
//			  2-no prescaler
//			  3-non-inverting pwm
}
