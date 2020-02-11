#pragma once
#include "EntitasPP/ISystem.hpp"
#include "vec2.h"

using namespace EntitasPP;

class UserInputSystem : public IInitializeSystem, public IExecuteSystem, public ISetPoolSystem
{
private:
	Pool* _pool;
	vec2f _mousePos;
	std::vector<FRKey> pressedKeys;

public:

	void SetPool(Pool* pool) override;
	void Initialize() override;
	void Execute() override;
};

