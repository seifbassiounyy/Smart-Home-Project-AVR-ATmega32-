////Author: Seif Bassiouny
////Date: 27/1/2023
////Version: 1.1
////Module: APP

#include<string.h>
#include<stdlib.h>
#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "header_slave.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "EEPROM_Int.h"
#include "UART_Int.h"
#include "KEYPAD_Int.h"

#include<avr/io.h>
#include<avr/interrupt.h>
#define  F_CPU 1000000UL
#include  "util/delay.h"


void Init()
{
	//initialize all needed drivers
	UART_void_Init();
	DIO_void_Init();
	LCD_void_Init();
	EEPROM_void_Init();
	KEYPAD_void_Init();
	TIMER0_void_Init();
	TIMER1_void_Init();
	
	//we can reset the nofusers to zero, build then comment again so when add user and re-simulate user appears
	//EEPROM_void_Write(0x00FF, 0);
	//_delay_ms(5);
	
	nofusers=EEPROM_Uint8_Read(0x00FF);
	
	Uint8 temp = nofusers + 48;
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("nofusers: ");
	LCD_void_SetData(temp);
	_delay_ms(500);
	
	//initialize users from EEPROM to arrofusers
	initialize_users();
	
	//list users in our system to check
	List_Users();
}

void initialize_users()
{
	//initialize variables
	Uint8 read_name[10], read_password[5], j=0, i=0, order=0;
	
	//loop on nofusers
	for(i=0; i<nofusers; i++)
	{
		//reset order variable in each loop
		order=0x0000;
		
		//the beginning of the data of each user is 15 bytes distant from next user in memory, so we multiply index (i) by 15 to get first byte of name of next user in EEPROM
		order=i*15;
		
		//reset j variable which will index on the number of bytes of name as it is not constant; some users names are longer than others ex: seif, youssef.
		//However, for simplicity here maximum number of letters of name is 10 letters (bytes)
		j=0;
		
		//read name starting from order explained earlier
		read_name[j]=EEPROM_Uint8_Read(order);
		
		//increment j to assign next letter
		j++;
		
		//increment order to get next letter
		order++;
		
		//repeat until name ends with '\0'
		while(read_name[j] !='\0')
		{
			read_name[j]=EEPROM_Uint8_Read(order);
			j++;
			order++;
		}
		
		//read_name[j]='\0';
		
		//add only 9 to order to get the starting address of password (not 10 because order current value was incremented by one before leaving the while loop
		order=order+9;
		
		//read 4 bytes of password
		for(j=0; j<4; j++)
		{
			read_password[j]=EEPROM_Uint8_Read(order);
			order++;
		}
		
		//end password with '\0'
		read_password[4]='\0';
		
		//copy name and password to the arrofusers at current index
		strcpy(arrofusers[i].name, read_name);
		strcpy(arrofusers[i].password, read_password);
	}
}

void List_Users()
{
	//initialize variable
	Uint8 temp=0, i;
	
	//clear LCD
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	
	//loop on all arrofusers after initializing them from EEPROM to display them for check and debugging purpose
	for(i=0; i < nofusers; i++)
	{
		temp = i + 49;
		LCD_void_SetData(temp);
		LCD_void_SetData('-');
		LCD_void_SetString(arrofusers[i].name);
		LCD_void_SetData(' ');
		LCD_void_SetString(arrofusers[i].password);
		LCD_void_SetData(' ');
		_delay_ms(1000);
	}
	_delay_ms(2000);
}

Uint8 Get_Input()
{
	//initialize variables
	Uint8 x = '\0';
	
	//this is similar to get pressed number, however I added a while loop to be stuck in until user presses the keypad to continue used later
	while(x=='\0')
	{
		x = KEYPAD_Uint8_GetPressedNumber();
	}
	return x;
}

