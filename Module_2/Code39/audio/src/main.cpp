/*----------------------------------------------------------------------------
LAB EXERCISE 9 - Analog input and PWM
 ----------------------------------------
	Use two potentiometers to adjust the volume and pitch of the output sound wave.
	
	Inputs: Virtual potentiometers 1 and 2
	Output: Virtual speaker,  Real PC

	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"
#include "pindef.h"

/*
Define the PWM speaker output
Define analog inputs
Define serial output
*/
#define _320Hz 0.003125f
#define _8KHz 0.000125f

//Write your code here
Serial audio_debug(USBTX, USBRX);
AnalogIn pitch(Ain0);
AnalogIn volume(Ain1);
PwmOut speaker(D12);

//Define variables
float i;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	while(1){
		/*
		Print values of the potentiometers to the PC serial terminal
		Create a saw-tooth sound wave
		Make the period and volume adjustable using the potentiometers
		*/
		/**
		 * 320Hz to 8KHz
		 * 0.003125s to 0.000125s
		 * 0.003125 - 0.000125 = 0.003
		 * The analog steps have to be 0 to 0.003. Since the input value of
		 * the pot will be 0.0 - 1.0, we know 0.003*a_val will result in steps
		 * hence output = 0.003125 - 0.003*a_val, if a_val = 0, output = 0.003125 - 320Hz
		 *  																		, if a_val = 1, output = 0.000125 - 8KHz
		*/
		float pitch_analog_val = pitch.read();
		float pitch_calc = _320Hz - (0.003f*pitch_analog_val);
		speaker.period(pitch_calc);
		/**
		 * The amplitude ranges from 0v to 3.3v. But the volume analog return 0.0f to 1.0f
		 * The amplitude is dependent on the width of the pwm i.e. Ton, duty cycle
		 * 100%duty cycle means 3.3v. PwmOut write function takes the duty cycle between 0.0f
		 * 1.0f. Hence we feed the out of the analog read directly into pwm write.
		*/
		speaker.write(volume.read());
		
		audio_debug.printf("Volume %f, Pitch: %f\r\n", volume.read(), pitch.read());
		
		for(float i = 0; i < 1; i += pitch_calc)
		{
			speaker = i;
		}
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2014*************************************
