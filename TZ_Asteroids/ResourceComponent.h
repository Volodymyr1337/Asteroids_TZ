#pragma once
#include "EntitasPP/IComponent.hpp"

struct ResourceComponent : public EntitasPP::IComponent {
public:
	const char* path;

	void Reset(const char* path) {
		this->path = path;
	}
};