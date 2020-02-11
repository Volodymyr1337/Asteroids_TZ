#pragma once
#include "Framework.h"
#include "EntitasPP/IComponent.hpp"
#include "vec2.h"

struct ViewComponent : public EntitasPP::IComponent {
public:
	Sprite* sprite;
	vec2f spriteSize;
	int renderOrder;

	void Reset(Sprite* sprite, vec2f sprtSize, int renderOrder) {
		this->sprite = sprite;
		this->spriteSize = sprtSize;
		this->renderOrder = renderOrder;
	}
};