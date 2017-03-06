/*
 * UART.c
 *
 * Created: 28-Feb-17 16:19:30
 * Author : nyasha majoni
 */ 

#include <avr/io.h>
#include "util/delay.h"

#define F_CPU 16000000UL
#define BAUD 9600UL                       
#define BAUDRATE ((F_CPU/BAUD/16U)-1U)   //for Baud Rate Register 

//initialize UART
void UART_init(void)
{
	/*set up baud rate*/
	UBRR0H = (BAUDRATE >> 8); //shift to the right by 8 bits, the first 4 bits of the register are occupied
	UBRR0L = BAUDRATE;
	/*set up transmit and receive*/
        UCSR0B |= (1u << RXEN0)|(1u << TXEN0);     //Enable UART transmit and receive
	UCSR0C |= (1u << UCSZ01)|(1u << UCSZ00);   //8 bit data format
}

//function to transmit data
void UART_transmit(unsigned char data)
{
	while (!(UCSR0A & (1u << UDRE0)));   //wait until transmitter is ready, ie  UDRE0 = 1;
	/*implement start bit*/
	UDR0 = data;  //Get that data out, load data
}

//function to receive data
unsigned char UART_receive(void)
{
	while(!(UCSR0A & (1u << RXC0)));    //wait until data in the receive buffer is read/empty ie RXC0 = 0;    
	return UDR0;    
}

int main(void)
{
    UART_init();
    DDRB |= 0xFF;
	
    while (1) 
    {
	unsigned char c;

	//UART_transmit('8');

	c = UART_receive();
	if (c == 'a')
	{
		PORTB |= (1u << PINB7);  //received data via serial monitor and used the on-board LED to check
	}
    }
}

