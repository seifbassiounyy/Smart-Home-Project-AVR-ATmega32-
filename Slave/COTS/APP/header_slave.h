////Author: Seif Bassiouny
////Date: 27/1/2023
////Version: 1.1
////Module: APP


#ifndef HEADER_SLAVE_H_
#define HEADER_SLAVE_H_

void Init();
void Start();
void Register_User();
void Light_Control();
void Door_Control();
void Admin();
void Remove_User();
void Register_User();
void Air_condition();
void close();
void open();
void List_Users();
void Login();
void getname(Uint8 *name);
void Welcome_User();
void initialize_users();
Uint8 Get_Input();
void Air_condition_User();
void Light_Control_User();


struct user
{
	Uint8 name[10];
	Uint8 password[5];
	Uint8 order;
	Uint16 address;
};

Uint8 nofusers;
struct user arrofusers[10];


#endif /* HEADER_SLAVE_H_ */