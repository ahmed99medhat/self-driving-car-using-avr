/*
* LCD.c
*
* Created: 2/15/2022 5:51:50 PM
*  Author: User
*/

#include "LCD.h"
#include <stdio.h>
#include <math.h>


void LCD_Initialization(void)
{
	/*Define direction for control pins*/
	DIO_SetPinDirection(LCD_CTRL_PORT, LCD_RS, LCD_OUT);
	DIO_SetPinDirection(LCD_CTRL_PORT, LCD_RW, LCD_OUT);
	DIO_SetPinDirection(LCD_CTRL_PORT, LCD_EN, LCD_OUT);
	/*Define direction for data pins*/
	DIO_SetPinDirection(LCD_DATA_PORT, LCD_D4, LCD_OUT);
	DIO_SetPinDirection(LCD_DATA_PORT, LCD_D5, LCD_OUT);
	DIO_SetPinDirection(LCD_DATA_PORT, LCD_D6, LCD_OUT);
	DIO_SetPinDirection(LCD_DATA_PORT, LCD_D7, LCD_OUT);
	/*Define commands needed to choose 4Bit mode*/
	LCD_Write_Command(BITSequence1);/*Define working in 4BIT mode*/
	LCD_Write_Command(BITSequence2);/*Define working in 4BIT mode*/
	LCD_Write_Command(BITSequence3);/*Use 4BIT mode*/
	LCD_Write_Command(ReturnHome);/*Return home*/
	LCD_Write_Command(DisplayON);/*Display ON, Cursor OFF*/
	LCD_Write_Command(ClearScreen);/*Clear screen*/
	LCD_Write_Command(IncrementRight);/*Increment cursor right*/

}

void LCD_Clear(void)
{
	LCD_Write_Command(ClearScreen);
}

void LCD_Write_Command(uint8_t command)
{
	/*Register Select pin will select control register*/
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_RS, LCD_LOW);
	/*Read/Write pin will be write on LCD*/
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_RW, LCD_LOW);
	/*Be sure that enable is disabled*/
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_EN, LCD_LOW);
	/*Send high nipple of the command, without changing old PORTA pins(0-3)*/
	PORTA = (command & 0xF0) | (PORTA & 0x0F);
	/*Send High pulse for 1 millisecond*/
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_EN, LCD_LOW);
	/*Send low nipple of the command, without changing old PORTA pins(0-3)*/
	PORTA = (command << 4) | (PORTA & 0x0F);
	/*Send High pulse for 1 millisecond*/
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_EN, LCD_LOW);
	/*Wait controller to finish command*/
	_delay_ms(5);
}

void LCD_Write_Character(uint8_t character)
{
	/*Register Select pin will select data register*/
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_RS, LCD_HIGH);
	/*Read/Write pin will be write on LCD*/
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_RW, LCD_LOW);
	/*Be sure that enable is disabled*/
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_EN, LCD_LOW);
	/*Send high nipple of the command, without changing old PORTA pins(0-3)*/
	PORTA = (character & 0xF0) | (PORTA & 0x0F);
	/*Send High pulse for 1 millisecond*/
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_EN, LCD_LOW);
	/*Send low nipple of the command, without changing old PORTA pins(0-3)*/
	PORTA = (character << 4) | (PORTA & 0x0F);
	/*Send High pulse for 1 millisecond*/
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_CTRL_PORT, LCD_EN, LCD_LOW);
	/*Wait controller to finish command*/
	_delay_ms(5);
}
void LCD_Write_String(uint8_t* str)
{
	while(*str != '\0')
	{
		LCD_Write_Character(*str);
		_delay_ms(10);
		str++;
	}
}
