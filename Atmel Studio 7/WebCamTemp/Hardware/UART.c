/*
 * UART.c
 *
 * Created: 27.12.2015 10:13:20
 *  Author: viktorpanasiuk
 */

#include "UART.h"

/* Send data to UART */
void sendDataToUART(uint8_t *data, uint8_t n)
{
	while (n--) /* For all number of bytes */
		sendByteToUART(*data++); /* Send data to UART */
}

/* Read data from UART */
uint8_t * readDataFromUART(uint8_t *data, uint8_t n)
{
	uint8_t *p = data; /* Pointer to data */
	while(n--) /* For all number of bytes */
		*p++ = readByteFromUART(); /* Save byte from UART */
	return data; /* Return pointer to data */
}

/* Send string to UART */
void sendTextToUART(const char *string)
{
	while (1) /* Infinite loop */
	{
		if (*string == '\0') /* If null character */
			return; /* Then return */
		sendByteToUART(*string++); /* Send byte to UART */
	}
}