/*
 * PWM_fast.c
 *
 * Created: 25-Feb-17 12:18:00
 * Author : nyasha majoni
 */ 

#include <avr/io.h>
#include "avr/interrupt.h"
#include "util/delay.h"

void fast_pwm_init()
{
	TCCR0A |= (1u << COM0A1)|(1u << WGM01)|(1u << WGM00); //Non-inveting mode and fast PWM selected
	TCCR0B |= (1u << CS00); //no prescaller
}

int main(void)
{
    uint8_t brightness;
    DDRB |= (1u << PINB7); //set OC0A pin as output 
    fast_pwm_init();       
	
    while (1) 
    {
		/*Increasing and decreasing LED brightness*/
		for (brightness = 0; brightness < 255; brightness++)
		{
			OCR0A = brightness;
			_delay_ms(5);
		}
		for (brightness = 255; brightness > 0; brightness--)
		{
			OCR0A = brightness;
			_delay_ms(5);
		}
    }
}

