/*
 * LM35_program.c
 *
 * Created: 11/12/2024 07:26:25 م
 *  Author: Kareem Hussein
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "ADC_interface.h"

/* HAL */
#include "LM35_interface.h"


void LM35_voidInit(u8 copy_u8ChannelId)
{
	DIO_voidSetPinDirection(DIO_PORTA, copy_u8ChannelId, DIO_PIN_INPUT);
	
	ADC_voidInit(ADC_REFERENCE_INTRNAL);
}


void LM35_voidGetTemperature(u8 copy_u8ChannelId, u8* copy_u8Temperature)
{
	if(copy_u8Temperature != NULL)
	{
		u16 local_u16DigitalVal, local_u16AnaloglVal;
		
		ADC_voidGetDigitalValue(copy_u8ChannelId, &local_u16DigitalVal);
		
		local_u16AnaloglVal = ((u32)local_u16DigitalVal * 2560) / 1024;
		
		*copy_u8Temperature = 	local_u16AnaloglVal/10;
	}
	else
	{
		//return Error State
	}
}