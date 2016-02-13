#ifndef GLOBALCONST_H_
#define GLOBALCONST_H_


enum PWMType{
	SoftwarePWM,
	HardwarePWM
};

struct Axis_Servo{
	int Address;
	float MaxAngleLeft;
	float MaxAngleRight;
	float ZeroAngleOffset;
	bool Inverted;
};


//Servos
const Axis_Servo YawServo = {
	1,		//Pin
	80,
	-80,
	0,
	true
};
const Axis_Servo PitchServo = {
	0,		//Pin
	80,
	-80,
	-11,
	true
};
const Axis_Servo RollServo = {
	2,		//Pin
	70,
	-70,
	-5,
	false
};



#endif /* GLOBALCONST_H_ */
