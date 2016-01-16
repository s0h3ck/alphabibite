/**
 * K3P16 © Copyright 2015
 * Date : 25/11/2015
 *
 * File's name: movements.cpp
 */

#include "movements.h"

void fear()
{
	DIGITALIO_Write(14, 1);
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		MOTOR_SetSpeed(7,-70);
		MOTOR_SetSpeed(8,0);
		DIGITALIO_Write(14, 0);
		THREAD_MSleep(300);
		MOTOR_SetSpeed(8,-75);
		MOTOR_SetSpeed(7,0);
		DIGITALIO_Write(14, 1);
		THREAD_MSleep(300);
	}
	for (i = 0; i < 5; i++)
	{
		MOTOR_SetSpeed(7,70);
		MOTOR_SetSpeed(8,0);
		DIGITALIO_Write(14, 0);
		THREAD_MSleep(300);
		MOTOR_SetSpeed(8,75);
		MOTOR_SetSpeed(7,0);
		DIGITALIO_Write(14, 1);
		THREAD_MSleep(300);
	}
	MOTOR_SetSpeed(7,0);
	MOTOR_SetSpeed(8,0);
	DIGITALIO_Write(14, 0);
}

void angry()
{
	DIGITALIO_Write(14, 0);
	DIGITALIO_Write(15, 1);
	MOTOR_SetSpeed(7,-50);
	MOTOR_SetSpeed(8,-50);
	THREAD_MSleep(3000);
	MOTOR_SetSpeed(7,84);
	MOTOR_SetSpeed(8 ,90);
	THREAD_MSleep(1500);
	MOTOR_SetSpeed(7,0);
	MOTOR_SetSpeed(8,0);
	DIGITALIO_Write(15, 0);
	DIGITALIO_Write(14, 0);
}

void happy()
{
	DIGITALIO_Write(14, 1);
	MOTOR_SetSpeed(7,100);
	THREAD_MSleep(4000);
	MOTOR_SetSpeed(7,-100);
	THREAD_MSleep(4000);
	MOTOR_SetSpeed(7,0);
	DIGITALIO_Write(14, 0);
}

void sad()
{
	DIGITALIO_Write(14, 1);
	MOTOR_SetSpeed(7,100);
	THREAD_MSleep(2500);
	DIGITALIO_Write(14, 0);

	MOTOR_SetSpeed(7,45);
	MOTOR_SetSpeed(8,45);
	THREAD_MSleep(2000);

	MOTOR_SetSpeed(7, -100);
	THREAD_MSleep(1500);
	MOTOR_SetSpeed(7,45);
	MOTOR_SetSpeed(8,45);
	THREAD_MSleep(4000);

	MOTOR_SetSpeed(7,0);
	MOTOR_SetSpeed(8,0);
	DIGITALIO_Write(14, 0);
}

void miam()
{
	int i = 0;
	DIGITALIO_Write(14, 1);
	MOTOR_SetSpeed(7,100);
	THREAD_MSleep(700);
	MOTOR_SetSpeed(7,-100);
	THREAD_MSleep(700);
	MOTOR_SetSpeed(7,0);
	MOTOR_SetSpeed(8,100);
	THREAD_MSleep(700);
	MOTOR_SetSpeed(8,-100);
	THREAD_MSleep(700);
	MOTOR_SetSpeed(7,0);
	MOTOR_SetSpeed(8,0);
	DIGITALIO_Write(14, 1);
}


