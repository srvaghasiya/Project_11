#include"app.h"
#define DELAY 400000
#define KEYPAD_DELAY 450000
//#define TEST


char *truth[37]  = 
{
	"Name ten body parts that your partner likes to kiss?",
    	"Say a list of 10 items or things you bought and never used or regretted buying?",
    	"If you were the opposite sex for one hour, what would you do?",
  	"What was the most embarrassing moment of your life?",
    	"Have you ever been humiliated? Explain what happened and how you felt?",
    	"Describe the strangest dream you've had in your life?",
    	"Which player would you like to swap lives with for a week?",
    	"What physical feature do you get complimented on the most?",
    	"What is that one thing you would never do even if someone offered you all of the money in the world?",
    	"Among all the people in this room, which guy/girl would you like to date?",
    	"Who in the room do you think would be a bad date?",
    	"What is the quality or characteristic that would like to change about you?",
    	"Have you fallen in love with a friend of your partner? Has anyone noticed?",
    	"What do you think that your boyfriend/girlfriend thinks about marriage?",
    	"What was the craziest thing that has happened to you in a mall?",
    	"Mention the most annoying experience in some shopping?",
    	"What is the meanest thing you have done in your life?", 
    	"Have you ever thought of cheat on your boyfriend/girlfriend?",
    	"Have you ever lied to your partner to avoid an intimate moment, for example, say that you feel sick?",
    	"What is the worst rumor or gossip you said or repeated and at the end was something wrong?",
    	"What was the most disgusting joke ever played with someone?",
    	"What's your wildest fantasy?",
    	"Have you ever peed in a pool?",
    	"What is the most stupid thing you've done in front of a crowd?",
    	"What's the first thing you would do if you were invisible?", 
    	"Have you ever been hinted or has overstepped someone of the same sex? What happened, how did you react?",
    	"Which of the players in this group considered to have the most sensual and daring clothes?",
    	"Who do you think is the worst party dress? What would you recommend?",
    	"You might think that someone of your friends or family made a terrible decision for life says who and what s/he did?",
    	"Say who (here) has a wrong partner or does not suit him?",
    	"If you were marooned on an island with one person whom you know personally, who would like it to be that person?",
    	"He mentions something that ever done and that you did not want to be known?",
    	"What is the dumbest thing you've said your partner while on intimacy?",
    	"Have you ever picked your nose and eaten it?",
    	"Which of the people who are in this game, considered to have the best body?",
    	"Which of the people who are in this game, believes it has lately deteriorated their physical appearance: his body, his dress?",
    	"If you could suddenly become invisible, what more naughty things you like to do?"
};

char *dare[42] =
{
	"Go up to someone and scare them",
	"Very affectionately kiss another participant (the rest can choose whom)",
	"Give a massage to a companion for 5 minutes",
	"Eat a tablespoon of butter",
	"Asks for money on the street telling a funny story and nothing credible and board 50$",
	"Sing and dance in the street like crazy",
	"Become the slave of another player of your choosing for 5 mins",
	"Embrace the first passing through the stree",
	"Dance with a broom or mop",
	"For guys: Briefly walk like a lady in high heel",
	"Climb to sing in the bar of a bar",
	"Declare who is your true love",
	"Tell something very intimate",
	"Sing the alphabet without moving your mouth",
	"Do your best president impression",
	"Yell out the first word that comes to your mind right now",
	"Call the pizza place and order 300 sardine pizzas",
	"Once you have your eyes closed, feel someones face and guess who they are",
	"Make up a story about the item to your right",
	"Sing everything you say for the next 10 minutes",
	"Give a foot massage to someone present",
	"Give the person to your left a hickey",
	"Say the alphabet backward in 15 seconds",
	"Ask a random stranger to make out with you",
	"Act like you do not understand your language until your next turn (come up with your language)",
	"Do pushups until its your turn again",
	"Wear a finger mustache for the next 5 minutes",
	"Eat a raw egg",
	"Bark like a dog\",Sing a song all the way through to the end",
	"Dance wildly to your favorite song",
	"Act like a dog and get petted by everyone",
	"Get a shower with all your clothes on",
	"Draw a face around your belly button",
	"Let someone write a word on your forehead in permanent marker",
	"Post an embarrassing picture of yourself online",
	"Put ice cube down bra or underwear and wait till melts",
	"Act like an old lady or an old man",
	"Spin around ten times, when you get done, try to walk in a straight line",
	"Go a whole minute without blinking",
	"Say banana after everything you say until it is your turn again",
	"Act like a monkey until it is your turn again"
};


