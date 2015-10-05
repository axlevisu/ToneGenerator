#include "at89c5131.h"
#include "stdio.h"





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
	count =0;
}


void Serial_Init ()
{
	SCON = 0x50;
  TMOD = (TMOD & 0x0F) | 0x20;
	ES = 1;
	TH1 = 0xFA;
	TR1 = 1;
}

void Timer0_ISR (void) interrupt 1
{
	TH0 = HiBy;											//For 25ms operation
	TL0 = LoBy; 
	if(b!=0x0f){
	Out=~Out;}
}

void Serial_ISR (void) interrupt 4
{
	if(SBUF<=0x0B)
		{a = SBUF;}
	else{b = SBUF;}
	RI = 0;
	change_delay=1;
}

void main(void)
{
	Timer_Init();
	Serial_Init();
	while(1){
		if (change_delay==1){
		if(b==0x0c){
			if(a==0x00){}
			if(a==0x01){}
			if(a==0x02){}
			if(a==0x03){}
			if(a==0x04){}
			if(a==0x05){}
			if(a==0x06){}
			if(a==0x07){}
			if(a==0x08){}
			if(a==0x09){}
			if(a==0x0A){}
			if(a==0x0B){}
			}
		if(b==0x0d){
			if(a==0x00){}
			if(a==0x01){}
			if(a==0x02){}
			if(a==0x03){}
			if(a==0x04){}
			if(a==0x05){}
			if(a==0x06){}
			if(a==0x07){}
			if(a==0x08){}
			if(a==0x09){}
			if(a==0x0A){}
			if(a==0x0B){}
			}
		if(b==0x0e){
			if(a==0x00){}
			if(a==0x01){}
			if(a==0x02){}
			if(a==0x03){}
			if(a==0x04){}
			if(a==0x05){}
			if(a==0x06){}
			if(a==0x07){}
			if(a==0x08){}
			if(a==0x09){}
			if(a==0x0A){}
			if(a==0x0B){}
			}
		}
		

		
	}
}