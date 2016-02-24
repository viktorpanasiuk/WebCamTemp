/*
 * Timer0.h
 *
 * Created: 03.01.2016 14:15:17
 *  Author: viktorpanasiuk
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

/*
* Initialization of Timer/Counter0
* @param nothing
* @return nothing
*/
inline void initTimer0(void)
{
	TCCR0 = (1<<WGM01); /* CTC mode for Timer0 */
	TCNT0 = 0; /* Clear counter register */
	OCR0 = 250; /* 1ms period for 1/64 prescaller and 16MHz */
	TIMSK |= (1<<OCIE0); /* Enable on compare interrupt handler for Timer0 */
}

/*
* Start the Timer/Counter0
* @param nothing
* @return nothing
*/
inline void timer0Start(void)
{
	TCCR0 |= (3<<CS00); /* Start Timer0 */
}

/*
* Stop the Timer/Counter0
* @param nothing
* @return nothing
*/
inline void timer0Stop(void)
{
	TCCR0 &= ~(7<<CS00); /* Stop Timer0 */
}

/*
* Clear the counter register of the Timer/Counter0
* @param nothing
* @return nothing
*/
inline void timer0Clear(void)
{
	TCNT0 = 0; /* Clear counter register of Timer0 */
}

#endif /* TIMER0_H_ */