#pragma once
#include "Framework.h"
#include "GameConfig.h"
#include "EntitasPP/IComponent.hpp"

struct AbilityComponent : public EntitasPP::IComponent {
public:
	ABILITY_TYPE abilityType;

	void Reset(ABILITY_TYPE abilityType) {
		this->abilityType = abilityType;
	}
};