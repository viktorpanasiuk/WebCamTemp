/*
 * DS18B20.c
 *
 * Created: 26.12.2015 14:54:23
 *  Author: viktorpanasiuk
 */ 

#include "DS18B20.h"
#include "1-Wire.h"
#include <util/crc16.h>

#define READ_ROM			0x33
#define MATCH_ROM			0x55
#define SKIP_ROM			0xCC
#define CONVERT_T			0x44
#define WRITE_SCRATCHPAD	0x4E
#define READ_SCRATCHPAD		0xBE

const uint8_t DEVICE_ID = 0x28;

uint8_t initSequence(void)
{	
	resetPulse(); /* Issue the reset pulse */
	return presencePulse(); /* Check for presence pulse */
}

ROM_T * readROM(ROM_T *ROM)
{
	uint8_t n = sizeof(ROM_T) / sizeof(uint8_t); /* How much bytes we need to read */
	
	sendByteTo1Wire(READ_ROM); /* Send appropriate command */
	while(n--) /* For each byte in ROM */
		((uint8_t *)ROM)[n] = readByteFrom1Wire(); /* Read it value from DS18B20 */		
	return ROM; /* Return pointer to ROM */
}

void matchROM(ROM_T *ROM)
{
	uint8_t n = sizeof(ROM_T) / sizeof(uint8_t); /* How much bytes we need to send */
	
	sendByteTo1Wire(MATCH_ROM); /* Send appropriate command */
	while (n--) /* For each byte in ROM */
		sendByteTo1Wire(((uint8_t *)ROM)[n]); /* Send it value to DS18B20 */
}

void skipROM(void)
{
	sendByteTo1Wire(SKIP_ROM); /* Send appropriate command */
}

void convertTemperature(void)
{
	sendByteTo1Wire(CONVERT_T); /* Send appropriate command */
	waitUnill1WireDeviceIsInProgress();
}

void writeScratchpad(EEPROM_T * EEPROM)
{
	uint8_t *p = (uint8_t *)EEPROM; /* Cast EEPROM pointer */
	uint8_t n = sizeof(EEPROM_T) / sizeof(uint8_t); /* How much bytes we need to write */
	
	sendByteTo1Wire(WRITE_SCRATCHPAD); /* Send appropriate command */
	while (n--) /* For each byte in EEPROM */
		sendByteTo1Wire(*p++); /* Write data to DS18B20 */
}

SCRATCHPAD_T * readScratchpad(SCRATCHPAD_T * Scratchpad)
{
	uint8_t *p = (uint8_t *)Scratchpad; /* Cast scratchpad pointer */
	uint8_t n = sizeof(SCRATCHPAD_T) / sizeof(uint8_t); /* How much bytes we need to read */
	
	sendByteTo1Wire(READ_SCRATCHPAD); /* Send appropriate command */
	while (n--) /* For each byte in scratchpad */
		*p++ = readByteFrom1Wire(); /* Save the data from DS18B20 */
	return Scratchpad; /* Return pointer to scratchpad */
}

uint8_t isValidCRC(SCRATCHPAD_T *Scratchpad)
{
	uint8_t n = sizeof(SCRATCHPAD_T) / sizeof(uint8_t); /* Bytes in scratchpad */
	uint8_t *p = (uint8_t *)Scratchpad; /* Cast scratchpad pointer to uint8_t */
	uint8_t crc = 0; /* Initial value for CRC */
	/* For each byte in scratchpad except the last one */
	for (uint8_t i = 0; i < (n-1); i++)
		crc = _crc_ibutton_update(crc, *p++); /* Get CRC for byte */
	/* If the calculated CRC equal to required one then return the 1, otherwise 0 */
	return crc == *p ? 1 : 0 ;
}