#include"comm_driver.h"

// to store received command
char cmdRecv[10];

// variable to store serial stream
static int file;

// Init function to initialize and open serial port ttyAMA0
int uartInit()
{
	// open serial port ttyAMA0
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

// Close the serial port file
void uartTerminate()
{
	close(file);
}

// Send message on UART
int commMsgSend(char *msg)
{
	int count;

	if((count = write(file, msg, strlen(msg)))<0)
	{
		perror("UART: Failed to write to the output\n");
		return -1;
	}
	
	write(file, "\n", 1);
}

// Receive message from UART. returns address of received string
char* commMsgRecv(void)
{
	int count = 0;
	char c;

	while(1)
	{
		if(read(file,&c,1)>0)
		{
			cmdRecv[count++] =c;
			if(c=='\n')   // end the string when new line character receives
			{
				cmdRecv[count-1]='\0';
				break;
			}
		}
	}
	return cmdRecv;
}
