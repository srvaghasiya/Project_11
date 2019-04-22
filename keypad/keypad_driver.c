#include"keypad_driver.h"
#include<stdio.h>

const uint8 r[4]={4,17,27,22};
const uint8 c[4]={10,9,11,5};

uint8 abc=128;

void init_pins()
{
	uint8 i;
	wiringPiSetup();
	wiringPiSetupGpio();
	
	/* row init */
	for(i=0;i<4;i++)
	{
		pinMode(r[i],OUTPUT);
		digitalWrite(r[i],LOW);
	}
	
	/* col init */
	for(i=0;i<4;i++)
	{
		pinMode(c[i],INPUT);
		pullUpDnControl(c[i],PUD_UP);
	}
}

const uint8 keypad_lut[4][4]={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

void high_rows(void)
{
	uint8 i;

	for(i=0;i<4;i++)
	{
		digitalWrite(r[i],HIGH);
	}

}

uint8 colscan(void)
{
	uint8 i;

	for(i=0;i<4;i++)
	{
		if(LOW == digitalRead(c[i]))
		{
			return i;
		}
	}

	return 5;
}

uint8 keyscan(void)
{
	volatile uint8 i,row=5,col=5;
	static uint8 state;

	init_pins();

	do
	{
		col=colscan();
	}while(col > 3);

	high_rows();

	for(i=0;i<4;i++)
	{
		digitalWrite(r[i],LOW);

		if(colscan() < 4)
		{
			row = i;
			digitalWrite(r[i],LOW);
			break;
		}

		digitalWrite(r[i],HIGH);
	}

	while(colscan() < 4);
	
	if(row<4 && col<4)
		state = keypad_lut[row][col];

	printf("%c\n",state);

	return state;
}
