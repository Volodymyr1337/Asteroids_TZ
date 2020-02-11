#pragma once
#include "EntitasPP/ISystem.hpp"
#include "EntitasPP/Pool.hpp"
#include "vec2.h"

using namespace EntitasPP;

class BoundsWrappingSystem : public IExecuteSystem, public ISetPoolSystem
{
private:
	std::shared_ptr<Group> _group;
	vec2f _maxBounds;
	vec2f _minBounds;

public:

	void SetPool(Pool* pool) override;
	void Execute() override;
};

