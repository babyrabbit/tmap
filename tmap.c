#define TEST 0
#define CALIBRATION 0
#define

sbit AB0 = chans ^ 0;		// flag for AB 0
sbit AB1 = chans ^ 1;		// flag for AB 1
sbit AB2 =
sbit AB3 = 
 
sbit current0 = P0 ^ 0;		//control current source 0
sbit current1 = P0 ^ 1;		//control current source 1
sbit current2 = P3 ^ 7;		//control current source 2
sbit current3 = P3 ^ 6;		//control current source 3

sbit MUXIN0 = P0 ^ 5;		//control multiplexer 0 selection pins 
sbit MUXA0 = P0 ^ 4;  
sbit MUXB0 = P0 ^ 3;
sbit MUXC0 = P0 ^ 2;

sbit MUXIN1 = P2 ^7 ;
sbit MUXA1 = P2 ^ 6;
sbit MUXB1 = P2 ^ 5;
sbit MUXC1 = P2 ^ 4;

sbit MUXIN2 = P2 ^3 ;
sbit MUXA2 = P2 ^ 2;
sbit MUXB2 = P2 ^ 1;
sbit MUXC2 = P2 ^ 0;

sbit MUXIN3 = P3 ^ 5;
sbit MUXA3 = P3 ^ 4;
sbit MUXB3 = P3 ^ 3;
sbit MUXC3 = P3 ^ 2;

sfr16 EDAT1 = 0x0BC;		//edata1=low edata2=high byte
sfr16 ADC = 0x0D9;
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
	while (1){
	select_sensor(); //start sensor selection
	read_voltage(); // read voltage across this sensor
	
	save_data(); //put V[i] I[i] into a memory 
	}
	
	
	}
