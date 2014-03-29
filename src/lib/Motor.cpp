/*
Motor.h - Library for motor control
Created by MJC; Mikkel, Joakim & Casper
December 2011
*/

//#include "Arduino.h"
#include "Motor.h"

const int ENCODER_PULSE	= 16;
const int GEAR_RATIO = 19;
const float CIRCUMFERENCE = 22.9415; //cm

//MOTOR
Motor::Motor(int out1, int out2)
{
	pinMode(out1, OUTPUT);
	pinMode(out2, OUTPUT);
	_out1 = out1;
	_out2 = out2;
}
void Motor::run(int Speed)
{
	if (Speed < 0){Speed = 0;}
	if (Speed > 100){Speed = 100;}
	Speed = map(Speed, 0, 100, 0, 255);
	analogWrite(_out1, Speed);
	digitalWrite(_out2, LOW);
}
void Motor::runReverse(int Speed)
{
	if (Speed < 0){Speed = 0;}
	if (Speed > 100){Speed = 100;}
	Speed = map(Speed, 0, 100, 0, 255);
	digitalWrite(_out1, LOW);
	analogWrite(_out2, Speed);
}
void Motor::runExt(int Speed)
{
	if (Speed < -100){Speed = -100;}
	if (Speed > 100){Speed = 100;}
	
	if (Speed < 0){
		Speed = map(-1*Speed, 0, 100, 0, 255);
		runReverse(Speed);
	} else {
		Speed = map(Speed, 0, 100, 0, 255);
		run(Speed);
	}
}
void Motor::fullStop(){
	digitalWrite(_out1, HIGH);
	digitalWrite(_out2, HIGH);
}

//ENCODER
Encoder::Encoder(int in1, int in2)
{
	pinMode(in1, INPUT);
	pinMode(in2, INPUT);
	_in1 = in1;
	_in2 = in2;
}
int Encoder::getRotations(int count)
{
	return int(float(count)/float(ENCODER_PULSE*GEAR_RATIO));
}
float Encoder::getSpeed(int count1, int count2, int timeDelay)
{
	// timeDelay between count1 and count2 in milliseconds

	//Get rotations from counts
	int rotations1 = getRotations(count1);
	int rotations2 = getRotations(count2);
	
	// Rotations per milliseconds
	float rot_ms = float(rotations2-rotations1) /  timeDelay;
	// Speed in cm/ms
	float speed = rot_ms*CIRCUMFERENCE;
	// Convert speed to m/s  | ms --> s = *1000 ; cm --> m = /100
	return 1000*speed/100;
}
float Encoder::getSpeed2(int count1, int count2, int timeDelay)
{
	// timeDelay between count1 and count2 in milliseconds
	
	// Rotations per milliseconds
	float rot_ms = float((count2-count1) / float(ENCODER_PULSE*GEAR_RATIO)) /  timeDelay;
	// Speed in cm/ms
	float speed = rot_ms*CIRCUMFERENCE;
	// Convert speed to m/s  | ms --> s = *1000 ; cm --> m = /100
	return 1000*speed/100;
}


UltraSonic::UltraSonic(int dataPin, int triggerPin, int power, bool reverseSignal)
{
	_dataPin = dataPin;
	_triggerPin = triggerPin;
	_power = power;
	_reverseSignal = reverseSignal;
	
	pinMode(_power, OUTPUT);
	digitalWrite(_power, HIGH);
}
void UltraSonic::turnOn()
{
	digitalWrite(_power, HIGH);
	delay(200);
}
void UltraSonic::turnOff()
{
	digitalWrite(_power, LOW);
}
int UltraSonic::getDistance()
{
	//Set triggerPin to OUTPUT mode
	pinMode(_triggerPin, OUTPUT);
	
	//Send low-high-low pulses
	if (_reverseSignal == true){
		digitalWrite(_triggerPin, LOW);
		delayMicroseconds(2);
		digitalWrite(_triggerPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(_triggerPin, LOW);
		delayMicroseconds(2);
	} else {
		digitalWrite(_triggerPin, HIGH);
		delayMicroseconds(500);
		digitalWrite(_triggerPin, LOW);
		delayMicroseconds(200);
		digitalWrite(_triggerPin, HIGH);
		delayMicroseconds(200);
	}
	
	//Listening for echo pulse
	pinMode(_dataPin, INPUT);
	bool val;
	
	//Wait, until a high value is read
	if (_reverseSignal == true){
		do {
			val = digitalRead(_dataPin);
		} while (val == LOW);
	} else {
		do {
			val = digitalRead(_dataPin);
		} while (val == HIGH);
	}
	
	int timeCount = 0;
	//Count, until low value is read again
	if (_reverseSignal == true){
		do {
			val = digitalRead(_dataPin);
			timeCount ++;
			delayMicroseconds(50);
		} while (val == HIGH);
	} else {
		do {
			val = digitalRead(_dataPin);
			timeCount ++;
			delayMicroseconds(50);
		} while (val == LOW);
	}
	
	//Return values (if value less than 300 cm, it is acceptable)
	if (timeCount >= 0 && timeCount < 300){
		return timeCount;
	}
	//Otherwise, we return -1
	else {
		return -1;
	}
}
int UltraSonic::getMean(int readings, int delayTime)
{
	int sum = 0;
	
	for (int i=0; i<readings; i++){
		sum += getDistance();
		delay(delayTime);
	}
	
	return sum/readings;
}
bool UltraSonic::phfmSmaller(int dist, int readings)
{
	return false;
}
bool UltraSonic::phfmBigger(int dist, int readings)
{
	return false;
}