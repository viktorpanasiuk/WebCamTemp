/*
 * OneWire.h
 *
 * Created: 26.12.2015 17:20:42
 *  Author: viktorpanasiuk
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <stdint.h>

/*
* Wait until 1-wire device is in progress
* @param nothing
* @return nothing
*/
void waitUnill1WireDeviceIsInProgress(void);

/*
* Issuing of the reset pulse
* @param nothing
* @return nothing
*/
void resetPulse(void);

/*
* Checking for appearance of presence pulse
* The state is 0 if the presence pulse is absent and 1 in other case
* @param nothing
* @return uint8_t state
*/
uint8_t presencePulse(void);

/*
* Sending one byte to 1-Wire device
* @param uint8_t sending byte
* @return nothing
*/
void sendByteTo1Wire(uint8_t byte);

/*
* Reading the one byte from 1-Wire interface
* @param nothing
* @return uint8_t reading byte
*/
uint8_t readByteFrom1Wire(void);

#endif /* ONEWIRE_H_ */