/*----------------------------------------------------------------------------
LAB EXERCISE 8.2 - INTERRUPT IN/OUT
PROGRAMMING USING MBED API
 ----------------------------------------
 In this exercise you need to use the mbed API functions to:
 
	1) Define InterruptIn and ISR for the button press
	2) In the interrupt service routine, the LED is used to indicate when a
	button was pressed:
			+ USER_BUTTON - LED1

	3) Put the processor into sleep mode upon exiting from the ISR
			
	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"

//Define outputs

	//Write your code here
BusOut led(D13, D7);
//Define interrupt inputs

	//Write your code here
InterruptIn  b_1(D2);
InterruptIn  b_2(D3);
InterruptIn  b_3(D4);
InterruptIn  b_4(D5);

//Define ISRs for the interrupts
void button_1_handler(){
	
	//Write your code here
	led = led | (1 << 0x01);
}

void button_2_handler(){
	
///Write your code here
	led = led & ~(1 << 0x01);
}

void button_3_handler(){
	
///Write your code here
	led = led | (1 << 0x00);
}

void button_4_handler(){
	
///Write your code here
	led = led & ~(1 << 0x00);
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	
	__enable_irq();			//enable interrupts
	
	//initially turn off  LED
	//Write your code here
	led = 0;
	//Interrupt handlers
	//Attach the address of the ISR to the rising edge
		//Write your code here
	b_1.rise(&button_1_handler);
	b_2.rise(&button_2_handler);
	b_3.rise(&button_3_handler);
	b_4.rise(&button_4_handler);

	//Sleep on exit
	while(1){
		
		//Write your code here
		__wfi() ; 		//go to sleep
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
