/*
 * teleVRServoControl.h
 *
 *  Created on: 23.11.2015
 *      Author: kalle
 */

#ifndef TELEVRSERVOCONTROL_H_
#define TELEVRSERVOCONTROL_H_
#include "GlobalConst.h"
class teleVR_ServoControl {
public:


	teleVR_ServoControl();
	virtual ~teleVR_ServoControl();

	bool init_PWM();
	bool setOrientation(float Roll, float Pitch, float Yaw);
	bool writePWM(float Angle, Axis_Servo AxisServo);
	/**
	 * Calculate the number of ticks the signal should be high for the required amount of time
	 */
	int calcTicks(float impulseMs, int hertz);

	/**
	 * input is [0..1]
	 * output is [min..max]
	 */
	float map(float input, float min, float max);

private:

	int fd;
};

#endif /* TELEVRSERVOCONTROL_H_ */
