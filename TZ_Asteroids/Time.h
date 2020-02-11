#pragma once
#include "Framework.h"

class Time
{
public:
	static Time& Instance()
	{
		static Time _instance;
		return _instance;
	}

	float deltaTime;
	void Update();

private:
	Time() {};
	~Time() {};

	Time(Time const&) = delete;
	Time& operator= (Time const&) = delete;

	float _prev;
	float _curr;
};

