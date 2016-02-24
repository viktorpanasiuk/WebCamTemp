/*
 * DS18B20.h
 *
 * Created: 26.12.2015 14:54:37
 *  Author: viktorpanasiuk
 */ 

#ifndef DS18B20_H_
#define DS18B20_H_

#include <stdint.h>

/* ROM data structure */
typedef struct
{
	uint8_t CRC;
	uint8_t SerialNumber[6];
	uint8_t FamilyCode;
} ROM_T;

/* EEPROM data structure */
typedef struct 
{	
	uint8_t THRegister;
	uint8_t TLRegister;
	uint8_t ConfigurationRegister;
} EEPROM_T;

/* Scratchpad data structure */
typedef struct 
{
	uint8_t TemperatureLSB;
	uint8_t TemperatureMSB;
	uint8_t THRegister;
	uint8_t TLRegister;
	uint8_t ConfigurationRegister;
	uint8_t Reserved[3];
	uint8_t CRC;
} SCRATCHPAD_T;

/* Configuration bits */
enum {
	R0 = 1<<5,
	R1 = 1<<6
};

/* Resolution of DS18B20 */
typedef enum
{
	RESOLUTION_9BIT		= 0,
	RESOLUTION_10BIT	= R0,
	RESOLUTION_11BIT	= R1,
	RESOLUTION_12BIT	= R0|R1
} RESOLUTION_T;

/*
* Providing of initialize sequence for DS18B20
* The state is 0 if the presence pulse is absent and 1 in other case
* @param nothing
* @return uint8_t state
*/
uint8_t initSequence(void);

/***************
* ROM COMMANDS *
***************/

/*
* Search ROM command
* Searching of all existing 1-Wire devices
* @param nothing
* @return nothing
*/
void searchROM(void);

/*
* Read ROM command
* Reading the ROM of the lonely 1-Wire device
* @param ROM_T * pointer to value in which ROM will be saved 
* @return ROM_T * pointer to ROM value
*/
ROM_T * readROM(ROM_T *ROM);

/*
* Match ROM command
* Issuing of the ROM into 1-Wire line
* @param ROM_T * pointer to ROM value
* @return nothing
*/
void matchROM(ROM_T *ROM);

/*
* Skip ROM command
* Issuing of skip ROM command
* @param nothing
* @return nothing
*/
void skipROM(void);

/*
* Alarm search command
* Searching of all DS18B20 devices in alarm state
* @param nothing
* @return nothing
*/
void alarmSearch(void);

/********************
* FUNCTION COMMANDS *
********************/

/*
* Convert T command
* Triggering the conversion temperature procedure for all DS18B20
* @param nothing
* @return nothing
*/
void convertTemperature(void);

/*
* Read scratchpad command
* Reading of the current content of DS18B20
* @param nothing
* @return nothing
*/
void writeScratchpad(EEPROM_T * EEPROM);

/*
* Read scratchpad command
* Reading of the current content of DS18B20
* @param SCRATCHPAD_T * pointer to structure, where the data will be saved
* @return SCRATCHPAD_T * pointer to the structure
*/
SCRATCHPAD_T * readScratchpad(SCRATCHPAD_T * Scratchpad);

/*
* Copy scratchpad command
* Saving of the part of scratch pad to DS18B20 EEPROM
* @param nothing
* @return nothing
*/
void copyScratchpad(void);

/*
* RecallE2 command
* Restoring of the part of scratch pad from DS18B20 EEPROM
* @param nothing
* @return nothing
*/
void recallE2(void);

/*
* Read power supply command
* Reading the type of power supplying for DS18B20
* @param nothing
* @return uint8_t state
*/
uint8_t readPowerSupply(void);

/*
* Check is the CRC is valid?
* Return 1 if CRC test done and 0 if failed
* @param SCRATCHPAD_T * pointer to scratchpad structure
* @return uint8_t state
*/
uint8_t isValidCRC(SCRATCHPAD_T *Scratchpad);

#endif /* DS18B20_H_ */