#pragma once
#include "EntitasPP/IComponent.hpp"
#include "vec2.h"

struct MovementComponent : public EntitasPP::IComponent {
public:
	vec2f direction;

	void Reset(vec2f dir) {
		direction = dir;
	}
};