char mode;
char noOfPlayers;
char phoneNumbers[8][11];
char appSpinFlag = 0;
char appQueFlag = 0;
char appLedBlinkFlag = 0;

pthread_mutex_t appMutex,appMutex1;

void voiceOutput(char *str,char c)
{
	char voiceStr[400] = "pico2wave -w ./sound/temp.wav \"";
	strcat(voiceStr,str);
	if(c == 0)
		strcat(voiceStr," \" && aplay ./sound/temp.wav");
	else

		strcat(voiceStr," \" && aplay ./sound/temp.wav &");
	system(voiceStr);
}

void greeting()
{
	lcd_scroll("TRUTH  O     >>>","<<<     R   DARE",1);
	lcd_scroll("<<<   TEAM   >>>","<<<    11    >>>",0);
	lcd_scroll("<<<  Guides  >>>"," TAKIS  &  MIKE ",0);
	lcd_scroll("<<<   LETS   >>>","    HAVE FUN    ",0);
}

char manOrauto()
{
	char c;
	simple_lcd("  select mode   ","A:Wifi B:Offline");
	voiceOutput("Select mode of game",1);
	do
	{
		c = keyscan();
		usleep(KEYPAD_DELAY);
	}while(!(c=='A' || c == 'B'));
	return c;

}

char getPlayers()
{
	char c;

	simple_lcd("No. of Players ","   8 or 4 or 2  ");
	voiceOutput("Select Number of Players",1);

	do
	{
		c = keyscan();
		usleep(KEYPAD_DELAY);
	}while(!(c=='2' || c=='4' || c=='8'));
	c = c-'0';
	return c;
}

