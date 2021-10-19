/*----------------------------------------------------------------------------
LAB EXERCISE 12 - Real-Time Operating System
 ----------------------------------------
	Integrate functions developed in previous modules and run then concurrently
	in the mbed RTOS. The following four threads have to be implemented:
	
	1. Display the temperature on the LCD and to the PC
	2. Adjust the brightness of the RGB LED using a potentiometer
	3. Display an incrementing counter on the LCD and to the PC
	4. Blink an LED
  
  NOTE:  For this lab, the LCD, temp sensor and POT are virtual devices.

	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"
#include "rtos.h"
#include "DS1631.h"
#include "NHD_0216HZ.h"
#include "pindef.h"

/*
Define the mutex
Define the LCD display and the temperature sensor
Define other inputs and outputs
*/

//Write your code here
AnalogIn pot(A0);
PwmOut red_led(D7);
osMutexId gPotentiometerMutex;

float gPotValue;
//Display temperature on the LCD
void temp_thread(void const *args){
	
	//write your code here
	
}

//Adjust the brightness of the RGB LED
void adjust_brightness(void const *args){
	//write your code here
	while(1)
	{
		osMutexWait(gPotentiometerMutex, 0);
		gPotValue = pot.read();
		red_led.write(gPotValue);
		osMutexRelease(gPotentiometerMutex);
	}
}

//Blink an LED
void led1_thread(void const *args){
	
	//write your code here
	while(1)
	{
		osMutexWait(gPotentiometerMutex, 0);
		red_led.write(0);
		wait(500);
		red_led.write(gPotValue);
		wait(500);
		osMutexRelease(gPotentiometerMutex);
	}
}

//Display a counter on the LCD
void count_thread(void const *args){
	
	//write your code here
	
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	/*
	Initialise and clear the LCD display
	Start all threads
	Wait for timer interrupt
	*/
	//write your code here
	red_led.period_ms(500);
	osMutexDef (gPotentiometerMutex);
	gPotentiometerMutex = osMutexCreate(osMutex(gPotentiometerMutex));
	while(1)
	{
		
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
