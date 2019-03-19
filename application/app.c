#include"app.h"
#define DELAY 400000
#define TEST

char mode;
char noOfPlayers;
char phoneNumbers[8][11];

void lcd_scroll(char *str1,char *str2,int flg)
{
	char str_up[17];
	char str_down[17];
	int i;
	memset(str_up,' ',16);
	memset(str_down,' ',16);

	str_up[16]='\0';
	str_down[16]='\0';

	ClrLcd();

	for(i=0;i<16;i++)
	{
	       memset(str_up,' ',16);
       	       memset(str_down,' ',16);
	       memcpy(str_up,str1+15-i,i+1);
	       memcpy(str_down+15-i,str2,i+1);
	       lcdLoc(LINE1);
	       typeln(str_up);
	       lcdLoc(LINE2);
	       typeln(str_down);
	       usleep(DELAY); 
	}

	if(flg == 1)
	{
	
		for(i=0;i<5;i++)
		{
			ClrLcd();
			usleep(DELAY);
		       	lcdLoc(LINE1);  
		       	typeln(str_up);
			lcdLoc(LINE2);
			typeln(str_down);
			usleep(DELAY); 
		}
	
		sleep(2);
	}
	else if(flg==0)
	{
		sleep(2);
	}
	
}

void greeting()
{
	lcd_scroll("TRUTH  O     >>>","<<<     R   DARE",1);
	lcd_scroll("<<<   TEAM   >>>","<<<    11    >>>",0);
	lcd_scroll("<<<   Guide  >>>"," Mike and Takiz ",0);
	lcd_scroll("<<<   LETS   >>>","    HAVE FUN    ",0);
}

void simple_lcd(char *str1,char *str2)
{
	ClrLcd();
	lcdLoc(LINE1);
	typeln(str1);
	lcdLoc(LINE2);
	typeln(str2);
}

void line_lcd(char line,char *str)
{
	lcdLoc(line);
	typeln("                ");
	lcdLoc(line);
	typeln(str);
}

char manOrauto()
{
	char c;
	simple_lcd("  select mode   ","1 Wifi 2 Offline");
	do
	{
#ifdef TEST
		scanf("%d",&c);
		while(getchar()!='\n');
	}while(!(c==1 || c == 2));
#else
		c = keyscan();
		usleep(500000);
	}while(!(c=='1' || c == '2'));
#endif
	return c;

}

char getPlayers()
{
	char c;

	simple_lcd("No. of Players ","   8 or 4 or 2  ");

	do
	{
#ifdef TEST
		scanf("%d",&c);
		while(getchar()!='\n');
	}while(!(c==2 || c==4 || c==8));
#else
		c = keyscan();
		usleep(500000);
	}while(!(c=='2' || c=='4' || c=='8'));
#endif
}

void getPhoneNumbers()
{
	char i,cnt,c,t;
	char str[16];
	line_lcd(LINE1,"Enter Phone No: ");
	for(i=0;i<noOfPlayers;i++)
	{
	//	cnt =0;
		for(cnt=0;cnt<11;cnt++)
		{
			sprintf(str,"P%d: %s",i+1,phoneNumbers[i]);
			line_lcd(LINE2,str);
			if(cnt==10)
			{
				line_lcd(LINE1,"A:Save  B:Cancel");
				do
				{
#ifdef TEST
					scanf("%c",&t);
					while(getchar()!='\n');
#else
					t = keyscan();
					usleep(500000);
#endif
				}while(!(t=='A' || t=='B'));

				printf("%c\n",t);
							
				if(t == 'A')
				{	
					line_lcd(LINE2,"                ");
					line_lcd(LINE2,"SAVED..!!");
					usleep(3*DELAY); 
				}
				else if(t == 'B')
				{
					memset(phoneNumbers[i],0,16);
					i--;
					line_lcd(LINE2,"                ");
					line_lcd(LINE2,"CANCELLED..!!");
					usleep(3*DELAY); 
				}
				else
				{

				}	
				line_lcd(LINE1,"Enter Phone No: ");

				break;
			}
			do
			{
#ifdef TEST
				{
					scanf("%c",&phoneNumbers[i][cnt]);
					while(getchar()!='\n');
				}
#else
				phoneNumbers[i][cnt] = keyscan();
				usleep(500000);
#endif
				printf("%d\n",!(phoneNumbers[i][cnt]>='0' && phoneNumbers[i][cnt]<='9'));
			}while(!(phoneNumbers[i][cnt]>='0' && phoneNumbers[i][cnt]<='9'));	
		}
	}

}

#ifdef TEST
void printPh()
{
	int i;
	for(i=0;i<noOfPlayers;i++)
		printf("%s\n",phoneNumbers[i]);
}
#endif

int main()
{
	lcd_init();
//	greeting();
	mode = manOrauto();
	noOfPlayers = getPlayers();

	switch(mode)
	{
		case 1:
#ifdef TEST
			printf("mode:%d\tplayers:%d\n",mode,noOfPlayers);
			getPhoneNumbers();
			printPh();

#endif
			break;
		case 2:
#ifdef TEST
			printf("mode:%d\tplayers:%d\n",mode,noOfPlayers);
#endif
			break;
		default:
			break;
	}
}
