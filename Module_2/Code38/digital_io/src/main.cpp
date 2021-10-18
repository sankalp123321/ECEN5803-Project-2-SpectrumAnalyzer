/*----------------------------------------------------------------------------
LAB EXERCISE 8.1 - DIGITAL INPUTS AND OUTPUTS
PROGRAMMING USING MBED API
 ----------------------------------------
 In this exercise you need to use the mbed API functions to:
 
	1) Define BusIn, BusOut interfaces for inputs and outputs
	2) The LED is controlled by the button:
			+ USER_BUTTON - LED1
			
	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"

//Define input bus
	//Write your code here
BusIn button(D2, D3, D4, D5);
//Define output bus for the  LED
	//Write your code here
BusOut led(D13, D7);

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	led = 0;
	while(1){
		
		//Check which button was pressed and light up the corresponding LED
		//Write your code here
		switch(button)
		{
			case 0x01:
					led = led | (1 << 0x01);
				break;
			case 0x02:
					led = led & ~(1 << 0x01);
				break;
			case 0x04:
					led = led | (1 << 0x00);
				break;
			case 0x08:
					led = led & ~(1 << 0x00);
				break;
		};
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
