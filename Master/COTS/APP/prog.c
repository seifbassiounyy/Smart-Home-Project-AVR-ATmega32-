////Author: Seif Bassiouny
////Date: 27/1/2023
////Version: 1.1
////Module: APP

#include<string.h>
#include<stdlib.h>
#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "header.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "EEPROM_Int.h"
#include "UART_Int.h"
#include "KEYPAD_Int.h"
#include <avr/io.h>
#define  F_CPU 1000000UL
#include  "util/delay.h"



void Init()
{
	//initialize used drivers
	UART_void_Init();
	DIO_void_Init();
	LCD_void_Init();
	KEYPAD_void_Init();
	EEPROM_void_Init();
	
	//write 0 to nofusers in EEPROM to reset if wanted
	//EEPROM_void_Write(0x0010, 0);
	//_delay_ms(5);	
	
	//read nofusers fro EEPROM from unique address 0x0010
	nofusers=EEPROM_Uint8_Read(0x0010);
	Uint8 temp = nofusers + 48;
	
}

void Start()
{
	//initialize used variables
	Uint8 received='\0', choice='\0', x;
	
	//ask admin to enter '0' to start a session
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
	
	//if received is 'U' then user wishes to start a session on smart home; so we lock it on admin until user finishes changes
	if(received=='U')
	{
		x=1;
		
		//inform admin that system is currently in use
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("System currently in use,");
		LCD_void_SetCursor(1,0);
		LCD_void_SetString("please wait!");
		
		//reset received
		received='\0';
		
		//wait until user finishes session
		received = UART_Uint8_Receive();
		
		//if received = 'F' then session has finished
		if(received=='F')
			//return and ask to start session again
			return;	
	}
	
	//if admin starts a session
	else if(choice=='0')
	{
		//transmit 'A' to slave to inform that admin started a session to control home, and disable control from users
		UART_void_Transmit('A');
		
		//call function Login for admin to login
		Login();
		
		//transmit 'X' after admin finishes to inform slave that admin's session has ended
		UART_void_Transmit('X');
		
		//return from session
		return;
	}
}

Uint8 Validate(Uint8 x)
{
	//validation of input to be either '1' or '2' only
	while(x!='1' && x!='2')
	{
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("Please choose");
		LCD_void_SetCursor(1,0);
		LCD_void_SetString("either 1 or 2!");
		x='\0';
		while(x=='\0')
		{
			x = KEYPAD_Uint8_GetPressedNumber();
		}
	}
	return x;
}

Uint8 Get_Input()
{
	//initialize used variables
	Uint8 x = '\0';
	
	//this is similar to get pressed number, however I added a while loop to be stuck in until user presses the keypad to continue used later
	while(x=='\0')
	{
		x = KEYPAD_Uint8_GetPressedNumber();
	}
	return x;
}

void Login()
{
	//initialize used variables
	Uint8 ctr=0, flag=0, x='\0', y, pass[5]={'\0'}, t[5];
	Uint16 address;
	
	//initialize drivers
	KEYPAD_void_Init();
	DIO_void_Init();
	LCD_void_Init();
	
	//welcome admin
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Welcome Admin!");
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("To login press 1, to");
	LCD_void_SetCursor(1,0);
	LCD_void_SetString("change password press 2.");
	
	//Get input from keypad
	x = Get_Input();
	
	//validate input to be either 1 or 2 only
	x = Validate(x);
	
	//login
	if (x == '1')
	{
		while(ctr<4)
		{
			Uint8 pass1[5]={'\0'};
			
			//entered password 3 times incorrectly
			if(ctr==3)
			{
				//Turn on buzzer
				DIO_void_SetPinValue(DIO_Uint8_PIN1, DIO_Uint8_HIGH);
				_delay_ms(2000);
				DIO_void_SetPinValue(DIO_Uint8_PIN1, DIO_Uint8_LOW);
				
				return;
			}
			
			LCD_void_ClearScreen();
			LCD_void_SetCursor(0,0);
			LCD_void_SetString("Please enter password");
						
			//Here we should read password from keypad
			LCD_void_SetCursor(1,0);
			for(int i=0; i<4; i++)
			{
				pass1[i] = Get_Input();
				LCD_void_SetData(pass1[i]);
				_delay_ms(250);
			}
			
			//check password
			address=0x0000;
			flag = 0;
			
			//loop on each character in password and compare it to password stored in EEPROM, if there
			//is a difference increment ctr and ask user to re-enter password as it is incorrect 
			for(int i=0; i<4; i++)
			{
				y = EEPROM_Uint8_Read(address);
				address++;
				
				if (pass1[i]!=y)
				{
					ctr++;
					flag = 1;
					LCD_void_ClearScreen();
					LCD_void_SetCursor(0,0);
					LCD_void_SetString("Wrong Password!");
					break;
				}
			}
			
			//if flag = 0, then password is correct
			if (flag==0)
			{
				Welcome();
				return;
			}
		}
	}
	
	//register new password
	else if(x == '2')
	{
		//ask user to enter password
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("Enter password");
		LCD_void_SetCursor(1,0);
		LCD_void_SetString("of 4 digits.");
		_delay_ms(30);
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		
		//get password from keypad
		for(int i=0; i<4; i++)
		{
			pass[i] = Get_Input();
			LCD_void_SetData(pass[i]);
			_delay_ms(250);
		}
		pass[4]='\0';
		
		
		//write password on EEPROM
		EEPROM_void_Write_Successive(0x0000, pass);
		
		//set address to 0x0000
		address=0x0000;
		for(int i=0; i<4; i++)
		{
			t[i] = EEPROM_Uint8_Read(address);
			address++;
			_delay_ms(5);
		}
		
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString(t);
		_delay_ms(2000);
		
		//inform admin of adding the new password successfully
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("New Password");
		LCD_void_SetCursor(1,0);
		LCD_void_SetString("registered successfully!");
	}
	
	return;
}

