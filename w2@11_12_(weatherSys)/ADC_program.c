﻿/*
 * ADC_program.c
 *
 * Created: 09/12/2024 09:57:18 م
 *  Author: Kareem Hussein
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "ADC_interface.h"
#include "ADC_register.h"


void ADC_voidInit(u8 copy_u8ReferenceVoltage)
{
	switch(copy_u8ReferenceVoltage)
	{
		case ADC_REFERENCE_AREF:
		CLR_BIT(ADMUX_REG, REFS0);
		CLR_BIT(ADMUX_REG, REFS1);
		break;
		
		case ADC_REFERENCE_AVCC:
		SET_BIT(ADMUX_REG, REFS0);
		CLR_BIT(ADMUX_REG, REFS1);
		break;
		
		case ADC_REFERENCE_INTRNAL:
		SET_BIT(ADMUX_REG, REFS0);
		SET_BIT(ADMUX_REG, REFS1);
		break;
	}
	
	// Select Right Adjustment 
	CLR_BIT(ADMUX_REG, ADLAR);
	
	// Single Conversion Mode
	CLR_BIT(ADCSRA_REG, ADATE);
	
	//Disable ADC Interrupt
	CLR_BIT(ADCSRA_REG, ADIE);
	
	// Prescaler 128 For 16MHZ (125 KHZ)
	SET_BIT(ADCSRA_REG, ADPS0);
	SET_BIT(ADCSRA_REG, ADPS1);
	SET_BIT(ADCSRA_REG, ADPS2);
	
	// ADC Enable
	SET_BIT(ADCSRA_REG, ADEN);
}


void ADC_voidGetDigitalValue(u8 copy_u8ChannelId, u16* copy_pu16DigitalValue)
{
	if((copy_pu16DigitalValue != NULL) && (copy_u8ChannelId < 32))
	{
		//Clear ADMUX Channel Bits
		ADMUX_REG &= 0xE0; //0b11100000
		
		// Select Channel Number
		ADMUX_REG |= copy_u8ChannelId;
		
		// Start conversion
		SET_BIT(ADCSRA_REG, ADSC);
		
		// Busy Wait for ADC Flag
		while(0 == GET_BIT(ADCSRA_REG ,ADIF));
		
		// Clear ADC flag (WROC >> Write One to Clear)
		SET_BIT(ADCSRA_REG ,ADIF);
		
		// Pass out ADC data 
		*copy_pu16DigitalValue = ADC_u16_REG;
	}
	else
	{
		//return Error State
	}
}