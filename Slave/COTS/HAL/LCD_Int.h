////Author: Seif Bassiouny
////Date: 8/9/2022
////Version: 1.2
////Module: LCD

#ifndef LCD_INT_H_
#define LCD_INT_H_

#define LCD_Uint8_ROW_0	0
#define LCD_Uint8_ROW_1	1
#define LCD_Uint8_COL_0 0
#define LCD_Uint8_COL_1 1
#define LCD_Uint8_COL_2 2
#define LCD_Uint8_COL_3 3
#define LCD_Uint8_COL_4 4
#define LCD_Uint8_COL_5 5
#define LCD_Uint8_COL_6 6
#define LCD_Uint8_COL_7 7
#define LCD_Uint8_COL_8 8
#define LCD_Uint8_COL_9 9
#define LCD_Uint8_COL_10 10
#define LCD_Uint8_COL_11 11
#define LCD_Uint8_COL_12 12
#define LCD_Uint8_COL_13 13
#define LCD_Uint8_COL_14 14
#define LCD_Uint8_COL_15 15

//Initialization
void LCD_void_Init(void);
//Setters
void LCD_void_SetData(Uint8 Copy_data);
void LCD_void_SetCommand(Uint8 Copy_command);
void LCD_void_SetString(Sint8* P_string);
void LCD_void_SetCursor(Uint8 Copy_row, Uint8 Copy_column);
void LCD_void_ClearScreen(void);

#endif // LCD_INT_H_