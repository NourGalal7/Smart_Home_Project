/*
 * LED_interface.h
 *
 * Created: 18/11/2024 10:07:07 م
 *  Author: Kareem Hussein
 */ 


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_


#define	LED_FORWARD_CONNECTION			0
#define	LED_REVERSE_CONNECTION			1

                   /*************** APIS PROTO TYPES ***************/

void LED_voidInit  (u8 copy_u8LedPort, u8 copy_u8LedPin);
void LED_voidOn    (u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType);
void LED_voidOff   (u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType);
void LED_voidToggle(u8 copy_u8LedPort, u8 copy_u8LedPin);


#endif /* LED_INTERFACE_H_ */