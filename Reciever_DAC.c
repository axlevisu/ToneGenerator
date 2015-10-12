#include "at89c5131.h"
#include "stdio.h"


int HiBy,LoBy,a,b;
bit change_delay;
int Array[12] = {128*16,192*16,239*16,255*16,239*16,192*16,128*16,64*16,17*16,0,17*16,64*16};
int i=0;
bit transmit_completed = 0;
sbit CS_BAR = P0^2;
sbit LDAC_BAR = P0^1;
sbit Out = P0^0;
unsigned char serial_data;

void Timer_Init()
{
	// Set Timer0 to work in up counting 16 bit mode. Counts upto 
	// 65536 depending upon the calues of TH0 and TL0
	// The timer counts 65536 processor cycles. A processor cycle is 
	// 12 clocks. FOr 24 MHz, it takes 65536/2 uS to overflow
	// By setting TH0TL0 to 3CB0H, the timer overflows every 25 ms
	EA=1;
	TH0 = 0x3C;											//For 25ms operation
	TL0 = 0xB0;
	TMOD = (TMOD & 0xF0) | 0x01;  	// Set T/C0 Mode 
	ET0 = 1;                      	// Enable Timer 0 Interrupts 
	TR0 = 1;                      	// Start Timer 0 Running 
	//count =0;
}

void SPI_Init ()
{
  CS_BAR = 1;	                  	// DISABLE ADC SLAVE SELECT-CS 
	SPCON |= 0x20;               	 	// P1.1(SSBAR) is available as standard I/O pin 
	SPCON |= 0x01;                	// Fclk Periph/4 AND Fclk Periph=12MHz ,HENCE SCK IE. BAUD RATE=3000KHz 
	SPCON |= 0x10;               	 	// Master mode 
	SPCON &= ~0x08;               	// CPOL=0; transmit mode example|| SCK is 0 at idle state
	SPCON &= ~0x04;                	// CPHA=1; transmit mode example 
	IEN1 |= 0x04;                	 	// enable spi interrupt 
	EA=1;                         	// enable interrupts 
	SPCON |= 0x40; 
}


void Serial_Init ()
{
	SCON = 0x50;
  TMOD = (TMOD & 0x0F) | 0x20;
	ES = 1;
	TH1 = 243;
	TR1 = 1;
}

void Time_period (float frequency)
{
	int two_cmpl;
	int counts = 1000000/frequency;
  counts = counts/6;
	two_cmpl=65536-counts;
	HiBy = two_cmpl/256;
	LoBy=two_cmpl%256;
}

void Timer0_ISR (void) interrupt 1
{
	char c;
	TH0 = HiBy;											//For 25ms operation
	TL0 = LoBy; 
	if(b!=0x0f)
		{
			if(i%6==0){Out=~Out;}
			LDAC_BAR = 1;
			CS_BAR = 0;                 // enable ADC as slave		 
		  c = Array[i]/256;
			SPDAT= 0x70+c;								// Write start bit to start ADC 
		  while(!transmit_completed);	// wait end of transmition;TILL SPIF = 1 
		  transmit_completed = 0;    	// clear software transfert flag 
		
			
			c = Array[i]%256;
			SPDAT = c;
			while(!transmit_completed);
			transmit_completed = 0;
			
		  CS_BAR = 1; 
			LDAC_BAR = 0;}              	// disable ADC as slave*/}
	if(i!=12){i++;}
	else{i=0;}
}

void Serial_ISR (void) interrupt 4
{
	if(SBUF<=0x0B)
		{a = SBUF;}
	else{b = SBUF;}
	RI = 0;
	change_delay=1;
}

void it_SPI(void) interrupt 9 /* interrupt address is 0x004B */
{
	switch	( SPSTA )         /* read and clear spi status register */
	{
		case 0x80:	   /* read receive data */
    serial_data=SPDAT;    
		transmit_completed=1;/* set software flag */
 		break;

		case 0x10:
         /* put here for mode fault tasking */	
		break;
	
		case 0x40:
         /* put here for overrun tasking */	
		break;
	}
}

void main(void)
{
	P3 = 0X00;											// Make Port 3 output 
	P2 = 0x00;											// Make Port 2 output 
	P1 &= 0xEF;											// Make P1 Pin4-7 output
	P0 &= 0xF0;											// Make Port 0 Pins 0,1,2 output
	
	Timer_Init();
	Serial_Init();
	SPI_Init();
	while(1){
		if (change_delay==1){
		if(b==0x0c){
			if(a==0x00){Time_period(130.81);}
			if(a==0x01){Time_period(138.59);}
			if(a==0x02){Time_period(146.83);}
			if(a==0x03){Time_period(155.56);}
			if(a==0x04){Time_period(164.81);}
			if(a==0x05){Time_period(174.61);}
			if(a==0x06){Time_period(185.00);}
			if(a==0x07){Time_period(196.00);}
			if(a==0x08){Time_period(207.65);}
			if(a==0x09){Time_period(220.00);}
			if(a==0x0A){Time_period(233.08);}
			if(a==0x0B){Time_period(246.94);}
			}
		if(b==0x0d){
			if(a==0x00){Time_period(261.63);}
			if(a==0x01){Time_period(277.18);}
			if(a==0x02){Time_period(293.66);}
			if(a==0x03){Time_period(311.13);}
			if(a==0x04){Time_period(329.63);}
			if(a==0x05){Time_period(349.23);}
			if(a==0x06){Time_period(369.99);}
			if(a==0x07){Time_period(392.00);}
			if(a==0x08){Time_period(415.30);}
			if(a==0x09){Time_period(440.00);}
			if(a==0x0A){Time_period(466.16);}
			if(a==0x0B){Time_period(493.88);}
			}
		if(b==0x0e){
			if(a==0x00){Time_period(523.25);}
			if(a==0x01){Time_period(554.37);}
			if(a==0x02){Time_period(587.33);}
			if(a==0x03){Time_period(622.25);}
			if(a==0x04){Time_period(659.25);}
			if(a==0x05){Time_period(698.46);}
			if(a==0x06){Time_period(739.99);}
			if(a==0x07){Time_period(783.99);}
			if(a==0x08){Time_period(830.61);}
			if(a==0x09){Time_period(880.00);}
			if(a==0x0A){Time_period(932.33);}
			if(a==0x0B){Time_period(987.77);}
			}
		change_delay=0;
		}
		

		
	}
}