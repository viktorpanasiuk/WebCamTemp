/*
 * LED.h
 *
 * Created: 30.12.2015 12:52:36
 *  Author: viktorpanasiuk
 */ 


#ifndef LED_H_
#define LED_H_

#include "global.h"

/* LEDs ID */
typedef enum {
	LED0,
	LED1,
	LED2,
	LED3,
	LED4,
	LED5,
	LED6,
	LED7
} LED_ID_T;

/*
* Turn the ID LED on
* @param LED_ID_T ID
* @return nothing
*/
inline void turnOnLED(LED_ID_T ID)
{
	PORTA |= 1<<ID; /* Turn on the ID LED */
}

/*
* Turn the ID LED off
* @param LED_ID_T ID
* @return nothing
*/
inline void turnOffLED(LED_ID_T ID)
{
	PORTA &= ~(1<<ID); /* Turn on the ID LED */
}

/*
* Turn on the all LEDs
* @param uint8_t number of LEDs
* @return nothing
*/
inline void turnOnAllLED(uint8_t nLEDs)
{
	union
	{
		uint16_t valueFull;
		uint8_t valuePart[2];
	} value;
	
	value.valueFull = 0x00FF;
	value.valueFull <<= nLEDs;
	
	PORTA = value.valuePart[0] - 1; /* Turn off all LEDs */
}

/*
* Turn off the all LEDs
* @param uint8_t number of LEDs
* @return nothing
*/
inline void turnOffAllLED()
{
	PORTA = 0x00; /* Turn off all LEDs */
}

/*
* Initialization of LEDs
* @param uint8_t number of LEDs
* @return nothing
*/
inline void initLED(uint8_t nLEDs)
{
	union
	{
		uint16_t valueFull;
		uint8_t valuePart[2];
	} value;
	
	value.valueFull = 0x00FF;
	value.valueFull <<= nLEDs;
	
	DDRA = value.valuePart[0] - 1; /* Pins as output */
	PORTA = value.valuePart[0] - 1; /* Turn off all LEDs */
}

#endif /* LED_H_ */