void Start()
{
	//initialize variables
	Uint8 received='\0', choice='\0', x=0;
	
	//ask user to enter '0' to start a session
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("To start please enter '0'");
	
	//system is stuck in this while loop until either receives a signal 'A' from admin's phone to start a session or user enters '0' to start session 
	//whoever starts a session first will lock the screen on the other until he finishes, and then the smart home will be available again
	while(received=='\0' && choice=='\0')
	{
		choice = KEYPAD_Uint8_GetPressedNumber();
		received = UART_Uint8_Receive2();
	}
		
	//if received is 'A' then admin wishes to start a session on smart home; so we lock it on users until admin finishes changes
	if(received=='A')
	{
		x=1;
		
		//inform users that system is currently in use
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("System currently in use,");
		LCD_void_SetCursor(1,0);
		LCD_void_SetString("please wait!");
		
		//call admin function to allow admin to control smart home
		Admin();
		
		//return from session and unlock smart home for use again
		return;
	}
	
	//if '0' is pressed, then a user will control the system, and admin will have to wait
	else if(choice=='0')
	{
		//send 'U' to admin to inform that system is currently in use by a user
		UART_void_Transmit('U');
		
		//call Login function, for user to control home
		Login();
		
		//transmit 'F' to inform admin that session ended and smart home is available again for use
		UART_void_Transmit('F');
	}
}

void Register_User()
{
	//initialize variables
	Uint8 received='\0', order, new_password[5], x[5], new_name[10], i=0, j=0, flag=0, flag2=0, temp;
	Uint16 address=0x0000;
	struct user new;
	
	//receive name of new user until master sends '+' meaning the name has ended as we don't know the length of the name
	while(received != '+')
	{
		received = UART_Uint8_Receive();
		new_name[i]=received;
		i++;
	}
	
	//end last character of name with '\0' to mark the end of name
	new_name[i-1]='\0';
	
	//display name for confirmation and debugging
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString(new_name);
	_delay_ms(2000);
	
	//loop on all users to check if the new name matches a previously registered name
	for(j=0; j<nofusers; j++)
	{
		//if they match set flag2=1, and print duplicate
		if(strcmp(arrofusers[j].name, new_name)==0)
		{
			flag2 = 1;
			LCD_void_ClearScreen();
			LCD_void_SetCursor(0,0);
			LCD_void_SetString("duplicate");
		}
		//else print unique
		else
		{
			LCD_void_ClearScreen();
			LCD_void_SetCursor(0,0);
			LCD_void_SetString("unique");
		}
	}
	
	//while loop until user enters a unique name
	while(flag2==1)
	{
		//reset variables
		received='\0';
		flag2=0;
		i=0;
		
		//transmit '0' to master to infrom that this name is a duplicate and ask him to enter another name
		UART_void_Transmit('0');
		_delay_ms(5);
		
		//receive name of new user until master sends '+' meaning the name has ended as we don't know the length of the name
		while(received != '+')
		{
			received = UART_Uint8_Receive();
			new_name[i]=received;
			i++;
		}
		
		//end last character with '\0'
		new_name[i-1]='\0';
		
		//display name for confirmation and debugging
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString(new_name);
		
		//loop on all users to check if the new name matches a previously registered name
		for(j=0; j<nofusers; j++)
		{
			//if they match set flag2=1, and print duplicate, and repeat while loop
			if(strcmp(arrofusers[j].name, new_name)==0)
			{
				flag2 = 1;
				LCD_void_ClearScreen();
				LCD_void_SetCursor(0,0);
				LCD_void_SetString("duplicate");
			}
		}
	}
	
	UART_void_Transmit('1');
	_delay_ms(5);
	
	
	
	//resetting variables for password
	received='x';
	i=0;
	
	//receive password of new user
	while(received != '+')
	{
		received = UART_Uint8_Receive();
		new_password[i]=received;
		i++;
	}
	
	new_password[i-1]='\0';
	
	//assign the received name and password to new user struct
	
	strcpy(new.password, new_password);
	strcpy(new.name, new_name);
	
	//add the new user to the array of users and increment its count by one
	arrofusers[nofusers] = new;
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("received: ");
	LCD_void_SetString(arrofusers[nofusers].name);
	LCD_void_SetCursor(1,0);
	LCD_void_SetString(arrofusers[nofusers].password);
	
	
	//write the new user's data to memory according to their order: first 10 bytes hold name, and next 5 bytes hold password
	//so in total each user holds 15 bytes in memory and we get starting address of user by multiplying the order by 15
	order=nofusers*15;
	
	EEPROM_void_Write_Successive(order, arrofusers[nofusers].name);
	EEPROM_void_Write_Successive((order+10), arrofusers[nofusers].password);
	
	//used for debugging
	/*Uint8 read_name[5], m;
	
	m=order;
	for(j=0; j<4; j++)
	{
		read_name[j]=EEPROM_Uint8_Read(m);
		m++;
	}
	
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString(read_name);
	_delay_ms(1000);
	
	Uint8 t = nofusers+48;
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("before: ");
	LCD_void_SetData(t);
	_delay_ms(1000);*/
	
	//increment nofusers and write it to EEPROM at a unique address 0x00FF
	nofusers+=1;
	EEPROM_void_Write(0x00FF, nofusers);
	
	//used for debugging
	/*
	t = nofusers+48;
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("after: ");
	LCD_void_SetData(t);
	_delay_ms(1000);*/
}

