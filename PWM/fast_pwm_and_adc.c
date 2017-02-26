/*
 * Controlling the speed of a motor using a potentiometer.
 * Microcontroller used: ATMEGA 2560
 * Created: 26-Feb-17 12:18:00
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

void adc_init()
{
	ADMUX   |= (1u << REFS0); //AVCC with external capacitor at AREF pin. I am going to use ADC0
	ADCSRA  |= (1u << ADEN)|(1u << ADPS0)|(1u << ADPS1)|(1u << ADPS2); //Enable ADC and set prescale of 128 so 125000Hz
}

//get adc result
uint16_t adc_val()
{
	ADCSRA |= (1u << ADSC);       //Start conversion
	while(ADCSRA & (1u << ADSC)); //Wait for conversion to complete. Avoid this for production grade code. Interrupts are better
	return (ADC);
}

//main function
int main(void)
{
    DDRB |= (1u << PINB7); //set OC0A pin as output 
    fast_pwm_init();       
    adc_init();
	
    while (1) 
    { 
         OCR0A = adc_val()/4;  //maping (0 - 255) to (0 - 1023) 
    }
}

