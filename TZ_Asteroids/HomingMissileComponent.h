#pragma once
#include "EntitasPP/IComponent.hpp"
#include "EntitasPP/Pool.hpp"

struct HomingMissileComponent : public EntitasPP::IComponent {
public:
	EntitasPP::EntityPtr target;

	void Reset(EntitasPP::EntityPtr target) {
		this->target = target;
	}
};