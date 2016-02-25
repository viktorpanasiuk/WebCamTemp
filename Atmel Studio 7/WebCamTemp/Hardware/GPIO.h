/*
 * GPIO.h
 *
 * Created: 26.12.2015 17:24:56
 *  Author: viktorpanasiuk
 */ 

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "global.h"

/*
* Initial setting of DQ
* @param nothing
* @return nothing
*/
inline void initDQ(void)
{
	DQ_DDR &= ~DQ_DDRX; /* Set DQ as input */
	DQ_PORT &= ~DQ_PINX; /* Set DQ pin level to 0 */
}

/*
* Pulling the DQ pin of DS18B20 to low
* @param nothing
* @return nothing
*/
inline void pullDQLow(void)
{
	DQ_DDR |= DQ_DDRX;  /* Set DQ as output */
}

/*
* Release the DQ pin of DS18B20
* @param nothing
* @return nothing
*/
inline void releaseDQ(void)
{
	DQ_DDR &= ~DQ_DDRX; /* Set DQ as input */
}

/*
* read the current state of DQ line
* Return 0 if line is low and not 0 in other case
* @param nothing
* @return uint8_t state
*/
inline uint8_t readDQ(void)
{
	return DQ_PIN & DQ_PINX;  /* Return DQ current level */
}

/*
* Turn the ID LED on
* @param LED_ID_T ID
* @return nothing
*/
inline void turnOnLED(uint8_t ID)
{
	PORTA |= 1<<ID; /* Turn on the ID LED */
}

/*
* Turn the ID LED off
* @param LED_ID_T ID
* @return nothing
*/
inline void turnOffLED(uint8_t ID)
{
	PORTA &= ~(1<<ID); /* Turn on the ID LED */
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
	PORTA = value.valuePart[0] - 1; /* Turn on all necessary LEDs */
}

#endif /* GPIO_H_ */