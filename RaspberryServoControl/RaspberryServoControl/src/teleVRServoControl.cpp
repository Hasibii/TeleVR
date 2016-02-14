/*
 * teleVRServoControl.cpp
 *
 *  Created on: 23.11.2015
 *      Author: kalle
 */

#include "teleVRServoControl.h"
#include <pca9685.h>
#include <iostream>
#include <wiringPi.h>c
#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

using namespace std;

teleVR_ServoControl::teleVR_ServoControl() {
	fd = -1;
}

teleVR_ServoControl::~teleVR_ServoControl() {
	pca9685PWMReset(fd);
}

void teleVR_ServoControl::resetPWM(){
	pca9685PWMReset(fd);
}

bool teleVR_ServoControl::init_PWM(){
	// Setup with pinbase 300 and i2c location 0x40
		fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
		if (fd < 0)
		{
			cout << ("Error in setup\n");
			return false;
		}

		// Reset all output
		pca9685PWMReset(fd);

	return true;
}

/**
 * Calculate the number of ticks the signal should be high for the required amount of time
 */
int teleVR_ServoControl::calcTicks(float impulseMs, int hertz)
{
	float cycleMs = 1000.0f / hertz;
	return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

/**
 * input is [0..1]
 * output is [min..max]
 */
float teleVR_ServoControl::map(float input, float min, float max)
{
	return (input * max) + (1 - input) * min;
}


bool teleVR_ServoControl::setOrientation(float Roll, float Pitch, float Yaw){

	writePWM(Roll,RollServo);
	writePWM(Pitch,PitchServo);
	writePWM(Yaw,YawServo);

	return true;
}

bool teleVR_ServoControl::writePWM(float Angle, Axis_Servo AxisServo){

	if(AxisServo.Inverted)
		Angle = Angle * (-1);

	float pwmValue = -1;
	Angle = Angle + AxisServo.ZeroAngleOffset;


	if(Angle > 0){
		if (Angle <= AxisServo.MaxAngleLeft){
			pwmValue = (1.00 + (90.00 - Angle)* (1.00/180.00));
		}
		else
			pwmValue = (1.00 + (90.00 - AxisServo.MaxAngleLeft)* (1.00/180.00));
		}
		else if(Angle <= 0){
			if(Angle >= AxisServo.MaxAngleRight){
				pwmValue = (1.00 + (90.00 - Angle)* (1.00/180.00));
			}
			else
				pwmValue = (1.00 + (90.00 - AxisServo.MaxAngleRight)* (1.00/180.00));
		}
	cout << "HardPWM Wrote " << pwmValue << " to Pin " << AxisServo.Address  << " for Angle: " << Angle << endl;
	if(pwmValue != -1){
		pwmWrite(PIN_BASE + AxisServo.Address, calcTicks(pwmValue, HERTZ));
	}


	return true;
}
