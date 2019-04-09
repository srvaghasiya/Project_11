#ifndef _SHIFT_REG_DRIVER_H_
#define _SHIFT_REG_DRIVER_H_

#include<wiringPi.h>
#include<stdio.h>


//Pin nnumbers need to finalise temp given 1 2 3
#define SHR_SDI		6
#define SHR_RCLK	13
#define SHR_SRCLK	19

extern void shrInit(void);
extern void shrLedOut(char,char);

#endif
