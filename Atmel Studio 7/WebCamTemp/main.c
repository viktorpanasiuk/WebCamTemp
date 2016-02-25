/*
 * WebCamTemp.c
 *
 * Created: 26.12.2015 19:46:54
 * Author : viktorpanasiuk
 */

#include "global.h"
#include <util/delay.h> /* For _delay_ms() function */
#include <avr/interrupt.h> /* For interrupt functions */
#include "GPIO.h"
#include "UART.h"
#include "Timer0.h"
#include "Application.h"

volatile uint8_t ledID = 0; /* Current ledID value */
volatile uint8_t ledID_prev = 255;  /* Previous ledID value */
volatile uint8_t duration = FLASH_DURATION; /* Flash duration value */

ISR(USART_RXC_vect) /* UART interrupt handler */
{
	ledID = UDR; /* Assign ledID to receive via UART value */
	if (ledID != ledID_prev) /* If current ledID equal to previous value */
	{
		turnOnLED(ledID); /* Turn on the ledID LED */
		timer0Start(); /* Start Timer0 */
		ledID_prev = ledID; /* Previous ledID assign to current */
		duration = FLASH_DURATION; /* Update LED flash duration */
	}
}

ISR(TIMER0_COMP_vect) /* Timer0 compare interrupt handler */
{
	if (--duration == 0) /* Decrement Duration value each 1ms and if it reach to 0 */
	{
		timer0Stop(); /* Stop Timer0 */
		turnOffAllLED(); /* Turn off all LEDs */
		timer0Clear(); /* Clear Timer0 counter register */
	}
}

/* Main */
int main(void)
{	
	const uint8_t ROM[][sizeof(ROM_T)] = /* ROM array */
	{
		{0x26, 0x00, 0x00, 0x04, 0x4B, 0x15, 0x89, 0x28}, // 0
		{0x71, 0x00, 0x00, 0x04, 0x4A, 0xC0, 0x65, 0x28}, // 1
		{0xA5, 0x00, 0x00, 0x04, 0x4A, 0xCB, 0xCE, 0x28}, // 2
		{0x41, 0x00, 0x00, 0x04, 0x4A, 0xAC, 0x65, 0x28}, // 3
		{0x22, 0x00, 0x00, 0x04, 0x4B, 0x06, 0x0D, 0x28}, // 4
		{0x86, 0x00, 0x00, 0x04, 0x4A, 0xF6, 0x46, 0x28}  // 5
	};
	
	uint8_t nDevices = sizeof(ROM) / sizeof(ROM_T); /* Number of DS18B20 devices */
	
	initUART(MYUBRR); /* Initialization of UART with appropriate baudrate */
	initTimer0(); /* Initialization of Timer/counter0 */
	initLED(nDevices); /* Initialization of LEDs */
	
	{ /* DS18B20s initialization */
		uint8_t nDevices = sizeof(ROM) / sizeof(ROM_T); /* Number of DS18B20 devices */
		ROM_T *pROM = (ROM_T *)&ROM; /* Pointer to ROM array */
		
		initDQ(); /* Initialization of DQ pin */
		
		while (nDevices--) /* For all DS18B20 */
			initDS18B20(pROM++, RESOLUTION_11BIT); /* Initialization of DS18B20 with appropriate resolution */
	}
	
	sei(); /* Global enable interrupts */
	
	while (1) /* Infinite loop */
	{
		sendTemperatureToUART((ROM_T *)&ROM, nDevices); /* Execute function routine */
	}
}

