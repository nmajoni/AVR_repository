/*
 * I2C.h
 *
 * Created: 07-Mar-17 12:44:32
 *  Author: nyasha majoni
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#define F_CPU 16000000UL

/*Initialize I2C*/
void I2C_init(void)
{
	//1. Set Baud Rate for data transfer in TWBR
	TWBR = 0x62u;   //calculated using this equation: SCL CLOCK = (CPU CLOCK FREQUENCY)/(16+2*(TWBR)*4^TWPS 
	//2. Set the TWEN bit in TWCR reg, for enabling TWI communication
	TWCR = (1u << TWEN);
	//3. Set the prescaler in TWSR
	TWSR = 0x00u;  //prescaller ser to 1
}

/*START Condition*/
void I2C_start(void)
{
	//1. Clear TWINT by writing 1 to it
	//2. Set TWSTA (TWI START Condition) bit in TWCR
	//3. Set TWEN bit in TWCR
	TWCR = (1u << TWINT)|(1u << TWSTA)|(1u << TWEN);
	
	//4. Check if TWINT bit is set in the control register ie TWCR
	while (!(TWCR & (1u << TWINT)));
}

/*STOP Condition*/
void I2C_stop(void)
{
	//1. Clear TWINT bit by writing 1 to it
	//2. Set TWEN bit
	//3. Set TWSTO bit
	TWCR = (1u << TWINT)|(1u << TWEN)|(1u << TWSTO);
}

/*WRITE Condition*/
void I2C_write(char x)
{
	//1. Move the data to be transmitted to TWDR (data register)
	TWDR = x;
	//2. Clear TWINT by setting bit as 1 in TWCR, TWEN is set
	TWCR = (1u << TWINT)|(1u << TWEN);
	//3. Check if TWINT bit is set in TWCR reg
	while(!(TWCR & (1u << TWINT)));
}

/*READ Condition*/
char I2C_read(void)
{	
	//1. Clear interupt TWINT bit by writing 1 to it in the TWCR, TWEN is set
	TWCR = (1u << TWEN)|(1u << TWINT);
	//2. Check if TWINT bit is set in TWCR reg
	while (!(TWCR & (1u << TWINT)));
	//3. Return TWDR
	return TWDR;
}


#endif /* I2C_H_ */
