/*
 * ADC_interface.h
 *
 * Created: 09/12/2024 09:57:44 م
 *  Author: Kareem Hussein
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


/* MACROS for Reference Voltage */
#define ADC_REFERENCE_AVCC			0
#define ADC_REFERENCE_AREF			1
#define ADC_REFERENCE_INTRNAL       2

/* MACROS for Channel Number as Single Ended Input */
#define ADC_CHANNEL_0			0
#define ADC_CHANNEL_1			1
#define ADC_CHANNEL_2			2
#define ADC_CHANNEL_3			3
#define ADC_CHANNEL_4			4
#define ADC_CHANNEL_5			5
#define ADC_CHANNEL_6			6
#define ADC_CHANNEL_7			7

                        /*************** APIS PROTOTYPES ***************/

void ADC_voidInit           (u8 copy_u8ReferenceVoltage);
void ADC_voidGetDigitalValue(u8 copy_u8ChannelId, u16* copy_pu16DigitalValue);


#endif /* ADC_INTERFACE_H_ */