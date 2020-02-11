#pragma once
#include "EntitasPP/IComponent.hpp"
#include "vec2.h"

struct AccelerationComponent : public EntitasPP::IComponent
{
public:
	vec2f acceleration;

	void Reset(vec2f acceleration) {
		this->acceleration = acceleration;
	}
};
