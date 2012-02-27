#define TEST 1

#if TEST
#include <stdio.h>
#define MAIN_TYPE int
#else
#include "pins.h"
#define MAIN_TYPE void
#endif

#define HIGH 1
#define LOW 0

int read_adc(int channel){
  printf("Reading adc channel %d\n", channel);
#if !TEST
  Wait(10);			// rise time
  ADCCON2 = channel;		// select channel
  Wait(1);
  SCONV = 1;			// start conversion

  i=0;
  while (ADCCON3==0x80) // wait while busy bit set
  {
    i++;
    Wait(1);
    if(i==20) return 0; // 20ms, if not finished, give up
  }
#endif
}

void init_uart(void){}
void init_adc(void){}
int get_temp(void){};
int select_sensor(){
}

void mux(int source, int i1, int i2, int i3){
  printf("mux %d : %d, %d, %d\n", source, i1, i2, i3);
#if !TEST
  switch(source){
    case 0: MUXA0 = i1; MUXB0 = i2; MUXC0 = i3;
      break;
    case 1: MUXA1 = i1; MUXB1 = i2; MUXC1 = i3;
      break;
    case 2: MUXA2 = i1; MUXB2 = i2; MUXC2 = i3;
      break;
    case 3: MUXA3 = i1; MUXB3 = i2; MUXC3 = i3;
      break;
  }
#endif
}

int sensor_state(int ABchannel){
#if !TEST
  MUXIN0=MUCIN1=MUCIN2=MUXIN3=LOW;
#endif
  int control;
  for (control=0; control<4; control++)
  {
  int i1 = ABchannel & 1;
  int i2 = ABchannel & 2;
  int i3 = ABchannel & 4;
  mux(control, i1, i2, i3);
  }
}

int save_data(){}
int read_current(){}
int check_current(){}

//void main (void)  {
//  unsigned char j=0XFE;               /* ?? j */
//  while (1) {                         /* ??????? */
///* ??? LED 0, 1, 2, 3, 4, 5, 6, 7 ?? */
 // {
 //     j=(j<<1) | 0x01;
 //     if(j==0XFF) j=0XFE;
  //    P1 = j;                         /* ?????? LED ??? */
 //     delay();                        /* ?? delay ??*/
 //   }
//  }
//}

int enable_current(int current, int onoff){
  printf("Enabling source %d\n", current);
#if !TEST


#endif
}
int read_current();
int check_current();

int read_voltage(int channel){
  enable_current(channel, 1);
  int value = read_adc(channel);
  enable_current(channel, 0);
}

MAIN_TYPE main(void){
  init_uart(); // initialise UART
  init_adc();  // initialise ADC
  enable_current(0, 1); //enable the current source
  get_temp(); //load temperature from the lakeshore thermometer
  read_current(); //read current value
  check_current(); // check if 5uA current value is wrong
  while (1){
    select_sensor(); //start sensor selection
    read_voltage(0); // read voltage across this sensor
    save_data(); //put V[i] I[i] into a memory
  }
}