void Remove_User()
{
	//initialize variables
	Uint8 received='\0', temp, y, deleted_name[10], i=0, j=0, flag=0, k=0, x[5],d[10];
	Uint16 address=0x0000;
		
	//receive name of new user until master sends '+' meaning the name has ended as we don't know the length of the name
	while(received != '+')
	{
		received = UART_Uint8_Receive();
		deleted_name[i]=received;
		i++;
	}
	
	//end last character with '\0'
	deleted_name[i-1]='\0';
	
	//display name for confirmation
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("name to be deleted: ");
	LCD_void_SetString(deleted_name);

	//loop on arrofusers		
	for(i=0; i<nofusers; i++)
	{
		//if name is found
		if(strcmp(arrofusers[i].name, deleted_name)==0)
		{
			//set flag=1
			flag = 1;
			
			//loop on all users following this user and shift them backward by one to delete current user and maintain compaction of arrofusers
			for(j=i; j<nofusers-1; j++)
			{
				arrofusers[j] = arrofusers[j+1];
				
				//get starting address of user same as discussed before
				temp = j*15;
				
				//write the name and address to new location (same location as the user before the current user)
				EEPROM_void_Write_Successive(temp, arrofusers[j+1].name);
				EEPROM_void_Write_Successive((temp+10), arrofusers[j+1].password);
			}
			
			//transmit 'v' to master to inform that name is deleted successfully
			UART_void_Transmit('v');
			_delay_ms(5);
			
			//inform that name is deleted for debugging
			LCD_void_ClearScreen();
			LCD_void_SetCursor(0,0);
			LCD_void_SetString("User ");
			LCD_void_SetString(deleted_name);
			LCD_void_SetString(" deleted successfully!");
			
			//decrement nofusers
			nofusers--;
			
			//write decremented nofusers to memory
			EEPROM_void_Write(0x00FF, nofusers);
		}
	}
	
	//if name was not found (flag=0)
	if(flag==0)
	{
		//send 'c' and inform master that name was not founs
		UART_void_Transmit('c');
		_delay_ms(5);
		
		//display that user was not found for debugging 
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("User ");
		LCD_void_SetString(deleted_name);
		LCD_void_SetString(" was not found!");
		
	}
	
	//display current nofusers for debugging
	y = nofusers + 48;
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Number of users: ");
	LCD_void_SetData(y);
}

void Light_Control()
{
	//initialize variables
	Uint8 choice='\0', percentage='\0', onoff='\0';
	
	//receive choice from master
	choice = UART_Uint8_Receive();
	
	//if choice is 6, then admin wants to control dimmer
	if(choice==6)
	{
		//receive percentage
		percentage = UART_Uint8_Receive();
		
		//assign value to timer0 to generate desired PWM signal
		TIMER0_void_SetTimer0CompareMatchReg(percentage);
	}
	
	//if choice is 5 (because it is put on separate pin)
	else if(choice==5)
	{
		//receive whether turn on or off
		onoff = UART_Uint8_Receive();
		
		//set light as desired for lamp 5
		if(onoff=='1')
			DIO_void_SetPinValue(DIO_Uint8_PIN8, DIO_Uint8_HIGH);
		else if(onoff=='0')
			DIO_void_SetPinValue(DIO_Uint8_PIN8, DIO_Uint8_HIGH);
	}
	
	//if choice is other than 5 and 6
	else
	{
		//receive whether turn on or off
		onoff = UART_Uint8_Receive();
		
		//set light as desired for lamp
		if(onoff=='1')
			DIO_void_SetPinValue(choice-1, DIO_Uint8_HIGH);
		else if(onoff=='0')
			DIO_void_SetPinValue(choice-1, DIO_Uint8_LOW);
	}
}

void Door_Control()
{
	//initialize variable
	Uint8 received='\0';
	
	//ask admin whether to open or close the door
	received = UART_Uint8_Receive();
	
	//close door -90 deg-> 125pwm
	if(received=='0')
		TIMER1_void_SetTimer1CompareMatchReg(125);	
	
	//open door 90 deg-> 250pwm
	else if(received=='1')
		TIMER1_void_SetTimer1CompareMatchReg(250);
}

