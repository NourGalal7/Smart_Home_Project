/*
 * LM35_interface.h
 *
 * Created: 11/12/2024 07:26:55 م
 *  Author: Kareem Hussein
 */ 


#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_


/* MACROS for ADC channel number for lm35 */
#define LM35_ADC_CHANNEL_0			0
#define LM35_ADC_CHANNEL_1			1
#define LM35_ADC_CHANNEL_2			2
#define LM35_ADC_CHANNEL_3			3
#define LM35_ADC_CHANNEL_4			4
#define LM35_ADC_CHANNEL_5			5
#define LM35_ADC_CHANNEL_6			6
#define LM35_ADC_CHANNEL_7			7


                            /*************** APIS PROTOTYPES ***************/
							
void LM35_voidInit          (u8 copy_u8ChannelId);
void LM35_voidGetTemperature(u8 copy_u8ChannelId, u8* copy_u8Temperature);


#endif /* LM35_INTERFACE_H_ */