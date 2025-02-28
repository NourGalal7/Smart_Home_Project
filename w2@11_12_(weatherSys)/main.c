/*
 * w2@11_12.c
 *
 * Created: 11/12/2024 09:26:20 م
 * Author : Kareem Hussein
 */ 


#define F_CPU			16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "ADC_interface.h"

/* HAL */
#include "LED_interface.h"
#include "LCD_interface.h"
#include "LM35_interface.h"


int main(void)
{
	u8 temp;
    LM35_voidInit(LM35_ADC_CHANNEL_0);
	LCD_voidInit();
	LED_voidInit(DIO_PORTC, DIO_PIN2); //LED0 G
	LED_voidInit(DIO_PORTC, DIO_PIN7); //LED1 Y
	LED_voidInit(DIO_PORTD, DIO_PIN3); //LED2 B
	LED_voidInit(DIO_PORTA, DIO_PIN3); //LED3 R
	
	LCD_voidDisplayString((u8*)"Auto. Weather System");
	_delay_ms(1000);
	LCD_voidClear();
	
    while (1) 
    {
		LM35_voidGetTemperature(LM35_ADC_CHANNEL_0, &temp);
		
		LCD_voidDisplayString((u8*)"Temp. is: ");
		LCD_voidDisplayNumber(temp);
		if(temp < 15)
		{
			LED_voidOn (DIO_PORTC, DIO_PIN2, LED_FORWARD_CONNECTION); //LED0 G
			LED_voidOff(DIO_PORTC, DIO_PIN7, LED_FORWARD_CONNECTION); //LED1 Y
			LED_voidOff(DIO_PORTD, DIO_PIN3, LED_FORWARD_CONNECTION); //LED2 B
			LED_voidOff(DIO_PORTA, DIO_PIN3, LED_FORWARD_CONNECTION); //LED3 R
		}
		else if(temp < 25)
		{
				LED_voidOff(DIO_PORTC, DIO_PIN2, LED_FORWARD_CONNECTION); //LED0 G
				LED_voidOn (DIO_PORTC, DIO_PIN7, LED_FORWARD_CONNECTION); //LED1 Y
				LED_voidOff(DIO_PORTD, DIO_PIN3, LED_FORWARD_CONNECTION); //LED2 B
				LED_voidOff(DIO_PORTA, DIO_PIN3, LED_FORWARD_CONNECTION); //LED3 R
		}
		else if(temp < 35)
		{
				LED_voidOff(DIO_PORTC, DIO_PIN2, LED_FORWARD_CONNECTION); //LED0 G
				LED_voidOff(DIO_PORTC, DIO_PIN7, LED_FORWARD_CONNECTION); //LED1 Y
				LED_voidOn (DIO_PORTD, DIO_PIN3, LED_FORWARD_CONNECTION); //LED2 B
				LED_voidOff(DIO_PORTA, DIO_PIN3, LED_FORWARD_CONNECTION); //LED3 R
		}
		else if(temp <= 50)
		{
				LED_voidOff(DIO_PORTC, DIO_PIN2, LED_FORWARD_CONNECTION); //LED0 G
				LED_voidOff(DIO_PORTC, DIO_PIN7, LED_FORWARD_CONNECTION); //LED1 Y
				LED_voidOff(DIO_PORTD, DIO_PIN3, LED_FORWARD_CONNECTION); //LED2 B
				LED_voidOn (DIO_PORTA, DIO_PIN3, LED_FORWARD_CONNECTION); //LED3 R
		}
		_delay_ms(1000);
		LCD_voidClear();
    }
}