void Air_condition()
{
	//initialize variable
	Uint8 received='\0';
	
	//ask admin whether to turn on or off the AC
	received = UART_Uint8_Receive();
	
	//turn on
	if(received=='1')
	{
		//rotates motor in clockwise 00000010
		DIO_void_SetPinValue(DIO_Uint8_PIN13, DIO_Uint8_HIGH);
		DIO_void_SetPinValue(DIO_Uint8_PIN14, DIO_Uint8_LOW); 
	}
	
	//turn off
	else if(received=='0')
	{
		//stops the motor
		DIO_void_SetPinValue(DIO_Uint8_PIN14, DIO_Uint8_HIGH);
		DIO_void_SetPinValue(DIO_Uint8_PIN13, DIO_Uint8_HIGH);	
	}
}


void Admin()
{
	//initialize variables
	Uint8 received='\0', new[5], i=0, flag=0, x[5];
	Uint16 address=0x0000;	
	
	while(1)
	{
		//receive desired modification from master
		received = UART_Uint8_Receive();
		
		switch(received)
		{
			//lights control
			case '1':
				Light_Control();
				break;
			
			//door control
			case '2':
				Door_Control();
				break;
			//air condition control
			case '3':
				Air_condition();
				break;
			
			//register new user to EEPROM
			case '4':
				Register_User();
				break;
			
			//remove old user from EEPROM
			case '5':
				Remove_User();
				break;
			
			//exit
			case '6':
				return;
			
			//exit
			case 'X':
				return;
			
			//default is to break
			default:
				break;
			
		}
	}

}

void getname(Uint8 *test1)
{
	//initialize variables
	Uint8 temp='\0', page='1', i=0;
	
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Enter '0' to start");
	
	//while user does not press '#' continue taking name or letter limit exceeds 10
	while(temp != '#' && i<10)
	{
		//get input from user
		temp = Get_Input();
		
		//if input is = 0 then user wants to change page to press a letter in another page
		if(temp=='0')
		{
			//ask user to choose a page
			LCD_void_ClearScreen();
			LCD_void_SetCursor(1,0);
			LCD_void_SetString(test1);
			LCD_void_SetCursor(0,0);
			LCD_void_SetString("choose page(1~3)");
			
			//get page number form user
			temp = Get_Input();
			
			//display page 1 containing "A-B-C-D-E-F-G-H-I" from (1-9)
			if(temp=='1')
			{
				LCD_void_ClearScreen();
				LCD_void_SetCursor(1,0);
				LCD_void_SetString(test1);
				LCD_void_SetCursor(0,0);
				LCD_void_SetString("A-B-C-D-E-F-G-H-I");
				page='1';
			}
			
			//display page 2 containing "J-K-L-M-N-O-P-Q-R" from (1-9)
			else if(temp=='2')
			{
				LCD_void_ClearScreen();
				LCD_void_SetCursor(1,0);
				LCD_void_SetString(test1);
				LCD_void_SetCursor(0,0);
				LCD_void_SetString("J-K-L-M-N-O-P-Q-R");
				page='2';
			}
			
			//display page 3 containing "S-T-U-V-W-X-Y-Z" from (1-8)
			else if(temp=='3')
			{
				LCD_void_ClearScreen();
				LCD_void_SetCursor(1,0);
				LCD_void_SetString(test1);
				LCD_void_SetCursor(0,0);
				LCD_void_SetString("S-T-U-V-W-X-Y-Z");
				page='3';
			}
		}
		
		//remap each button to certain letter according to chosen page 
		else
		{
			if(page=='1')
			{
				if(temp=='1')
					test1[i]='A';
				else if(temp=='2')
					test1[i]='B';
				else if(temp=='3')
					test1[i]='C';
				else if(temp=='4')
					test1[i]='D';
				else if(temp=='5')
					test1[i]='E';
				else if(temp=='6')
					test1[i]='F';
				else if(temp=='7')
					test1[i]='G';
				else if(temp=='8')
					test1[i]='H';
				else if(temp=='9')
					test1[i]='I';
					
				//increment counter of name
				i++;
			}
			
			else if(page=='2')
			{
				if(temp=='1')
					test1[i]='J';
				else if(temp=='2')
					test1[i]='K';
				else if(temp=='3')
					test1[i]='L';
				else if(temp=='4')
					test1[i]='M';
				else if(temp=='5')
					test1[i]='N';
				else if(temp=='6')
					test1[i]='O';
				else if(temp=='7')
					test1[i]='P';
				else if(temp=='8')
					test1[i]='Q';
				else if(temp=='9')
					test1[i]='R';
					
				//increment counter of name
				i++;
			}
			
			else if(page=='3')
			{
				if(temp=='1')
					test1[i]='S';
				else if(temp=='2')
					test1[i]='T';
				else if(temp=='3')
					test1[i]='U';
				else if(temp=='4')
					test1[i]='V';
				else if(temp=='5')
					test1[i]='W';
				else if(temp=='6')
					test1[i]='X';
				else if(temp=='7')
					test1[i]='Y';
				else if(temp=='8')
					test1[i]='Z';
				
				//increment counter of name
				i++;
			}
		}
		
		//display entered name so far
		LCD_void_SetCursor(1,0);
		LCD_void_SetString(test1);
		_delay_ms(350);
	}
}