void Light_Control()
{
	Uint8 choice='\0', percentage[4]={'\0'}, i=0, final;
			
	//transmit '1' to inform slave that admin will control light system
	UART_void_Transmit('1');
	
	//ask admin which room to control light in
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Please choose room from (1~6)");
	
	//Get input from keypad
	choice = Get_Input();
	
	//if choice is '6', then user has chosen dimmer light
	if(choice == '6')
	{
		//get integer value of '6'
		choice = choice - '0';
		
		//transmit 6 to inform slave that admin will control light number 6
		UART_void_Transmit(choice);
		
		//ask user to enter percentage of lighting of dimmer
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("Please enter lighting percentage");
		LCD_void_SetCursor(1,0);
		LCD_void_SetString("of dimmer(0~100)");
		_delay_ms(500);
		
		
		//get percentage of dimmer from admin
		for(i=0; i<3;i++)
		{
			//assign value to percentage array
			percentage[i] = Get_Input();
			
			//delay to avoid multiple input when clicked for a long press
			_delay_ms(250);
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
			UART_void_Transmit(250);
			_delay_ms(10);
		}
		else
		{
			//map percentage to value from 0-255
			final = (0 + ((255-0) / (100-0)) * (final-0));
			UART_void_Transmit(final);
			_delay_ms(10);
		}
	}
	
	//else, admin has chosen normal light (on/off)
	else
	{
		//get integer value of light number
		choice = choice - '0';
		
		//transmit to slave the number of light
		UART_void_Transmit(choice);
		_delay_ms(10);
		
		//ask admin turn on or off the light
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("Turn on or off?(1/0)");
		_delay_ms(10);
		
		//get answer from admin
		choice = Get_Input();
		
		//transmit answer to slave(1/0)
		UART_void_Transmit(choice);
		_delay_ms(10);
	}	
	
}

void Door_Control()
{
	Uint8 choice='\0';
	
	//transmit '1' to inform slave that admin will control light system
	UART_void_Transmit('2');
	
	//ask user open or close door
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Open or close door?(1/0)");
	
	//Get input from keypad
	choice = Get_Input();
	
	//validate choice
	while(choice!='0' && choice!='1')
	{
		choice = Get_Input();
	}
	
	//transmit admin's choice
	UART_void_Transmit(choice);
}

