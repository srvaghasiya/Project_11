#ifndef _COMM_DRIVER_H_
#define _COMM_DRIVER_H_

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>

extern char cmdRecv[10];

extern int uartInit();
extern void uartTerminate();

extern int commMsgSend(char *);
char *commMsgRecv(void);

#endif