void Login()
{
	//initialize variables
	Uint8 ctr=0, flag=0, flag2=0, x='\0', temp, y, password[5], name[10]={'\0'}, i=0, t[5];
	Uint16 address;
	
	//welcome admin
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Welcome User!");
	_delay_ms(300);
	
	//inform user how to enter name
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Please enter name, then #");
	LCD_void_SetCursor(1,0);
	LCD_void_SetString("to change page enter '0'");
	_delay_ms(2000);

	//get name from user 
	getname(name);
	
	//display name for confirmation
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Entered name: ");
	LCD_void_SetString(name);
	_delay_ms(1000);
	
	//loop on arrofusers
	for(i=0; i<nofusers; i++)
	{
		//if name is found
		if(strcmp(arrofusers[i].name, name)==0)
		{
			//set flag=1
			flag = 1;
			
			//inform name was found for debugging
			LCD_void_ClearScreen();
			LCD_void_SetCursor(0,0);
			LCD_void_SetString("Username found.");
			_delay_ms(500);
			
			//ask user to enter password, if user enters name incorrectly 3 times, buzzer rings
			while(ctr<3)
			{
				//ask user to enter password
				LCD_void_ClearScreen();
				LCD_void_SetCursor(0,0);
				LCD_void_SetString("Please enter password of 4 digits.");

				//print entered password for user and assign it to password array
				LCD_void_SetCursor(1,0);
				for(int j=0; j<4; j++)
				{
					password[j] = Get_Input();
					LCD_void_SetData(password[j]);
					_delay_ms(250);
				}
				
				//display password to user for confirmation
				LCD_void_ClearScreen();
				LCD_void_SetCursor(0,0);
				LCD_void_SetString("Entered password: ");
				LCD_void_SetString(password);
				LCD_void_ClearScreen();
				_delay_ms(1000);
				
				//end password array with '\0'
				password[4]='\0';
				
				//compare stored and entered passwords
				for(int j=0; j<4; j++)
				{	
					//if any digit is incorrect				
					if (arrofusers[i].password[j] != password[j])
					{
						//set flag2=1
						flag2=1;
					}
				}
				
				//if flag2=0; password entered correctly
				if(flag2==0)
				{
					//welcome the user
					LCD_void_ClearScreen();
					LCD_void_SetCursor(0,0);
					LCD_void_SetString("Welcome ");
					LCD_void_SetString(name);
					_delay_ms(500);
					
					//call Welcome_User function
					Welcome_User();
					
					//return from session
					return;
				}
				
				//if flag2=1; password entered incorrectly
				else if(flag2==1)
				{
					//increment ctr to keep track of number of times password was entered incorrectly
					ctr++;
					
					//inform user that password is incorrect
					LCD_void_ClearScreen();
					LCD_void_SetCursor(0,0);
					LCD_void_SetString("Incorrect password!");
					_delay_ms(500);
					
					//if ctr=3, turn on buzzer
					if(ctr==3)
						DIO_void_SetPinValue(DIO_Uint8_PIN15, DIO_Uint8_HIGH);	
				}
			}
			
			//return from session
			return;
		}
	}
	
	//if flag=0
	if(flag==0)
	{
		//inform user that name was not found
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("User ");
		LCD_void_SetString(name);
		LCD_void_SetString(" was not found!");
		_delay_ms(1000);
		
		//return from session
		return;	
	}

	//return from session
	return;
}

