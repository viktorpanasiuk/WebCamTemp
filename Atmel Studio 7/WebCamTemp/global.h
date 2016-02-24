/*
 * global.h
 *
 * Created: 26.12.2015 22:03:09
 *  Author: viktorpanasiuk
 */ 

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <avr/io.h>

/* Definition of CPU frequency */
#define F_CPU 16000000UL /* CPU frequency for _delay_us() function */

/* Definition for UART */
#define BAUD 250000 /* UART baudrate */
#define MYUBRR F_CPU/16/BAUD-1

/* Definition for DS18B20 */
#define DQ_PIN	PINB /* Input pin register for DQ pin */
#define DQ_PORT	PORTB /* Output port register for DQ pin */ 
#define DQ_DDR	DDRB /* Port direction register for DQ pin */
#define DQ_PINX	(1<<PB0) /* Pin number of output port for DQ pin */
#define DQ_DDRX	(1<<DDB0) /* Pin number of port direction for DQ pin*/

/* Definition for LED */
#define LED0_PORT	PORTA /* Output port register for LED0 */
#define LED0_PIN	(1<<PA0) /* Input port register for LED0 */
#define LED0_DDR	DDRA /* Direction register for LED0 */
#define LED0_DDRX	(1<<DDA0) /* Pin number of output port register for LED0 */
//---------------------------
#define LED1_PORT	PORTA /* Output port register for LED1 */
#define LED1_PIN	(1<<PA1) /* Input port register for LED1 */
#define LED1_DDR	DDRA /* Direction register for LED1 */
#define LED1_DDRX	(1<<DDA1) /* Pin number of output port register for LED1 */
//---------------------------
#define LED2_PORT	PORTA /* Output port register for LED2 */
#define LED2_PIN	(1<<PA2) /* Input port register for LED2 */
#define LED2_DDR	DDRA /* Direction register for LED2 */
#define LED2_DDRX	(1<<DDA2) /* Pin number of output port register for LED2 */
//---------------------------
#define LED3_PORT	PORTA /* Output port register for LED3 */
#define LED3_PIN	(1<<PA3) /* Input port register for LED3 */
#define LED3_DDR	DDRA /* Direction register for LED3 */
#define LED3_DDRX	(1<<DDA3) /* Pin number of output port register for LED3 */
//---------------------------
#define LED4_PORT	PORTA /* Output port register for LED4 */
#define LED4_PIN	(1<<PA4) /* Input port register for LED4 */
#define LED4_DDR	DDRA /* Direction register for LED4 */
#define LED4_DDRX	(1<<DDA4) /* Pin number of output port register for LED4 */
//---------------------------
#define LED5_PORT	PORTA /* Output port register for LED5 */
#define LED5_PIN	(1<<PA5) /* Input port register for LED5 */
#define LED5_DDR	DDRA /* Direction register for LED5 */
#define LED5_DDRX	(1<<DDA5) /* Pin number of output port register for LED5 */

/* Definition of flash duration */
#define FLASH_DURATION 15 /* Flash duration of each LED */
#endif /* GLOBAL_H_ */