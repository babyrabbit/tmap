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
