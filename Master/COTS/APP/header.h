////Author: Seif Bassiouny
////Date: 27/1/2023
////Version: 1.1
////Module: APP


#ifndef HEADER_H_
#define HEADER_H_

void Init();
void Login();
Uint8 Get_Input();
void Welcome();
void Light_Control();
void getname(Uint8 *name);
void Register_User();
void Remove_User();
void Door_Control();
void Start();
void Air_condition();
void Exit();
Uint8 Validate(Uint8 Copy_input);


struct user
{
	Uint8 name[10];
	Uint8 password[5];
	Uint8 order;
	Uint16 address;
};

Uint8 nofusers;
struct user arrofusers[10];

#endif /* HEADER_H_ */