/*----------------------------------------------------------------------------
LAB EXERCISE 11.4- SPI and I2C interface
SERIAL COMMUNICATION
 ----------------------------------------
 Display the temperature from the virtual DS1631 temperature sensor on the 
      virtual LCD
 
 Input: virtual DS1631 temperature sensor
 Output: virtual LCD display
	
	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "NHD_0216HZ.h"
#include "DS1631.h"
#include <string.h>
//#inlcude "pindef.h"

//Define the LCD and the temperature sensor

//Write your code here
const int temp_addr = 0x90;
NHD_0216HZ LCD(PB_6, PA_7, PA_5);
DS1631 TEMPERATURE(PB_9, PB_8, temp_addr);

//Define a variable to store temperature measurement
float temp;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main() {
	//Initialise the LCD
	
	//Write your code here
	LCD.init_lcd();
	LCD.clr_lcd();
	while(1){
		/*
		Read the temperature from the DS1631
		Update the LCD with new temperature measurement
		*/
		//Write your code here
		
		temp = TEMPERATURE.read();
		LCD.set_cursor(0,0);
		//wait(10);
		//LCD.printf("hello");
		LCD.printf("%.3f", temp);
		wait(1);
		LCD.clr_lcd();
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
