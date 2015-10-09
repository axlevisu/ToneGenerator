#include "at89c5131.h"
#include "stdio.h"
#define LED P1

int HiBy,LoBy,a,b;
bit change_delay;
///
///~
sbit Out = P0^0;

///


///~



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
	int counts = 1000000/frequency;
	int two_cmpl;
	///
	
	///~
	two_cmpl=65536-counts;
	HiBy = two_cmpl/256;
	LoBy=two_cmpl%256;
}

void Timer0_ISR (void) interrupt 1
{	///
	
	///~
	TH0 = HiBy;											//For 25ms operation
	TL0 = LoBy; 
	if(b!=0x0f){
	Out=~Out;
	///
			
		
	///~
	
	}
}

void Serial_ISR (void) interrupt 4
{
	if(SBUF<=0x0B)
		{a = SBUF;}
	else{b = SBUF;}
	RI = 0;
	change_delay=1;
	LED = 16*SBUF;
}


void main(void)
{
	///
	///~
	Timer_Init();
	Serial_Init();
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

/*if(b==0x0e){
			if(a==0x00){Time_period(1046.50);}
			if(a==0x01){Time_period(1108.73);}
			if(a==0x02){Time_period(1174.66);}
			if(a==0x03){Time_period(1244.51);}
			if(a==0x04){Time_period(1318.51);}
			if(a==0x05){Time_period(1396.91);}
			if(a==0x06){Time_period(1479.98);}
			if(a==0x07){Time_period(1567.98);}
			if(a==0x08){Time_period(1661.22);}
			if(a==0x09){Time_period(1760.00);}
			if(a==0x0A){Time_period(1864.66);}
			if(a==0x0B){Time_period(1975.53);}
			}*/