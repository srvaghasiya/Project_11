#include"comm_driver.h"

char cmdRecv[10];
static int file;

int uartInit()
{
	if((file = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY))<0)
	{
		perror("UART: Failed to open the device.\n");
		return -1;
	}
	struct termios options;
	tcgetattr(file, &options);
	options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
	options.c_iflag = IGNPAR | ICRNL;
	tcflush(file, TCIFLUSH);
	tcsetattr(file, TCSANOW, &options);
	return 0;
}

void uartTerminate()
{
	close(file);
}


int commMsgSend(char *msg)
{
	int count;

//	printf("send msg : %s\n",msg);

	if((count = write(file, msg, strlen(msg)))<0)
	{
		perror("UART: Failed to write to the output\n");
		return -1;
	}
	
	write(file, "\n", 1);
}

char* commMsgRecv(void)
{
	int count = 0;
	char c;

	while(1)
	{
		if(read(file,&c,1)>0)
		{
//			printf("in rec: %c\n",c);
			cmdRecv[count++] =c;
			if(c=='\n')
			{
//				printf("here\n");
				cmdRecv[count-1]='\0';
				break;
			}
		}
	}
//	printf("return:%s\n",cmdRecv);
	return cmdRecv;
}
/*
int main()
{
	char cmd[100];
	char abc;
	char rcv[100];
	uartInit();
	while(1)
	{
		printf("Enter command:");
		scanf("%s",cmd);
		commMsgSend(cmd);
		abc = 0;
		do
		{
			strcpy(rcv,commMsgRecv());
//			printf("%s\n",rcv);
			abc = rcv[0];
//			printf("%c\t%d\n",abc,abc);
		}while(!(abc == 't' || abc =='n' || abc=='l'));
		printf("%c\n",abc);
	}
	uartTerminate();
}*/
