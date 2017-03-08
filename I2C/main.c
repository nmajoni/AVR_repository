/*
 * I2C.c
 * 
 * Created: 07-Mar-17 09:28:12
 * Author : nyasha majoni
 */ 

#include <avr/io.h>
#include "I2C.h"
#include <util/delay.h>


int main(void)
{
   DDRA = 0xFF;     //PORT A as output
   I2C_init();      
   I2C_start();
   I2C_write(0x40); //Write slave address to enable it, this is the IO expander's address
      
    while (1) 
    {
		/*
		I2C_write(0x55); //Data to IO expander
		_delay_ms(1000);
		*/
    }
}

