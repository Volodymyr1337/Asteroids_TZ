#include "Time.h"


void Time::Update()
{
	_prev = _curr;
	_curr = getTickCount();
	deltaTime = _curr - _prev;
	deltaTime /= 1000.0f;
}
