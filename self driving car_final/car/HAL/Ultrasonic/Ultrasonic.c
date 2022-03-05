/*
 * Ultrasonic.c
 *
 * Created: 2/17/2022 8:10:14 PM
 *  Author: User
 */ 
#include "Ultrasonic.h"
       
static volatile uint16_t distance_of_pulse  = 0; //variable to save the time of high pulse of echo until its falling
static volatile uint16_t echo_pin_value     = 0;// flag
uint16_t Ultrasonic(void)
{
	DIO_SetPinDirection(TRIG_PORT, TRIG_PIN,DIO_OUTPUT);
	GICR  |= 1<<INT0 ; //	Enable Peripheral interrupt
	MCUCR |= 1<<ISC00; 
	uint16_t count_a=0; /*variable use to save the time has taken between triggering of ultrasonic and interruption of echo */
	sei();//Enable global interrupt
	while (1) 
     {
		DIO_SetPinValue(TRIG_PORT,TRIG_PIN,DIO_HIGH);//set trigger pin high
		_delay_us(15);
		DIO_SetPinValue(TRIG_PORT,TRIG_PIN,DIO_LOW);//set trigger pin low
		count_a=distance_of_pulse/58;	//distance in centimeters
		return count_a;//return distance in centimeters
     }
   	   
}
ISR(INT0_vect)
{
	if (echo_pin_value==1)
	{
		TCCR1B =0;// stop the timer
		distance_of_pulse=TCNT1;
		TCNT1=0;
		echo_pin_value=0;
	}
	else if (echo_pin_value==0)
	{
		TCCR1B |= 1<<CS10; //START TIMER 1
		echo_pin_value=1;
	}
}




