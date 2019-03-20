#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<wiringPi.h>

#define SEC_TO_MICROSEC(x)	((x)*1000000)
#define ROTOR_DELAY_SEC		0.1

extern volatile char rotorCurPos,rotorPrevPos;
extern volatile long long cnt;

extern int rotorReedPinsInit(void);

extern void *rotor(void *arg);
