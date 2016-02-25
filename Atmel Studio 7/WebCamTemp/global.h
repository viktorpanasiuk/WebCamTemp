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

/* Definition of flash duration */
#define FLASH_DURATION 15 /* Flash duration of each LED */

#endif /* GLOBAL_H_ */