void getPhoneNumbers()
{
	char i,cnt,c,t;
	char str[16];
	char str1[100];
	line_lcd(LINE1,"Enter Phone No: ");
	for(i=0;i<noOfPlayers;i++)
	{
		sprintf(str1,"Enter phone number for player %d",i+1);
		voiceOutput(str1,1);
		for(cnt=0;cnt<11;cnt++)
		{
			sprintf(str,"P%d: %s",i+1,phoneNumbers[i]);
			line_lcd(LINE2,str);
			if(cnt==10)
			{
				printf("here in getPhone number if\n");
				voiceOutput("Ae for Save B for re-enter",1);
				line_lcd(LINE1,"A:Save  B:Cancel");
				do
				{
					t = keyscan();
					usleep(KEYPAD_DELAY);
				}while(!(t=='A' || t=='B'));

				if(t == 'A')
				{	
					line_lcd(LINE2,"                ");
					line_lcd(LINE2,"SAVED..!!");
					voiceOutput("saved",0);
					usleep(3*DELAY); 
				}
				else if(t == 'B')
				{
					memset(phoneNumbers[i],0,16);
					i--;
					line_lcd(LINE2,"                ");
					line_lcd(LINE2,"CANCELLED..!!");
					voiceOutput("Cancelled",0);
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
				phoneNumbers[i][cnt] = keyscan();
				usleep(KEYPAD_DELAY);
			}while(!(phoneNumbers[i][cnt]>='0' && phoneNumbers[i][cnt]<='9'));
		}
	}

}

void printPh()
{
	int i;
	for(i=0;i<noOfPlayers;i++)
		printf("%s\n",phoneNumbers[i]);
}

void *lcd_spin_start(void *arg)
{
	pthread_mutex_lock(&rotorMutex_rpm);
	while(!(rotorRPM > 0.0))
	{
		pthread_cond_wait(&rotorCond_start,&rotorMutex_rpm);
	}
	line_lcd(LINE2,"Spin Started...");
	system("play -q sound/spinning.mp3 &");
	rotorLedEnableFlag = 0;
	rotorStopCnt = 0;
	pthread_mutex_unlock(&rotorMutex_rpm);
}

void *lcd_spin_stop(void *arg)
{
	pthread_mutex_lock(&rotorMutex_rpm);
	while(rotorStopCnt == 0)
	{
		pthread_cond_wait(&rotorCond_stop,&rotorMutex_rpm);
	}
	appSpinFlag = 2;
	line_lcd(LINE2,"Spinner Stopped.");
	rotorStopCnt = 0;
	rotorLedEnableFlag = 1;
	system("pkill play");

//	usleep(1000);
	system("play -q sound/stop2.mp3");
	pthread_mutex_unlock(&rotorMutex_rpm);
}

void *lcd_question_gen(void *arg)
{
	char flag = 0;
	while(1)
	{
		pthread_mutex_lock(&appMutex);
		if(appQueFlag == 1)
		{
			appQueFlag = 0;
			pthread_mutex_unlock(&appMutex);
			pthread_exit(0);
		}
		pthread_mutex_unlock(&appMutex);

		if(flag == 0)
		{
			line_lcd(LINE2,"A: Generate Que");
			flag = 1;
		}
		else
		{
			line_lcd(LINE2,"B: Ask Manually");
			flag = 0;
		}
		sleep(1);
	}
}

void *lcd_new_round(void *arg)
{
	char flag = 0;
	while(1)
	{
		pthread_mutex_lock(&appMutex);
		if(appQueFlag == 1)
		{
			appQueFlag = 0;
			pthread_mutex_unlock(&appMutex);
			pthread_exit(0);
		}
		pthread_mutex_unlock(&appMutex);

		if(flag == 0)
		{
			line_lcd(LINE2,"A: Next Round");
			flag = 1;
		}
		else
		{
			line_lcd(LINE2,"D: Exit Game");
			flag = 0;
		}
		sleep(1);

	}
	
}

void *lcd_timer(void *arg)
{
	int time,i;
	char str[16];
	time = (int)arg;
	
	while(time--)
	{
		sprintf(str,"%d",time+1);
		voiceOutput(str,1);
		sprintf(str,"Time left : %d",time+1);
		line_lcd(LINE2,str);
		usleep(866667);
	}
}

void *led_blink(void *arg)
{
	char flag = 0;
	while(1)
	{
		pthread_mutex_lock(&appMutex1);
		if(appLedBlinkFlag == 1)
		{
			appLedBlinkFlag = 0;
			pthread_mutex_unlock(&appMutex1);
			pthread_exit(0);
		}
		pthread_mutex_unlock(&appMutex1);

		if(flag == 0)
		{
			shrLedOut(0,1);
			flag = 1;
		}
		else
		{
			shrLedOut(0,0);
			flag = 0;
		}
		sleep(1);
	}
	
}

char lieDetector()
{
	char ans;

	uartInit();
	commMsgSend("s");
	do
	{
		ans = (commMsgRecv())[0];
	}while(!(ans == 't' || ans == 'n' || ans =='l'));
	uartTerminate();

	return ans;
}

void game_begin()
{
	char temp_sp,temp_cp,input,input1,input2,input3;
	pthread_t pid_rotor;
	pthread_t pid_lcd_spin_start;
	pthread_t pid_lcd_spin_stop;
	pthread_t pid_lcd_spinning;
	pthread_t pid_lcd_question_gen;
	pthread_t pid_lcd_new_round;
	pthread_t pid_lcd_timer;
	char str[16];
	char str1[100];
	int rndCnt=1;
	int temp;
	char lieDetectorAns;
	int randomNum;

	srand(getpid());


	line_lcd(LINE1,"Game begins...");
	voiceOutput("Game Begins",1);
	line_lcd(LINE2,"              ");
	sleep(1);

	pthread_create(&pid_rotor,NULL,&rotor,NULL);
	while(1)
	{
		sprintf(str,"Round : %d",rndCnt);
		line_lcd(LINE2,"            ");
		line_lcd(LINE1,str);
		voiceOutput(str,0);

		line_lcd(LINE2,"Spin Bottle...");
		voiceOutput("Spin the Bottle",1);
		rotorStopCnt = 0;


		pthread_create(&pid_lcd_spin_start,NULL,&lcd_spin_start,NULL);
		pthread_create(&pid_lcd_spin_stop,NULL,&lcd_spin_stop,NULL);

		pthread_join(pid_lcd_spin_start,NULL);
		pthread_join(pid_lcd_spin_stop,NULL);

		if(noOfPlayers == 8)
		{
			temp_sp = rotorCurPos;
			if(temp_sp>4)
			{
				temp_cp = (temp_sp+4)%8;
			}
			else
			{
				temp_cp = temp_sp+4;
			}
		}
		else if(noOfPlayers == 4)
		{
			switch(rotorCurPos)
			{
				case 1:
				case 2:
					temp_sp = 1;
					temp_cp = 3;
					break;
				case 3:
				case 4:
					temp_sp = 2;
					temp_cp = 4;
					break;
				case 5:
				case 6:
					temp_sp = 3;
					temp_cp = 1;
					break;
				case 7:
				case 8:
					temp_sp = 4;
					temp_cp = 2;
					break;
				default:
					break;

			}
		}
		else if(noOfPlayers == 2)
		{
			switch(rotorCurPos)
			{
				case 1:
				case 2:
				case 3:
				case 4:
					temp_sp = 1;
					temp_cp = 2;
					break;
				case 5:
				case 6:
				case 7:
				case 8:
					temp_sp = 2;
					temp_cp = 1;
					break;
				default:
					break;

			}
		}
		else
		{
		}

		sleep(1);
		sprintf(str,"P%d selected..",temp_sp);
		line_lcd(LINE1,str);
		sprintf(str,"P%d ask..",temp_cp);
		line_lcd(LINE2,str);

		sprintf(str1,"Player %d you can ask truth or dare to player %d",temp_cp,temp_sp);
		voiceOutput(str1,0);

//		sleep(2);

		voiceOutput("Ae for Truth or B for Dare..",1);
		line_lcd(LINE1,"A: Truth");
		line_lcd(LINE2,"B: Dare");
		do
		{
			input = keyscan();
			usleep(KEYPAD_DELAY);
		}while(!(input== 'A' || input=='B'));
// truth selected	
		if(input == 'A')
		{
			line_lcd(LINE1,"So its Truth");
			line_lcd(LINE2,"            ");
			
			voiceOutput("ha ha ha Its Truth",0);
			
			sprintf(str1,"Player %d you can take help from system by pressing Ae",temp_cp);
			voiceOutput(str1,1);

			if(pthread_create(&pid_lcd_question_gen,NULL,&lcd_question_gen,NULL)!=0)
			{
				perror("que gen:");
				exit(0);
			}

				
			do{
				input1 = keyscan();
				usleep(KEYPAD_DELAY);
			}while(!(input1== 'A' || input1=='B'));
	
			pthread_mutex_lock(&appMutex);
			appQueFlag = 1;
			pthread_mutex_unlock(&appMutex);

			pthread_join(pid_lcd_question_gen,NULL);
//truth system question
			if(input1 == 'A')
			{
				do
				{
					sprintf(str1,"Player %d here is your help ",temp_cp);
					voiceOutput(str1,0);
					
					line_lcd(LINE1,"Help for You:");
					line_lcd(LINE2,"            ");
					

					sleep(1);
					randomNum = random()%37 + 1;
					sleep(1);


					voiceOutput(truth[randomNum],0);
					line_lcd(LINE2,truth[randomNum]);

					line_lcd(LINE1,"A : next help");
					line_lcd(LINE2,"B : continue");

					do
					{
						input3 = keyscan();
						usleep(KEYPAD_DELAY);
					}while(!(input3== 'A' || input3=='B'));
				}while(input3 != 'B');
			}
//truth  manual mode
			else if(input1 == 'B')
			{
			}
			
			input2 = 0;
			lieDetectorAns = 0;
			sprintf(str,"P%d R u lier?",temp_sp);
			line_lcd(LINE1,str);
			sprintf(str1,"Player %d don't be shy put your finger on lie detector..",temp_sp);
			voiceOutput(str1,1);
			line_lcd(LINE2,"Ask player to put his fingers on Lie Detector..!!");
//			line_lcd(LINE2,"Ask player to put his fingers on Lie Detector..!!");
			
			sprintf(str1,"player %d ask question you have 10 seconds to ask",temp_cp);
			voiceOutput(str1,1);
			sprintf(str,"P%d ask que",temp_cp);
			line_lcd(LINE1,str);

			sleep(2);

			pthread_create(&pid_lcd_timer,NULL,&lcd_timer,10);
			pthread_join(pid_lcd_timer,NULL);
			line_lcd(LINE2,"time over");
			voiceOutput("Time over",1);
			sleep(2);

			voiceOutput("Lie Detector started for 30 seconds",1);			
			line_lcd(LINE1,"Lie Dtctr Strtd");

			sleep(1);

			pthread_create(&pid_lcd_timer,NULL,&lcd_timer,30);
			lieDetectorAns = lieDetector();
			if(rndCnt%3 == 0)
			{
				if(lieDetectorAns != 'n')
					lieDetectorAns = 't';
			}

			pthread_join(pid_lcd_timer,NULL);
			line_lcd(LINE1,"Lie Dtctr Stop");
			line_lcd(LINE2,"time over");
			voiceOutput("Time over",1);
			sleep(2);
			
			if(mode == 'B')
			{
				if(lieDetectorAns == 'n')
				{
					line_lcd(LINE1,"Lie Dtctr Result");
					line_lcd(LINE2,"Player did not touch lie detector..");
					sprintf(str1,"player %d you should touch lie detector",temp_sp);
					voiceOutput(str1,0);
				}
				else if(lieDetectorAns == 't')
				{
					line_lcd(LINE1,"Lie Dtctr Result");
					line_lcd(LINE2,"Player is honest");
					voiceOutput("You are honest",0);
				}
				else if(lieDetectorAns == 'l')
				{
					line_lcd(LINE1,"Lie Dtctr Result");
					line_lcd(LINE2,"Big Lie");
					voiceOutput("Red Aleart It is lie",0);
				}
			}
			else if(mode == 'A')
			{
				int i;
				char str_phone[100];
				
				for(i=0;i<noOfPlayers;i++)
				{
					if((i+1)==temp_sp)
					{
						continue;
					}
					sprintf(str_phone,"python ./twilio/sms.py %s ",phoneNumbers[i]);

					if(lieDetectorAns == 'n')
					{
						line_lcd(LINE1,"Lie Dtctr Result");
						line_lcd(LINE2,"Player did not wear lie detector..");
						break;
					}
					else if(lieDetectorAns == 't')
					{
						strcat(str_phone,"not liar");
					}
					else if(lieDetectorAns == 'l')
					{
						strcat(str_phone,"good liar");
					}
//testing
					system(str_phone);
				}
			}
			sleep(5);

		}

//dare selected
		else if(input == 'B')
		{
			voiceOutput("yes it is dare. press a for help",1);
			line_lcd(LINE1,"You Dare to Dare");
			line_lcd(LINE2,"                ");
			pthread_create(&pid_lcd_question_gen,NULL,&lcd_question_gen,NULL);

			do{
				input1 = keyscan();
				usleep(KEYPAD_DELAY);
			}while(!(input1== 'A' || input1=='B'));

			pthread_mutex_lock(&appMutex);
			appQueFlag = 1;
			pthread_mutex_unlock(&appMutex);

			pthread_join(pid_lcd_question_gen,NULL);
//dare system question
			if(input1 == 'A')
			{
				do
				{

					sprintf(str1,"Player %d here is your help ",temp_cp);
					voiceOutput(str1,1);
					
					line_lcd(LINE1,"Help for You:");
					line_lcd(LINE2,"                ");
					sleep(1);
					
					randomNum = random()%42 + 1;

					sleep(1);
					voiceOutput(dare[randomNum],0);
					line_lcd(LINE2,dare[randomNum]);

					line_lcd(LINE1,"A : next help");
					line_lcd(LINE2,"B : continue");

					do
					{
						input3 = keyscan();
						usleep(KEYPAD_DELAY);
					}while(!(input3== 'A' || input3=='B'));
				}while(input3 != 'B');
	
			}
//dare manual mode
			else if(input1 == 'B')
			{
			}
			else
			{
			}
			input2 = 0;
			sprintf(str1,"Player %d you should finish dare",temp_sp);
			voiceOutput(str1,1);
			sprintf(str,"P%d finish dare",temp_sp);
			line_lcd(LINE1,str);
			line_lcd(LINE2,"                ");
			sleep(10);
		} // dare ending
		else
		{
		}
		
		pthread_create(&pid_lcd_new_round,NULL,&lcd_new_round,NULL);
		voiceOutput("Press Ae for next round");
	
		do
		{
			input2 = keyscan();
			usleep(KEYPAD_DELAY);
		}while(!(input2 == 'A' || input2=='D'));
				
		pthread_mutex_lock(&appMutex);
		appQueFlag = 1;
		pthread_mutex_unlock(&appMutex);

		if(input2 == 'D')
		{
			return;
		}
		else if(input2 == 'A')
		{
			rndCnt++;
			continue;
		}
		else
		{
		}
				
		pthread_join(pid_lcd_new_round,NULL);

	}
	pthread_join(pid_rotor,NULL);
}	

int main()
{
	pthread_t pid_led_blink;
	char greetingFlag = 0;
	char input;

	lcd_init();	//lcd init
	init_pins();	//keypad init
	shrInit();


	while(1)
	{
		pthread_create(&pid_led_blink,NULL,&led_blink,NULL);
		if(greetingFlag == 0)
		{
//			greeting();
			greetingFlag = 1;
		}

		mode = manOrauto();
		noOfPlayers = getPlayers();

//		printf("no of players: %d %c\n",noOfPlayers,mode);

		switch(mode)
		{
			case 'A':
				getPhoneNumbers();
//				printPh();
				break;
			case 'B':
				break;
			default:
				break;
		}

		pthread_mutex_lock(&appMutex1);
		appLedBlinkFlag = 1;
		pthread_mutex_unlock(&appMutex1);
	
		game_begin();

		line_lcd(LINE1,"A: New Game");
		line_lcd(LINE2,"D: Power Off");
		do
		{
			input= keyscan();
			usleep(KEYPAD_DELAY);
		}while(!(input == 'A' || input == 'D'));
	
		if(input == 'D')
		{
			line_lcd(LINE1,"                ");
			line_lcd(LINE2,"                ");
			system("sudo poweroff");
		}

		pthread_join(pid_led_blink,NULL);
	}
}
