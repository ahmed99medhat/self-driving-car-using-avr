/*
* Interfacing_Module_D22.c
*
* Created: 2/15/2022 12:10:23 PM
* Author : User
*/

#include "main.h"

	volatile uint16_t distance_front_the_ultra=0;//variable to get the distance of object front the ultrasonic
	

int main(void)
{
	LCD_Initialization();
	ServoMotor_Initialization();
	Motor_Initialization();
	while (1)
	{
		distance_front_the_ultra=Ultrasonic();//to get the distance of object front the ultrasonic
		if(distance_front_the_ultra>=35)
		{
			Motor_Start(Motor1, Motor_CW);
			Motor_Start(Motor2, Motor_CW);//move forward
			_delay_ms(15);
			Motor_Stop(Motor1);
			Motor_Stop(Motor2);
			LCD_Write_String("forward");
			_delay_ms(15);
		}
		else if (distance_front_the_ultra<35)
		{
			ServoMotor_Rotate(90);//rotate the servo 90 degree to the right
			distance_front_the_ultra=Ultrasonic();//to get new value after rotation
			                    if(distance_front_the_ultra>=35)
			                    {
									 LCD_Clear();
									 LCD_Write_String("right");
				                       Motor_Start(Motor1,Motor_CW);//move right
			                           Motor_Stop(Motor1);
									    _delay_ms(1000);//////////////////////////////////////////////////////////////
				                       ServoMotor_Rotate(-90);//to return to the initial position 
									   
									  
			                    }
			                    else if (distance_front_the_ultra<35)
			                    {
			                   	       ServoMotor_Rotate(-180);//to rotate servo 90 degree to the left
									   distance_front_the_ultra=Ultrasonic();//to get new value after rotation  
										  if (distance_front_the_ultra>=35)
										  {
											   LCD_Clear();
											   LCD_Write_String("left");
											  Motor_Start(Motor1,Motor_CW);
											  Motor_Stop(Motor1);//move left
											    _delay_ms(1000);//////////////////////////////////////////////////////////////
											  ServoMotor_Rotate(90);//to return to the initial position
											  
										  }
										  else if (distance_front_the_ultra<35)
										 {
											  LCD_Clear();
											  LCD_Write_String("Stop");
											 Motor_Stop(Motor1);
											 Motor_Stop(Motor2);//stop
											 ServoMotor_Rotate(90);//to return to the initial position
											
										 }
			                    } 
			
		   distance_front_the_ultra=0;
		}
	}
	return 0;
}
