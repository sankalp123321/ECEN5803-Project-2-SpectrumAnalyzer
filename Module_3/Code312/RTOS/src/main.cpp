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

#define osObjectPublic
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
//	static void temp_thread();
//	static void adjust_brightness();
//	static void led1_thread();
//	static void count_thread();
//	Thread temperature(0);
//	Thread led_brightness(0);
//	Thread led_blink(0);
//	Thread thread_counter();


#define temp_addr 	0x90
NHD_0216HZ LCD(PB_6, PA_7, PA_5);
DS1631 TEMPERATURE(PB_9, PB_8, temp_addr);
AnalogIn pot(A0);
PwmOut red_led(D7);

osMutexId gPotentiometerMutex;
osMutexDef(gPotentiometerMutex);
osMutexId LCD_mutex;
osMutexDef(LCD_mutex);

osSemaphoreId temper;
osSemaphoreDef(temper);
osSemaphoreId adjust;
osSemaphoreDef(adjust);
osSemaphoreId led1_;
osSemaphoreDef(led1_);
osSemaphoreId ccount;
osSemaphoreDef(ccount);





float gPotValue;
//float temp;
uint32_t count = 0;
//Display temperature on the LCD
void temp_thread(void const *args){
	
	//write your code here
	float temp = 0;
	while(1)
	{
		//Thread::wait(osWaitForever);
		//sem_temp.wait(500);
		osSemaphoreWait(temper,osWaitForever);
		printf("1");
		osMutexWait(LCD_mutex, osWaitForever);
		temp = TEMPERATURE.read();
		LCD.set_cursor(0,0);
		LCD.printf("%.3f", temp);
		
		osMutexRelease(LCD_mutex);
		//sem_temp.release();
		//Thread::wait(500);
		//Thread::yield();
		
		osSemaphoreRelease(adjust);
		//wait_ms(1000);
	}
}

//Adjust the brightness of the RGB LED
void adjust_brightness(void const *args){
	//write your code here
	while(1)
	{	
		osSemaphoreWait(adjust,osWaitForever);
		printf("2");
		//Thread::wait(osWaitForever);
		//sem_bright.wait(500);//osWaitForever);
		osMutexWait(gPotentiometerMutex, osWaitForever);
		gPotValue = pot.read();
		red_led.write(gPotValue);
		
		osMutexRelease(gPotentiometerMutex);
		//sem_bright.release();
		//Thread::wait(500);
		
		osSemaphoreRelease(led1_);
		//wait_ms(3000);

	}
}

//Blink an LED
void led1_thread(void const *args){
	
	//write your code here
	while(1)
	{
		osSemaphoreWait(led1_,osWaitForever);
		//Thread::wait(osWaitForever);
		//sem_blink.wait(500);
		printf("3");
		osMutexWait(gPotentiometerMutex, osWaitForever);
		red_led.write(0);
		wait_ms(500);
		red_led.write(gPotValue);
		wait_ms(500);

		osMutexRelease(gPotentiometerMutex);
		//sem_count.release();
		//Thread::yield();
		osSemaphoreRelease(ccount);
		//wait_ms(500);
	}
}

//Display a counter on the LCD
void count_thread(void const *args){
	
	//write your code here
	//uint32_t count = 0;
	while(1)
	{
		osSemaphoreWait(ccount,osWaitForever);
		//Thread::wait(osWaitForever);
//		sem_count.wait(500);
		printf("4");
		osMutexWait(LCD_mutex, osWaitForever);
		
		count++;
		LCD.set_cursor(0,1);
		//wait_us(100);
		LCD.printf("%.3d", count);
//		wait_ms(500);
//		LCD.clr_lcd();
		osMutexRelease(LCD_mutex);
		//sem_temp.release();
		//Thread::wait(500);
		
		osSemaphoreRelease(temper);
		//wait_ms(1000);
	}
}

osThreadDef(temp_thread, osPriorityNormal, 0x200); // Define the task
osThreadDef(adjust_brightness, osPriorityNormal, 0x200); // Define the task
osThreadDef(led1_thread, osPriorityNormal, 0x200); // Define the task
osThreadDef(count_thread, osPriorityNormal, 0x200); // Define the task


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	osKernelInitialize();
	/*
	Initialise and clear the LCD display
	Start all threads
	Wait for timer interrupt
	*/
	//write your code here
	
	gPotentiometerMutex = osMutexCreate(osMutex(gPotentiometerMutex));
	LCD_mutex = osMutexCreate(osMutex(LCD_mutex));
	temper = osSemaphoreCreate(osSemaphore(temper),2);
	adjust = osSemaphoreCreate(osSemaphore(adjust),2);
	led1_ = osSemaphoreCreate(osSemaphore(led1_),2);
	ccount = osSemaphoreCreate(osSemaphore(ccount),2);
	LCD.init_lcd();
	LCD.clr_lcd();
	
	

	printf("Starting...\r\n");
	unsigned char temp = NULL;// = 0xa5;

	//red_led.period_ms(500);
	osThreadCreate(osThread(temp_thread), NULL);
	osThreadCreate(osThread(adjust_brightness), NULL);
	osThreadCreate(osThread(led1_thread), NULL);
	osThreadCreate(osThread(count_thread), NULL);
//	Thread thread_counter(count_thread,NULL,osPriorityHigh,DEFAULT_STACK_SIZE);
//	Thread tempature(temp_thread,NULL,osPriorityHigh,DEFAULT_STACK_SIZE);
//	Thread led_brightness(adjust_brightness,NULL,osPriorityHigh,DEFAULT_STACK_SIZE);
//	Thread led_blink(led1_thread,NULL,osPriorityHigh,DEFAULT_STACK_SIZE);
	

//	
//	temperature.start(temp_thread);
//	led_brightness.start(adjust_brightness);
//	led_blink.start(led1_thread);
//	thread_counter.start(count_thread):
	
	//osThreadId_t osThreadGetId();
	//uint32_t i = osThreadGetCount();
	//Thread::gettid();
//	Thread temperature(temp_thread,NULL,osPriorityNormal,DEFAULT_STACK_SIZE,&temp);
//	Thread led_brightness(adjust_brightness,NULL,osPriorityNormal,DEFAULT_STACK_SIZE,&bright);
//	Thread led_blink(led1_thread,NULL,osPriorityNormal,DEFAULT_STACK_SIZE,&blink);
//	Thread thread_counter(count_thread,NULL,osPriorityNormal,DEFAULT_STACK_SIZE,&counter);
	
	
	//osMutexDef (gPotentiometerMutex);
	//gPotentiometerMutex = osMutexCreate(osMutex(gPotentiometerMutex));
	
	//sem_temp.release();
//	sem_count.release();
//	sem_blink.release();
//	sem_bright.release();
	//Thread::yield();
	osKernelStart();                         // start thread execution 
	osSemaphoreRelease(temper);
	osMutexRelease(gPotentiometerMutex);
	osMutexRelease(LCD_mutex);
	while(1){
		sleep();
	}
	
//	temperature.yield();
//	ThisThread::sleep_for(5000);
//	temperature.join();
//	led_brightness.join();
//	led_blink.join();
//	thread_counter();
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************