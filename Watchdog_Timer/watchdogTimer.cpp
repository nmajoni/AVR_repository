/*
 * watchdogTimer.cpp
 * A little program to set and test the watchdog timer on the Atmega328P. 
 * Each time we get stuck in the second while loop the program get rescued after 2s by the watchdog.
 *
 * Created: 07-Jun-17 13:00:22
 * Author : nyasha majoni
 */ 

#include <avr/io.h>
#include "avr/wdt.h"
#include "avr/interrupt.h"
#include <util/delay.h>

void watchdog_init(void);

int main(void)
{
    uint32_t run_away = 0;
    DDRB |= (1u << PINB5);
    watchdog_init();
	
    while (1) 
    {
		
	PORTB |=  (1u << PINB5);
	_delay_ms(500);   //blocking delay 500ms
	PORTB &= ~(1u << PINB5);
	_delay_ms(500);   //blocking delay 500ms 

	run_away++;
	while(run_away >= 10);
	{
		//the program is stuck here and can only be rescued by the watchdog
	}

	wdt_reset();
    }
}

void watchdog_init(void){
	cli();          //disable all interrupts
	wdt_reset();    //reset the watchdog timer
	WDTCSR |= (1u << WDCE) | (1u << WDE);    //start timed sequence
	WDTCSR =  (1u << WDIE) | (1u << WDE) | (1u << WDP2) | (1u << WDP1) | (1u << WDP0);   //enable watchdog interrupt and reset mode and a watchdog timeout of 2s
	sei();          //enable global interrupts again 	
}

ISR(WDT_vect){
	//useful stuff here
}
