/*
 * OneWire.c
 *
 * Created: 26.12.2015 17:20:52
 *  Author: viktorpanasiuk
 */

#define RESET_PULSE_DURATION	500 // uS
#define PRESENCE_PULSE_DURATION	500 // uS
#define PRESENCE_PULSE_CHECKING	10	// uS
#define TIME_SLOT_DURATION		100	// uS
#define SLOT_INIT_DURATION		5	// uS
#define PAUSE_BETWEEN_SLOTS		2	// uS
#define WRITE_0_DURATION		TIME_SLOT_DURATION
#define WRITE_1_DURATION		SLOT_INIT_DURATION
#define READ_INITIALIZE			SLOT_INIT_DURATION
#define MASTER_READ_SAMPLE		14	// uS


/*
*  ----       ----------------
*      |     /                |
*      |____/                 |__
*/

#include "1-Wire.h"
#include "GPIO.h"
#include <util/delay.h>
#include <util/atomic.h>

static void write0Slot(void)
{
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		pullDQLow(); /* Pull DQ pin low */
		_delay_us(WRITE_0_DURATION); /* Wait */
		releaseDQ(); /* Release DQ pin */
		_delay_us(TIME_SLOT_DURATION - WRITE_0_DURATION);	/* Waiting for the end of slot */
		while (!readDQ()) /* Waiting for the high DQ state */
			;
		_delay_us(PAUSE_BETWEEN_SLOTS); /* Pause between slots */
	}
}

static void write1Slot(void)
{
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		pullDQLow(); /* Pull DQ pin low */
		_delay_us(WRITE_1_DURATION); /* Wait */
		releaseDQ(); /* Release DQ pin */
		_delay_us(TIME_SLOT_DURATION - WRITE_1_DURATION);	/* Waiting for the end of slot */
		while (!readDQ()) /* Waiting for the high DQ state */
			;
		_delay_us(PAUSE_BETWEEN_SLOTS); /* Pause between slots */
	}
}

static uint8_t readSlot(void)
{
	uint8_t state; /* State of DQ pin*/
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		pullDQLow(); /* Pull DQ pin low */
		_delay_us(READ_INITIALIZE); /* Wait */
		releaseDQ(); /* Release DQ pin */
		_delay_us(MASTER_READ_SAMPLE - READ_INITIALIZE); /* Wait */
		state = readDQ(); /* Read DQ pin state */
		_delay_us(TIME_SLOT_DURATION - MASTER_READ_SAMPLE); /* Waiting for the end of slot */
		while (!readDQ()) /* Waiting for the high DQ state */
			;
		_delay_us(PAUSE_BETWEEN_SLOTS); /* Pause between slots */
	}
	return state; /* Return state of DQ */
}

void waitUnill1WireDeviceIsInProgress(void)
{
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		while (!readSlot()) /* Wait until read slot returns not 0 */
			;
	}
}

void resetPulse(void)
{
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		pullDQLow(); /* Pull DQ pin low */
		_delay_us(RESET_PULSE_DURATION); /* Wait */
		releaseDQ(); /* Release DQ pin */
		while (!readDQ()) /* Waiting for the high DQ state */
			;
	}
}

uint8_t presencePulse(void)
{
	uint8_t state = 0; /* The default state is 0 */
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		uint8_t n = PRESENCE_PULSE_DURATION / PRESENCE_PULSE_CHECKING; /* How many times check the DQ? */
		while(n--) /* Each time */
		{
			_delay_us(PRESENCE_PULSE_CHECKING); /* After current delay */
			if (!readDQ()) /* If DQ pin was low at least once */
				state = 1; /* The state becomes 1 */
		}
	}
	return state; /* Return the state */
}

void sendByteTo1Wire(uint8_t byte)
{
	uint8_t bit = 1; /* LSB bit is set */
	while (bit) /* While bit is not 0 */
	{
		if (!(byte & bit)) /* If bit in byte is 0 */ 
			write0Slot();
		else /* If bit in byte is 1 */
			write1Slot();
		bit += bit; /* Shift the value to the 1 bit left */
	}
}

uint8_t readByteFrom1Wire(void)
{
	uint8_t byte = 0; /* Definition of returned value */
	uint8_t bit = 1; /* LSB bit is set */
	while (bit) /* While bit is not 0 */
	{
		if (readSlot() == 0) /* If read slot return 0 */
			byte &= ~bit; /* Clear appropriate bit in byte */
		else /* If read slot return 1 */
			byte |= bit; /* Set appropriate bit in byte */
		bit += bit; /* Shift the value to the 1 bit left */
	}
	return byte; /* Return byte value */
}