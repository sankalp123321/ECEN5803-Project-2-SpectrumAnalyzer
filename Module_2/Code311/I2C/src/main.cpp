/*----------------------------------------------------------------------------
LAB EXERCISE 11.3 - I2C interface
SERIAL COMMUNICATION
 ----------------------------------------
	Access the virtual temperature sensor via I2C interface, print the current temperature
	to the PC via UART
	
	Input: temperature sensor
	Output: PC
	
	GOOD LUCK!
 *----------------------------------------------------------------------------*/
#include "mbed.h"
#include "I2C.h"
#include "pindef.h"

//I2C interface
I2C temp_sensor(I2C_SDA, I2C_SCL);
Serial pc(UART_TX, UART_RX);

//I2C address of temperature sensor DS1631
const int temp_addr = 0x90;

char cmd[] = {0x51, 0xAA};
char read_temp[2];

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	while(1){
		/*
		Write the Start Convert T command to the sensor
		Write the Read Temperature command to the sensor
		Read the 16-bit temperature data
		*/
		
		//Write your code here
		int err = 0;
		err = temp_sensor.write(temp_addr, &cmd[0], 1);
		err = temp_sensor.write(temp_addr, &cmd[1], 1);
		err = temp_sensor.read(temp_addr, read_temp, 2);

		//Convert temperature to Celsius
		float temp = (float((read_temp[0] << 8) | read_temp[1]) / 256);
		
		//Print temperature to the serial monitor
		
		//Write your code here
		
		printf("%.2f", temp);
		wait(1);
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
