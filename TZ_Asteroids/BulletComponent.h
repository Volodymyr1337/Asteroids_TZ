#pragma once
#include "EntitasPP/IComponent.hpp"

struct BulletComponent : public EntitasPP::IComponent {
public:
	int id;

	void Reset(int id) {
		this->id = id;
	}
};

