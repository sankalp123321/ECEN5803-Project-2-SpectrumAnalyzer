#include "mbed.h"
/* Include arm_math.h mathematic functions */
#include "arm_math.h"
/* Include mbed-dsp libraries */
#include "arm_common_tables.h"
#include "arm_const_structs.h"
#include "math_helper.h"
 
/* FFT settings */
#define SAMPLES                 512             /* 256 real party and 256 imaginary parts */
#define FFT_SIZE                SAMPLES / 2     /* FFT size is always the same size as we have samples, so 256 in our case */
 
/* Global variables */
float32_t Input[SAMPLES];
float32_t Output[FFT_SIZE];
bool      trig=0;
/* MBED class APIs */
DigitalOut myled(LED1);
AnalogIn   myADC(A1);
//AnalogOut  myDAC(D13);
Serial     pc(USBTX, USBRX);
Ticker     timer;
 
void sample()
{
   trig=1;
}
 
int main() {
 
    //arm_cfft_instance_f32 S;   // ARM CFFT module
    float maxValue;            // Max FFT value is stored here
    uint32_t maxIndex;         // Index in Output array where max value is
    bool once=0;
    pc.baud(115200);
    pc.printf("Starting FFT\r\n");
    while(1) 
		{
			timer.attach_us(&sample,20); //20us 50KHz sampling rate
      for (int i = 0; i < SAMPLES; i += 2) 
			{
				while (trig==0){}
				trig=0;
				Input[i] = myADC.read() - 0.5f; //Real part NB removing DC offset
				Input[i + 1] = 0;               //Imaginary Part set to zero
			}
      timer.detach();
      // Init the Complex FFT module, intFlag = 0, doBitReverse = 1
      //NB using predefined arm_cfft_sR_f32_lenXXX, in this case XXX is 256
      arm_cfft_f32(&arm_cfft_sR_f32_len256, Input, 0, 1);
 
      // Complex Magniture Module put results into Output(Half size of the Input)
      arm_cmplx_mag_f32(Input, Output, FFT_SIZE);
      
      //Calculates maxValue and returns corresponding value
      arm_max_f32(Output, FFT_SIZE, &maxValue, &maxIndex);
 
      if (once==0)
			{
				pc.printf("Maximum is %f\r\n",maxValue);
				once = 1;
      }
      
      //maxValue /= 100.0f;
      
//      myDAC=1.0f;     //SYNC Pulse to DAC Output
//      wait_us(20);    //Used on Oscilliscope set trigger level to the highest
//      myDAC=0.0f;     //point on this pulse (all FFT data will be scaled
//                        //90% of Max Value
//        
//        for (int i=0; i<FFT_SIZE/2 ; i++){
//            myDAC=(Output[i]/maxValue)*0.9f; // Scale to Max Value and scale to 90%
//            wait_us(10); //Each pulse of 10us is 50KHz/256 = 195Hz resolution
//            }
//        myDAC=0.0f;
       }
}
            