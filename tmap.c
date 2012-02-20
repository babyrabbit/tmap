#define TEST 0

int enable_source(int source, int onoff){
	printf("Enabling source %d", source);
#if !TEST
// do stuff...
#endif
}

int read_adc(int channel){
	printf("Reading adc channel %d", channel);
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

int init_uart(){
}

int read_voltage(int channel){
	enable_source(channel, 1);
	int value = read_adc(chanel);
	enable_source(channel, 0);
}
	
int main(){
	init_uart();
	read_voltage();
}
