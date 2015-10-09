//Transmitter
//Group 1
/**
Muppirala Viswa Virinchi
Sai Ritwik
Gokul Koraganji
**/
#include "at89c5131.h"
#include "stdio.h"
#define KEY P0
#define PRESS P1

void SerTx(int x);
void MSDelay(unsigned int value);

int keypad[4][4]= {
	0,1,2,3,
	4,5,6,7,
	8,9,10,11,
	12,13,14,15
};

void main()
{

	unsigned char colloc, rowloc;
	TMOD = 0x20;//timer 1 mode 2
	TH1 = 243; //4800 baud
	SCON = 0x50;//1stop bit and 8-bit long
	TR1 = 1;//Start Timer
	KEY = 0xFF;//Read from this port
	while(1){
		do{
			KEY = 0x0F;
			colloc = KEY;
			colloc &=0x0F;
			}while(colloc != 0x0F);
		do{

			do{

				MSDelay(20);
				colloc = KEY;
				colloc &= 0x0F;
			}while(colloc == 0x0F);

			MSDelay(20);
			colloc = KEY;
			colloc &= 0x0F;

		}while(colloc == 0x0F);
		while(1){
			KEY=0xEF;
			colloc = KEY;
			colloc &= 0x0F;
			if(colloc != 0x0F)
			{
				rowloc =0;
				break;
			}

			KEY=0xDF;
			colloc = KEY;
			colloc &= 0x0F;
			if(colloc != 0x0F)
			{
				rowloc =1;
				break;
			}


			KEY=0xBF;
			colloc = KEY;
			colloc &= 0x0F;
			if(colloc != 0x0F)
			{
				rowloc =2;
				break;
			}


			KEY=0x7F;
			colloc = KEY;
			colloc &= 0x0F;
			rowloc =3;
			break;
		}
		if(colloc == 0x0E){
			SerTx(keypad[rowloc][0]);
			PRESS =keypad[rowloc][0]*16;}
		else if(colloc == 0x0D){
  		SerTx(keypad[rowloc][1]);
			PRESS =keypad[rowloc][1]*16;}	
			else if(colloc == 0x0B){
			SerTx(keypad[rowloc][2]);		
			PRESS =keypad[rowloc][2]*16;}
			else{
			SerTx(keypad[rowloc][3]);
			PRESS =keypad[rowloc][3]*16;}		
			
	}
}

void SerTx(int x)
{
	SBUF = x;
	while(TI==0);
	TI = 0;
}

void MSDelay(unsigned int value)
{
	unsigned int x, y;
	for(x=0;x<1275;x++)
		for(y=0;y<value;y++);
}