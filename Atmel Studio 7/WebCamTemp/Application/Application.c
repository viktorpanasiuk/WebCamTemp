/*
 * Application.c
 *
 * Created: 27.12.2015 13:06:34
 *  Author: viktorpanasiuk
 */ 

#include "Application.h"
#include <util/crc16.h>
#include "DS18B20.h"
#include "UART.h"

/* Read ROM address of the DS18B20 and send it to UART */
void sendROMToUART(void)
{
	/* Definition a local variable for ROM */
	ROM_T ROM;
	/* If presence pulse is absent - return */
	if (!initSequence())
		return;
	/* Read ROM to local variable */
	readROM(&ROM);
	/* Send ROM value to UART */
	sendDataToUART((uint8_t *)&ROM, sizeof(ROM_T));
}

/* Read temperature from DS18B20 and send it to UART */
void sendTemperatureToUART(ROM_T ROM[], uint8_t nDevices)
{	
	if (!initSequence()) /* Initialization sequence for DS18B20 */
		return; /* If presence pulse is absent - return */
	skipROM(); /* Skip ROM command */
	convertTemperature(); /* Convert T command */
	
	while (nDevices--) /* For each device */
	{
		SCRATCHPAD_T Scratchpad; /* Variable for scratch pad */
				
		if (!initSequence()) /* Initialization sequence for DS18B20 */
			return; /* If presence pulse is absent - return */
		matchROM(ROM++); /* Match ROM command */
		readScratchpad(&Scratchpad); /* Read scratch pad command */
		
		if (isValidCRC(&Scratchpad))
		{
			sendByteToUART(Scratchpad.TemperatureLSB); /* Send LSB temperature to UART */
			sendByteToUART(Scratchpad.TemperatureMSB); /* Send MSB temperature to UART */
		}
		else
		{
			sendByteToUART(0xFF); /* Send failed LSB temperature to UART */
			sendByteToUART(0x0F); /* Send failed MSB temperature to UART */
		}
	}
}

/* Initialization of the appropriate DS18B20 by specific resolution value */
void initDS18B20(ROM_T *ROM, RESOLUTION_T Resolution)
{
	SCRATCHPAD_T Scratchpad; /* Local variable for scratch pad data */
	EEPROM_T *EEPROM = (EEPROM_T *)&Scratchpad.THRegister; /* Pointer to EEPROM data */
	
	if (!initSequence()) /* Initialization sequence for DS18B20 */
		return; /* If presence pulse is absent - return */
	matchROM(ROM); /* Match ROM command */
	readScratchpad(&Scratchpad); /* Read scratch pad data from DS18B20 */
	
	Scratchpad.ConfigurationRegister = Resolution; /* Set configuration register */
	
	if (!initSequence()) /* Initialization sequence for DS18B20 */
		return; /* If presence pulse is absent - return */
	matchROM(ROM); /* Match ROM command */
	writeScratchpad(EEPROM); /* Write scratch pad command */
}