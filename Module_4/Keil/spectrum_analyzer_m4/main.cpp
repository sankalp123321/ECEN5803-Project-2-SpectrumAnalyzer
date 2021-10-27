#include "mbed.h"
/* Include arm_math.h mathematic functions */
#include "arm_math.h"
/* Include mbed-dsp libraries */
#include "arm_common_tables.h"
#include "arm_const_structs.h"
#include "math_helper.h"
#include "fft_inp.h"

#define SAMPLING_FREQUENCY 10000.0f

/* FFT settings */
#define SAMPLES                 8192             /* 256 real party and 256 imaginary parts */
#define FFT_SIZE                SAMPLES / 2     /* FFT size is always the same size as we have samples, so 256 in our case */
/* Global variables */

#define _HARD_CODED_

unsigned int maxIndex = 0;
float32_t maxValue;
bool      trig=0;

/* MBED class APIs */
DigitalOut myled(D13);
AnalogIn   myADC(A1);
Serial     pc(USBTX, USBRX);
Ticker     timer;
Ticker     led_timer;

float32_t Input[SAMPLES];
float32_t Output[FFT_SIZE];

float freq_equiv = SAMPLING_FREQUENCY/(float)(SAMPLES/2.0f);

void sample()
{
   trig = 1;
}

bool ledState = 0;
void led_blinker()
{
    ledState = !ledState;
    myled = ledState;
}

int main() {
    pc.baud(115200);
    while(1){
      memset(Input, 0, SAMPLES);
      memset(Output, 0, FFT_SIZE);
      k = 0;
      timer.attach_us(&sample, 100);
      for (int i = 0; i < SAMPLES; i += 2) 
      {
          while(!trig) {}
          trig = 0;
#ifdef _HARD_CODED_
        Input[i] =  tone[k]; //Real part NB removing DC offset
#else
        Input[i] =  myADC.read() - 0.5f; //Real part NB removing DC offset
#endif
        Input[i + 1] = 0;               //Imaginary Part set to zero
        k++;
      }
      timer.detach();
      /* Process the data through the CFFT/CIFFT module */
      arm_cfft_f32(&arm_cfft_sR_f32_len4096, Input, 0, 1);

      /* Process the data through the Complex Magniture Module for calculating the magnitude at each bin */
      arm_cmplx_mag_f32(Input, Output, FFT_SIZE);

      /* Calculates maxValue and returns corresponding value */
      arm_max_f32(Output, FFT_SIZE, &maxValue, &maxIndex);
      printf("Max value: %f Index: %u Frequency: %fHz\r\n", Output[maxIndex], maxIndex, freq_equiv*(float)maxIndex);

      led_timer.attach_us(led_blinker, (1000000/(freq_equiv*(float)maxIndex)));
    }
}