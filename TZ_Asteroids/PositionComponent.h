#pragma once
#include "Framework.h"
#include "EntitasPP/IComponent.hpp"
#include "vec2.h"

struct PositionComponent : public EntitasPP::IComponent {
public:
	vec2f position;

	void Reset(vec2f pos) {
		position = pos;
	}
};
