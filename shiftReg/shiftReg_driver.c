#include"shiftReg_driver.h"

unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};


static void shrPulse(int pin)
{
	digitalWrite(pin, 0);
	digitalWrite(pin, 1);
}

static void shrOut(unsigned char byte)
{
	int i;
	unsigned char temp = 0;
	for(i=0;i<8;i++)
	{
		temp = byte & (0x80>>i);
		digitalWrite(SHR_SDI,temp>0);
		shrPulse(SHR_SRCLK);
	}
}

void shrInit(void)
{
	wiringPiSetup();
	wiringPiSetupGpio();

	pinMode(SHR_SDI, OUTPUT);
	pinMode(SHR_RCLK, OUTPUT);
	pinMode(SHR_SRCLK, OUTPUT);

	digitalWrite(SHR_SDI, 0);
	digitalWrite(SHR_RCLK, 0);
	digitalWrite(SHR_SRCLK, 0);
}

static void shrClear()
{
	shrOut(0x00);
	shrPulse(SHR_RCLK);
	delay(100);
}

static void shrSet()
{
	shrOut(0xFF);
	shrPulse(SHR_RCLK);
	delay(100);
}

static void shrSetVal(unsigned char val)
{
	shrOut(val);
	shrPulse(SHR_RCLK);
	delay(100);
}

void shrLedOut(char totalPlayer,char selPlayer)
{
	unsigned char temp = 0;
	static char stemp =  0;

	if(totalPlayer == 0)
	{
		if(selPlayer == 1)
		{
			shrSet();
		}
		else
		{
			shrClear();
		}
	}
	else if(totalPlayer == 8)
	{
		switch(selPlayer)
		{
			case 1:
				shrClear();
				temp = LED[0];
				shrSetVal(temp);
				break;
			case 2:
				shrClear();
				temp = LED[1];
				shrSetVal(temp);
				break;
			case 3:
				shrClear();
				temp = LED[2];
				shrSetVal(temp);
				break;
			case 4:
				shrClear();
				temp = LED[3];
				shrSetVal(temp);
				break;
			case 5:
				shrClear();
				temp = LED[4];
				shrSetVal(temp);
				break;
			case 6:
				shrClear();
				temp = LED[5];
				shrSetVal(temp);
				break;
			case 7:
				shrClear();
				temp = LED[6];
				shrSetVal(temp);
				break;
			case 8:
				shrClear();
				temp = LED[7];
				shrSetVal(temp);
				break;
			default:
				break;

		}
	}
	else if(totalPlayer == 4)
	{
		switch(selPlayer)
		{
			case 1:
			case 2:
				temp = LED[0]|LED[1];
				if(stemp == temp)
					return;
				stemp = temp;
				shrClear();
				shrSetVal(temp);
				break;
			case 3:
			case 4:
				temp = LED[2]|LED[3];
				if(stemp == temp)
					return;
				stemp = temp;
				shrClear();
				shrSetVal(temp);
				break;
			case 5:
			case 6:
				temp = LED[4]|LED[5];
				if(stemp == temp)
					return;
				stemp = temp;
				shrClear();
				shrSetVal(temp);
				break;
			case 7:
			case 8:
				temp = LED[6]|LED[7];
				if(stemp == temp)
					return;
				stemp = temp;
				shrClear();
				shrSetVal(temp);
				break;
			default:
				break;
		}
	}
	else if(totalPlayer == 2)
	{
		if(selPlayer)
		switch(selPlayer)
		{
			case 1:
			case 2:
			case 3:
			case 4:
				temp = LED[0]|LED[1]|LED[2]|LED[3];
				if(stemp == temp)
					return;
				stemp = temp;
				shrClear();
				shrSetVal(temp);
				break;
			case 5:
			case 6:
			case 7:
			case 8:
				temp = LED[4]|LED[5]|LED[6]|LED[7];
				if(stemp == temp)
					return;
				stemp = temp;
				shrClear();
				shrSetVal(temp);
				break;
			default:
				break;
		}
	}
}


