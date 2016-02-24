/*
 * UART.h
 *
 * Created: 27.12.2015 10:16:27
 *  Author: viktorpanasiuk
 */ 

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <avr/io.h>

/*
* Initialization of UART
* @param uint16_t value of ubrr register
* @return nothing
*/
inline void initUART(uint16_t ubrr)
{
	/* Set the baud rate */
	UBRRH = (uint8_t)(ubrr >> 8);
	UBRRL = (uint8_t)(ubrr);
	/* Enable RX interrupt, transmitting and receiving */
	UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
	/* 8 bit data, 1 stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}

/*
* Send single byte to UART
* @param uint8_t byte
* @return nothing
*/
inline void sendByteToUART(uint8_t byte)
{
	while (!(UCSRA & (1<<UDRE))) /* Wait till UDR completely transmit the byte */
		;
	UDR = byte; /* Send byte */
}

/*
* Read single byte from UART
* @param nothing
* @return uint8_t byte
*/
inline uint8_t readByteFromUART(void)
{
	while(!(UCSRA & (1<<RXC))) /* Wait till UART completely receive the byte */
		;
	return UDR; /* Return UDR */
}

/*
* Send data to UART
* @param uint8t * pointer to data
* @param uint8_t number of bytes
* @return nothing
*/
void sendDataToUART(uint8_t *data, uint8_t n);

/*
* Read data from UART
* @param uint8t * pointer to data
* @param uint8_t number of bytes
* @return uint8_t * pointer to data
*/
uint8_t * readDataFromUART(uint8_t *data, uint8_t n);

/*
* Send string to UART
* @param const char * pointer to string
* @return nothing
*/
void sendTextToUART(const char * string);

#endif /* UART_H_ */