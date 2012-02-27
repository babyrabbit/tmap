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

#if !TEST
int sensor_state(int ABchannel){
  MUXIN0=MUCIN1=MUCIN2=MUXIN3=LOW;
  for (control=0; control<4; control++)
  {
    switch(ABchannel){
      case 0:
         MUXA[control]=LOW; MUXB[control]=LOW; MUXC[control]=LOW;
         break;
      case 1:
        MUXA[control]=LOW; MUXB[control]=LOW; MUXC[control]=HIGH;
        break;
      case 2:
        MUXA[control]=LOW; MUXB[control]=HIGH; MUXC[control]=LOW;
        break;
      case 3:
        MUXA[control]=LOW; MUXB[control]=HIGH; MUXC[control]=HIGH;
        break;
      case 4:
        MUXA[control]=HIGH; MUXB[control]=LOW; MUXC[control]=LOW;
        break;
      case 5:
        MUXA[control]=HIGh; MUXB[control]=LOW; MUXC[control]=HIGH;
        break;
      case 6:
        MUXA[control]=HIGH; MUXB[control]=HIGH; MUXC[control]=LOW;
        break;
      case 7:
        MUXA[control]=HIGH; MUXB[control]=HIGH; MUXC[control]=HIGH;
        break;
      default:
        break;
    }
  }
}
#endif

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
int	check_current();

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