void Air_condition()
{
	Uint8 choice='\0';
	
	//inform slave that admin will control AC
	UART_void_Transmit('3');
	
	//ask admin turn on or off the AC
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Turn on or off the AC?(1/0)");
	
	//Get input from keypad
	choice = Get_Input();
	
	//validate input
	while(choice!='0' && choice!='1')
	{
		choice = Get_Input();
	}
	
	//transmit admin's choice
	UART_void_Transmit(choice);
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

void Register_User()
{
	Uint8 test1[10]={'\0'};
	Uint8 test2[5];
	struct user new;
		
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Enter name then press #,");
	LCD_void_SetCursor(1,0);
	LCD_void_SetString("to change page press '0'");
	_delay_ms(1500);
	
	
	getname(test1);
	
	UART_void_Transmit('4');
	_delay_ms(100);
	
	for(int i=0; i<strlen(test1); i++)
	{
		UART_void_Transmit(test1[i]);
		_delay_ms(5);
	}
	
	UART_void_Transmit('+');
	_delay_ms(5);
	
	Uint8 c = UART_Uint8_Receive();
	
	while(c=='0')
	{
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("This username already exists!");
		_delay_ms(1000);
		
		//reset test1
		for(int k=0; k<10;k++)
			test1[k]='\0';
			
		getname(test1);
		
		for(int i=0; i<strlen(test1); i++)
		{
			UART_void_Transmit(test1[i]);
			_delay_ms(5);
		}
		
		UART_void_Transmit('+');
		_delay_ms(5);
		c = UART_Uint8_Receive();
	}
	
		
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Enter password of new user:");
	
	//Here we should read password from keypad
	LCD_void_SetCursor(1,0);
	for(int i=0; i<4; i++)
	{
		test2[i] = Get_Input();
		LCD_void_SetData(test2[i]);
		_delay_ms(250);
	}
		
	strcpy(new.password, test2);
	strcpy(new.name, test1);
	new.order = nofusers;
	new.address = nofusers*15;
	arrofusers[nofusers] = new;
	
	
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Entered name: ");
	LCD_void_SetString(arrofusers[nofusers].name);
	
	for(int i=0; i<4; i++)
	{
		UART_void_Transmit(new.password[i]);
		_delay_ms(5);
	}
	UART_void_Transmit('+');
	_delay_ms(5);
	
	
	nofusers++;
	EEPROM_void_Write(0x0010, nofusers);
	_delay_ms(500);
	
	return;
}

void Remove_User()
{
	Uint8 flag=0, z, name[10]={'\0'};
		
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Enter name then press #,");
	LCD_void_SetCursor(1,0);
	LCD_void_SetString("to change page press '0'");
	_delay_ms(1500);
	
	if(nofusers==0)
	{
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("No users exist! ");
		return;
	}
	
	UART_void_Transmit('5');
	_delay_ms(100);
	
	getname(name);
		
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Entered name: ");	
	LCD_void_SetString(name);
	
	_delay_ms(500);
	
	
	for(int i=0; i<strlen(name); i++)
	{
		UART_void_Transmit(name[i]);
		_delay_ms(5);
	}
	
	UART_void_Transmit('+');
	_delay_ms(5);
	
	z = UART_Uint8_Receive();
	
	if(z=='v')
	{
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("User ");
		LCD_void_SetString(name);
		LCD_void_SetString(" deleted successfully!");
		nofusers--;
		EEPROM_void_Write(0x0010, nofusers);
		_delay_ms(100);
	}
	
	else
	{
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("User was not found! ");
	}
}

void Welcome()
{
	UART_void_Init();
	
	Uint8 choice='\0', redo=1;
	
	//start session for admin
	UART_void_Transmit('A');
	_delay_ms(100);
	
	//welcome admin
	LCD_void_ClearScreen();
	LCD_void_SetCursor(0,0);
	LCD_void_SetString("Welcome!");
	_delay_ms(10);

	
	while(redo)
	{
		//display control options for admin
		LCD_void_ClearScreen();
		LCD_void_SetCursor(0,0);
		LCD_void_SetString("1-Light 2-Door 3-Air Condition");
		LCD_void_SetCursor(1,0);
		LCD_void_SetString("4-Add 5-Remove	6-Exit");
		
		//get input from admin
		choice = Get_Input();
		
		//switch on admin input
		switch(choice)
		{
			case '1':
				//control lights
				Light_Control();
				break;
			
			case '2':
				//control door
				Door_Control();
				break;
			
			case '3':
				//control air conditioner
				Air_condition();
				break;
			
			case '4':
				//register a new user
				Register_User();
				break;
			
			case '5':
				//register new password to EEPROM
				Remove_User();
				break;	
			
			case '6':
				//exit
				UART_void_Transmit('X');
				return;
				
			default:
				break;
		}
		
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
		
		if(choice=='1')
			redo=1;
		else if(choice=='0')
			redo=0;
	}
	UART_void_Transmit('X');
}