void Light_Control_User()
{
	//initialize variables
	Uint8 choice='\0', percentage[4]={'\0'}, onoff='\0', i=0, final;
	
	//ask user to choose room (1-6)
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Choose room (1-6)");
	
	//receive choice from master
	choice = Get_Input();
	
	//if choice is 6, then admin wants to control dimmer
	if(choice=='6')
	{
		//ask user to enter percentage of lighting of dimmer
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("Please enter lighting percentage");
		LCD_void_SetCursor(1,0);
		LCD_void_SetString("of dimmer(0~100)");
		
		//get percentage of dimmer from admin
		for(i=0; i<3; i++)
		{
			percentage[i] = Get_Input();
			//delay to avoid multiple input when clicked for a long press
			_delay_ms(300);
		}
		
		//display percentage for confirmation
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString(percentage);
		_delay_ms(1000);
		
		//convert percentage string to integer value
		final=atoi(percentage);
		
		//if value > 100, assume max percentage
		if(final>=100)
		{
			TIMER0_void_SetTimer0CompareMatchReg(250);
			_delay_ms(10);
		}
		
		else
		{
			//map percentage to value from 0-255
			final = (0 + ((255-0) / (100-0)) * (final-0));
			//assign value to timer0 to generate desired PWM signal
			TIMER0_void_SetTimer0CompareMatchReg(final);
		}
	}
	
	//if choice is 5 (because it is put on separate pin)
	else if(choice=='5')
	{
		//ask user to turn on or off
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("Turn on or off?(1/0");
		
		//receive whether turn on or off
		onoff = Get_Input();
		
		//set light as desired for lamp 5
		if(onoff=='1')
			DIO_void_SetPinValue(DIO_Uint8_PIN8, DIO_Uint8_HIGH);
		else if(onoff=='0')
			DIO_void_SetPinValue(DIO_Uint8_PIN8, DIO_Uint8_HIGH);
	}
	
	//if choice is other than 5 and 6
	else
	{
		//ask user to turn on or off
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("Turn on or off?(1/0");
		
		//receive whether turn on or off
		onoff = Get_Input();
		
		//set light as desired for lamp
		if(onoff=='1')
			DIO_void_SetPinValue(choice-49, DIO_Uint8_HIGH);
		else if(onoff=='0')
			DIO_void_SetPinValue(choice-49, DIO_Uint8_LOW);
	}
}

void Air_condition_User()
{
	//initialize variable
	Uint8 received='\0';
	
	//ask user to turn on or off the AC
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Turn on or off the AC? (1/0)");
	
	//get input from user
	received = Get_Input();
	
	//turn on
	if(received=='1')
	{
		//rotates motor in clockwise 00000010
		DIO_void_SetPinValue(DIO_Uint8_PIN13, DIO_Uint8_HIGH);
		DIO_void_SetPinValue(DIO_Uint8_PIN14, DIO_Uint8_LOW);
	}
	
	//turn off
	else if(received=='0')
	{
		//stops the motor
		DIO_void_SetPinValue(DIO_Uint8_PIN14, DIO_Uint8_HIGH);
		DIO_void_SetPinValue(DIO_Uint8_PIN13, DIO_Uint8_HIGH);
	}
}

void Welcome_User()
{
	//initialize variables
	Uint8 choice='\0', redo=1;
	
	//while redo=1; user wants to do more changes
	while(redo)
	{
		//display control options for admin
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("1-Light 2-Air Condition 3-Exit");
		
		//get input from admin
		choice = Get_Input();
		
		//switch on admin input
		switch(choice)
		{
			//control lights
			case '1':
				Light_Control_User();
				break;
			
			//control door
			case '2':
				Air_condition_User();
				break;
			
			//exit
			case '3':
				UART_void_Transmit('X');
				return;
			
			//default is to break from switch
			default:
				break;
		}
		
		//ask user if they wish to do other changes
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("Do you want to");
		LCD_void_SetCursor(1,0);
		LCD_void_SetString("do other changes? (1/0) ");
		
		choice='\0';
		
		while(choice=='\0')
		{
			choice = KEYPAD_Uint8_GetPressedNumber();
		}
		
		//redo the while
		if(choice=='1')
			redo=1;
		
		//exit
		else if(choice=='0')
			redo=0;
	}
	
	//return from session
	return;
}