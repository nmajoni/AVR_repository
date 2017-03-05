/*
 * ADC.c
 * ATMEGA 2560
 * Created: 25-Feb-17 16:39:22
 * Author : nyasha majoni
 */ 

#include <avr/io.h>

void adc_init()
{
	ADMUX   |= (1u << REFS0); //AVCC with external capacitor at AREF pin. I am going to use ADC0 
	ADCSRA  |= (1u << ADEN)|(1u << ADPS0)|(1u << ADPS1)|(1u << ADPS2); //Enable ADC and set prescale of 128 so 125000Hz
}

uint16_t adc_val()
{
	ADCSRA |= (1u << ADSC);       //Start conversion
	while(ADCSRA & (1u << ADSC)); //Wait for conversion to complete. Avoid this for production grade code. Interrupts are better
	return (ADC);	
}

int main(void)
{
   volatile uint16_t adc_result;
   adc_init();
	
    while (1) 
    {
	adc_result = adc_val();  
    }
}

