#ifndef _ROTOR_H_
#define _ROTOR_H_


#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<wiringPi.h>
#include"../application/app.h"
#include"../shiftReg/shiftReg_driver.h"



#define SEC_TO_MICROSEC(x)	((x)*1000000)
#define ROTOR_DELAY_SEC		0.1

extern volatile char rotorCurPos,rotorPrevPos;
extern volatile long long cnt;

extern float rotorRPM;
extern int rotorStopCnt;

extern pthread_mutex_t rotorMutex_rpm;
extern pthread_cond_t rotorCond_start;
extern pthread_cond_t rotorCond_stop;

extern int rotorReedPinsInit(void);

extern void *rotor(void *arg);


#endif
