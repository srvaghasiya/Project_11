
#include"rotor_driver.h"

// here we need to Pin numbedrs not GPIO number
char rotorReedPins[8]={18,23,24,25,8,7,12,16};

volatile char rotorCurPos = 0,rotorPrevPos = 0;
volatile long long cnt = 0;

float rotorRPM;

int rotorStopCnt;

char rotorLedEnableFlag = 0;

pthread_mutex_t rotorMutex_rpm;
pthread_cond_t rotorCond_start;
pthread_cond_t rotorCond_stop;

void print()
{
	printf("\ncnt: %d\n,current: %d\nprev: %d\n\n",cnt,rotorCurPos,rotorPrevPos);
}

void rotorCntIsr0(void)
{
	rotorPrevPos = rotorCurPos;
//	rotorCurPos = 1;
	rotorCurPos = 5;
	printf("pos: %d\n",rotorCurPos);
	cnt++;
	if(!rotorLedEnableFlag)
		shrLedOut(noOfPlayers,rotorCurPos);
}

void rotorCntIsr1(void)
{
	rotorPrevPos = rotorCurPos;
//	rotorCurPos = 2;
	rotorCurPos = 6;
	printf("pos: %d\n",rotorCurPos);
	cnt++;
	if(!rotorLedEnableFlag)
		shrLedOut(noOfPlayers,rotorCurPos);
}

void rotorCntIsr2(void)
{
	rotorPrevPos = rotorCurPos;
//	rotorCurPos = 3;
	rotorCurPos = 7;
	printf("pos: %d\n",rotorCurPos);
	cnt++;
	if(!rotorLedEnableFlag)
		shrLedOut(noOfPlayers,rotorCurPos);
}

void rotorCntIsr3(void)
{
	rotorPrevPos = rotorCurPos;
//	rotorCurPos = 4;
	rotorCurPos = 8;
	printf("pos: %d\n",rotorCurPos);
	cnt++;
	if(!rotorLedEnableFlag)
		shrLedOut(noOfPlayers,rotorCurPos);
}

void rotorCntIsr4(void)
{
	rotorPrevPos = rotorCurPos;
//	rotorCurPos = 5;
	rotorCurPos = 1;
	printf("pos: %d\n",rotorCurPos);
	cnt++;
	if(!rotorLedEnableFlag)
		shrLedOut(noOfPlayers,rotorCurPos);
}

void rotorCntIsr5(void)
{
	rotorPrevPos = rotorCurPos;
//	rotorCurPos = 6;
	rotorCurPos = 2;
	printf("pos: %d\n",rotorCurPos);
	cnt++;
	if(!rotorLedEnableFlag)
		shrLedOut(noOfPlayers,rotorCurPos);
}

void rotorCntIsr6(void)
{
	rotorPrevPos = rotorCurPos;
//	rotorCurPos = 7;
	rotorCurPos = 3;
	printf("pos: %d\n",rotorCurPos);
	cnt++;
	if(!rotorLedEnableFlag)
		shrLedOut(noOfPlayers,rotorCurPos);
}

void rotorCntIsr7(void)
{
	rotorPrevPos = rotorCurPos;
//	rotorCurPos = 8;
	rotorCurPos = 4;
	printf("pos: %d\n",rotorCurPos);
	cnt++;
	if(!rotorLedEnableFlag)
		shrLedOut(noOfPlayers,rotorCurPos);
}


int rotorReedPinsInit()
{
	int i;
	wiringPiSetup();
	wiringPiSetupGpio();
	for(i=0;i<8;i++)
	{
		pullUpDnControl(rotorReedPins[i],PUD_UP);
	}
	wiringPiISR(rotorReedPins[0],INT_EDGE_FALLING,&rotorCntIsr0);
	wiringPiISR(rotorReedPins[1],INT_EDGE_FALLING,&rotorCntIsr1);
	wiringPiISR(rotorReedPins[2],INT_EDGE_FALLING,&rotorCntIsr2);
	wiringPiISR(rotorReedPins[3],INT_EDGE_FALLING,&rotorCntIsr3);
	wiringPiISR(rotorReedPins[4],INT_EDGE_FALLING,&rotorCntIsr4);
	wiringPiISR(rotorReedPins[5],INT_EDGE_FALLING,&rotorCntIsr5);
	wiringPiISR(rotorReedPins[6],INT_EDGE_FALLING,&rotorCntIsr6);
	wiringPiISR(rotorReedPins[7],INT_EDGE_FALLING,&rotorCntIsr7);

}

static float rotorRpmCnt()
{
	static long long prev;
	long long current,diffrence;

	current = cnt;

	diffrence = current - prev;

	prev = current;

	return ((diffrence*60.0)/(8.0*ROTOR_DELAY_SEC));
}

void *rotor(void *arg)
{
	int startCntFlag;
	rotorReedPinsInit();
	
	startCntFlag = 0;
	while(1)
	{

		pthread_mutex_lock(&rotorMutex_rpm);
		rotorRPM = rotorRpmCnt();
		
		if(startCntFlag == 1)
		{
			if(rotorRPM == 0.0)
			{
				rotorStopCnt++;
			}
			else
			{
				rotorStopCnt = 0;
			}

		}

		pthread_mutex_unlock(&rotorMutex_rpm);

		if(rotorRPM > 0.0)
		{
			startCntFlag = 1;
			pthread_cond_signal(&rotorCond_start);
		}
		
		if(rotorStopCnt == 20)
		{
			startCntFlag = 0;
			pthread_cond_signal(&rotorCond_stop);
			usleep(SEC_TO_MICROSEC(ROTOR_DELAY_SEC));
		}

		usleep(SEC_TO_MICROSEC(ROTOR_DELAY_SEC));
			
	}
}
