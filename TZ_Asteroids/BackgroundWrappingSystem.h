#pragma once
#include "EntitasPP/ISystem.hpp"
#include "EntitasPP/Pool.hpp"
#include "vec2.h"

using namespace EntitasPP;

class BackgroundWrappingSystem : public IInitializeSystem, public IExecuteSystem, public ISetPoolSystem
{
private:
	std::shared_ptr<Group> _group;
	vec2f _maxBounds;
	vec2f _minBounds;
	vec2f _backgroundQt;
	vec2f _bgSize;


public:

	void SetPool(Pool* pool) override;
	void Initialize() override;
	void Execute() override;
};

