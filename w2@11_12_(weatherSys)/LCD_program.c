/*
 * LCD_program.c
 *
 * Created: 19/11/2024 09:45:47 م
 *  Author: Kareem Hussein
 */ 


#define F_CPU			16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"


void LCD_voidInit(void)
{
	DIO_voidSetPinDirection(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_E_PORT,  LCD_E_PIN,  DIO_PIN_OUTPUT);
	
	_delay_ms(40);
	
	/* Function Set (2Lines, 5*7 font) */
	// Select write operation (R/W = 0)
	DIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	// Select Instruction Register[command] (RS = 0)
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	PRV_voidWriteHalfPort(0b0010);
	/* Enable */
	PRV_voidEnableTriggerWrite();
	LCD_voidSendCommand(0b00101000);
	_delay_us(45);
	
	/* Display On/Off Control (DisplayOn, CursorOn, BlinkOn) */
	LCD_voidSendCommand(0b00001111);
	_delay_us(45);
	
	/* Display Clear */
	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);
	
	/* Entry Mode Set (IncrementOn, ShiftOff) */
	LCD_voidSendCommand(0b00000110);
}


void LCD_voidSendCommand(u8 copy_u8cmnd) 
{
	// Select write operation (R/W = 0)
	DIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);	
	
	// Select Instruction Register[command] (RS = 0)
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	
	// Write The Most 4 bits Of command on Data Pins
	PRV_voidWriteHalfPort(copy_u8cmnd >> 4);
	
	/* Enable */
	PRV_voidEnableTriggerWrite();
	
	// Write The Least 4 bits Of command on Data Pins
	PRV_voidWriteHalfPort(copy_u8cmnd);
	
	/* Enable */
	PRV_voidEnableTriggerWrite();
}


void LCD_voidDisplayChar(u8 copy_u8Data)
{
	// Select write operation (R/W = 0)
	DIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	
	// Select Data Register[data] (RS = 1)
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
	
	// Write The Most 4 bits Of data on Data Pins
	PRV_voidWriteHalfPort(copy_u8Data >> 4);
	
	/* Enable */
	PRV_voidEnableTriggerWrite();
	
	// Write The Least 4 bits Of data on Data Pins
	PRV_voidWriteHalfPort(copy_u8Data);
	
	/* Enable */
	PRV_voidEnableTriggerWrite();
}


void LCD_voidDisplayString(u8* copy_Pu8String)
{
	if(copy_Pu8String != NULL)
	{
		u8 local_u8Counter = 0;
		while(copy_Pu8String[local_u8Counter] != '\0')
		{
			LCD_voidDisplayChar(copy_Pu8String[local_u8Counter]);
			local_u8Counter++;
		}
	}
	else
	{
		// return Error State
	}
}


void LCD_voidDisplayNumber(u32 copy_u32Number) //79
{
	u32 local_u32ReversedNumber = 1;
	if(copy_u32Number == 0)
	{
		LCD_voidDisplayChar('0');
	}
	else
	{
		while(copy_u32Number != 0)
		{
			local_u32ReversedNumber = (local_u32ReversedNumber * 10)+ (copy_u32Number % 10);//197
			copy_u32Number /= 10;
		}
		
		do 
		{
			LCD_voidDisplayChar((local_u32ReversedNumber % 10) + '0');
			local_u32ReversedNumber /= 10; 
		} while (local_u32ReversedNumber != 1);
	}
}


void LCD_voidClear(void)
{
	/* Display Clear */
	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);
}


void LCD_voidGoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position)
{
	switch(copy_u8LineNumber)
	{
		case LCD_LINE_ONE:
		LCD_voidSendCommand(0b10000000+copy_u8Position); //0x80+copy_u8Position
		_delay_us(45);
		break;
		
		case LCD_LINE_TWO:
		LCD_voidSendCommand(0b11000000+copy_u8Position); //0xC0+copy_u8Position
		_delay_us(45);
		break;
	}
}


static void PRV_voidEnableTriggerWrite(void)
{
	/* Enable Pulse *//* H => L */
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);	
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);
}


static void PRV_voidWriteHalfPort(u8 copy_u8Value)
{
	DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(copy_u8Value, 0));
	DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(copy_u8Value, 1));
	DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(copy_u8Value, 2));
	DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(copy_u8Value, 3));
}