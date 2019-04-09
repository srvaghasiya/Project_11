
#include"rotor_driver.h"

// here we need to Pin numbedrs not GPIO number
char rotorReedPins[8]={18,23,24,25,8,7,12,16};

volatile char rotorCurPos = 0,rotorPrevPos = 0;
volatile long long cnt = 0;

float rotorRPM;

int rotorStopCnt;

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
	rotorCurPos = 1;
	cnt++;
	shrLedOut(noOfPlayers,rotorCurPos);
//	print();
}

void rotorCntIsr1(void)
{
	rotorPrevPos = rotorCurPos;
	rotorCurPos = 2;
	cnt++;
	shrLedOut(noOfPlayers,rotorCurPos);
//	print();
}

void rotorCntIsr2(void)
{
	rotorPrevPos = rotorCurPos;
	rotorCurPos = 3;
	cnt++;
	shrLedOut(noOfPlayers,rotorCurPos);
//	print();
}

void rotorCntIsr3(void)
{
	rotorPrevPos = rotorCurPos;
	rotorCurPos = 4;
	cnt++;
	shrLedOut(noOfPlayers,rotorCurPos);
//	print();
}

void rotorCntIsr4(void)
{
	rotorPrevPos = rotorCurPos;
	rotorCurPos = 5;
	cnt++;
	shrLedOut(noOfPlayers,rotorCurPos);
//	print();
}

void rotorCntIsr5(void)
{
	rotorPrevPos = rotorCurPos;
	rotorCurPos = 6;
	cnt++;
	shrLedOut(noOfPlayers,rotorCurPos);
//	print();
}

void rotorCntIsr6(void)
{
	rotorPrevPos = rotorCurPos;
	rotorCurPos = 7;
	cnt++;
	shrLedOut(noOfPlayers,rotorCurPos);
//	print();
}

void rotorCntIsr7(void)
{
	rotorPrevPos = rotorCurPos;
	rotorCurPos = 8;
	cnt++;
	shrLedOut(noOfPlayers,rotorCurPos);
//	print();
}

//void (*rotorCntIsr[8])(void) = {rotorCntIsr0,rotorCntIsr1,rotorCntIsr2,rotorCntIsr3,rotorCntIsr4,rotorCntIsr5,rotorCntIsr6,rotorCntIsr7};


int rotorReedPinsInit()
{
	int i;
	wiringPiSetup();
	wiringPiSetupGpio();
	for(i=0;i<8;i++)
	{
		pullUpDnControl(rotorReedPins[i],PUD_UP);
//		wiringPiISR(rotorReedPins[i],INT_EDGE_FALLING,rotorCntIsr[i]);
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
//int main()
{
	int startCntFlag;
	rotorReedPinsInit();
	
	startCntFlag = 0;
	while(1)
	{

		pthread_mutex_lock(&rotorMutex_rpm);
//		rotorRPM = rotorRpmCnt();
//
//		testing purpose only remove this lines once testing done.
		printf("Enter RPM for testing : ");
		scanf("%f",&rotorRPM);
		printf("rotorStopCnt : %d\n",rotorStopCnt);
		if(rotorRPM != 0.0)
		{
			printf("Enter cur pos:");
			scanf("%d",&rotorCurPos);
		}

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
//for testing its 2 make 20 for real
		if(rotorStopCnt == 2)
		{
			startCntFlag = 0;
			pthread_cond_signal(&rotorCond_stop);
			printf("after signal..\n");
			usleep(SEC_TO_MICROSEC(ROTOR_DELAY_SEC));
//			pthread_exit(0);
		}

		printf("rpm : %f\n",rotorRPM);  //for testing purpose
		printf("cur pos : %d\n",rotorCurPos); //for testing purpose
		usleep(SEC_TO_MICROSEC(ROTOR_DELAY_SEC));
			
	}
}
