/*
 * Application.h
 *
 * Created: 27.12.2015 13:06:46
 *  Author: viktorpanasiuk
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "DS18B20.h"

/*
* This function use for getting ROM from individual DS18B20
* The first configure the DQ pin of DS18B20 in gloabl.h file
* The second place both initUART() and initDS18B20() to DEVICE INITIALIZATION section before using
* The ROM transmit to UART as 8 bytes
* @param nothing
* @return nothing
*/
void sendROMToUART(void);

/*
* This function use for getting ROM from individual DS18B20
* The first configure the DQ pin of DS18B20 in gloabl.h file
* The second place both initUART() and initDS18B20() before using
* The ROM transmit to UART as 8 bytes
* @param nothing
* @return nothing
*/
void sendTemperatureToUART(ROM_T ROM[], uint8_t nDevices);

/*
* Providing of initialization of DS18B20
* @param ROM_T ROM
* @param RESOLUTION_T resolution
* @return nothing
*/
void initDS18B20(ROM_T *ROM, RESOLUTION_T Resolution);

#endif /* APPLICATION_H_ */