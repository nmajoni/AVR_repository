/*
 * UART.c
 *
 * Created: 28-Feb-17 16:19:30
 * Author : nyasha majoni
 */ 

#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>
#include <string.h>

/*defines*/
#define TX_BUFFER 128
#define F_CPU 16000000UL
#define BAUD 9600UL                       
#define BAUDRATE ((F_CPU/BAUD/16U)-1U)   //for Baud Rate Register 

/*global static variables*/
static char serial_buffer[TX_BUFFER];
static uint8_t serial_read_pos;
static uint8_t serial_write_pos; 

/*UART program functions*/
void UART_init(void);
void UART_transmit(unsigned char data);
unsigned char UART_receive(void);
void put_into_buffer(char c);
void serial_write(char  c[]);


//main function
int main(void)
{
    UART_init();
    DDRB |= 0xFF;
    sei();
    serial_read_pos  = 0;
    serial_write_pos = 0;

    serial_write("Hello\n\r");
    serial_write("Buddy\n\r");
	
    while (1) 
    {
    }
}


//initialize UART
void UART_init(void)
{
	/*set up baud rate*/
	UBRR0H = (BAUDRATE >> 8); //shift to the right by 8 bits, the first 4 bits of the register are occupied
	UBRR0L = BAUDRATE;
	/*set up transmit and receive*/
	UCSR0B |= (1u << RXEN0)|(1u << TXEN0)|(1u << TXCIE0);     //Enable UART transmit and receive
	UCSR0C |= (1u << UCSZ01)|(1u << UCSZ00);   //8 bit data format
}

//function to transmit data without interrupts
void UART_transmit(unsigned char data)
{
	while (!(UCSR0A & (1u << UDRE0)));   //wait until transmitter is ready, ie  UDRE0 = 1, buffer empty
	/*implement start bit*/
	UDR0 = data;  //Get that data out, load data
}

//function to receive data without interrupts
unsigned char UART_receive(void)
{
	while(!(UCSR0A & (1u << RXC0)));    //wait until data in the receive buffer is read/empty ie RXC0 = 0;
	return UDR0;
}

//function to append characters into my buffer
void put_into_buffer(char c)
{
	serial_buffer[serial_write_pos] = c;
	serial_write_pos++;
	
	if (serial_write_pos >= TX_BUFFER)
	{
		serial_write_pos = 0;
	}
}

//function to transmit a string char by char
void serial_write(char c[])
{
	for(uint8_t i = 0; i < strlen(c); i++)
	{
		put_into_buffer(c[i]);
	}
	
	if (UCSR0A & (1 << UDRE0)) //check if transmit buffer is ready
	{
		UDR0 = 0;              //transmit null character to fire off the transmit done interrupt
	}
}

//TX complete ISR
ISR(USART0_TX_vect)
{
	if (serial_read_pos != serial_write_pos)
	{
		UDR0 = serial_buffer[serial_read_pos];
		serial_read_pos++;
		
		if (serial_read_pos >= TX_BUFFER)
		{
			serial_read_pos = 0;
		}
	}
}


