/*
Motor.h - Library for motor control
Created by MJC; Mikkel, Joakim & Casper
December 2011
*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
	public:
		Motor(int out1, int out2);
		void run(int Speed);
		void runReverse(int Speed);
		void runExt(int Speed);
		void fullStop();
	private:
		int _out1, _out2;
		int Speed;
};

class Encoder
{
	public:
		Encoder(int in1, int in2);
		int getRotations(int count);
		float getSpeed(int count1, int count2, int timeDelay);
		float getSpeed2(int count1, int count2, int timeDelay);
	private:
		int _in1, _in2;
		int count;
};

class SensorIR
{
	public:
		SensorIR(int limit);
		int getMean();
		int getCount();
		int getLimit();
		void setLimit(int limit);
		bool phfm(String sensors, int readings);
		bool phfmToggle(String sensors, bool on, int readings);
		bool phfmCount(int sensors, int readings);
		bool phfmMinCount(int sensors, int readings);
	private:
		int _limit;
};

class UltraSonic
{
	public:
		UltraSonic(int dataPin, int triggerPin, int power, bool reverseSignal);
		void turnOn();
		void turnOff();
		int getDistance();
		int getMean(int readings, int delayTime);
		bool phfmSmaller(int dist, int readings);
		bool phfmBigger(int dist, int readings);
	private:
		int _dataPin, _triggerPin, _power;
		bool _reverseSignal;
};

#endif