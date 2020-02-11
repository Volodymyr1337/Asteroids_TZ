#pragma once
#include "EntitasPP/IComponent.hpp"

struct AsteroidComponent : public EntitasPP::IComponent {
public:
	int level;

	void Reset(int level) {
		this->level = level;
	}
};
