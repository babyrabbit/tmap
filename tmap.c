#define TEST 0
#define CALIBRATION 0
#define MEASURE 1

sbit AB0 = chans ^ 0;		// flag for AB 0
sbit AB1 = chans ^ 1;		// flag for AB 1
sbit 
sbit source0 = P0 ^ 0;		//control current source 0
sbit source1 = P0 ^ 1;		//control current source 1

sbit int0 = P2 ^ 0;			//temp AB1 OVER
sbit int1 = P2 ^ 1;			//temp AB2 OVER
sfr16 EDAT1 = 0x0BC;		//edata1=low edata2=high byte
sfr16 ADC = 0x0D9;
sfr16 DAC0= 0x0F9;
sfr16 DAC1=0x0FB;
sfr16 EDA1= 0xBC;

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
void enable_current(){
};
int read_voltage(int channel){
	enable_current(channel, 1);
	int value = read_adc(chanel);
	enable_current(channel, 0);
	
}
	
void main(void){
	init_uart(); // initialise UART
	init_adc();  // initialise ADC
	enable_current(); //enable the current source
	get_temp(); //load temperature from the lakeshore thermometer
	
	read_current(); //read current value
	check_current(); // check if 5uA current value is wrong
	select_sensor(); //start sensor selection
	read_voltage(); // read voltage across this sensor
	
	save_data(); //put V[i] I[i] into a memory 
	write_data();
	
	do_temperature();
	}
