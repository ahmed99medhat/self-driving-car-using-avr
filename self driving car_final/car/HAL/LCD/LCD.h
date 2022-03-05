/*
 * LCD.h
 *
 * Created: 2/15/2022 5:50:38 PM
 *  Author: User
 */

#ifndef LCD_H_
#define LCD_H_

#include "LCD_Configuration.h"

void LCD_Initialization(void);
void LCD_Clear(void);
void LCD_Write_Command(uint8_t command);
void LCD_Write_Character(uint8_t character);
void LCD_Write_String(uint8_t* str);
#endif /* LCD_H_ */