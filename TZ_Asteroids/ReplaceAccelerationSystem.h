#pragma once
#include "EntitasPP/ISystem.hpp"
#include "EntitasPP/Pool.hpp"

using namespace EntitasPP;

class ReplaceAccelerationSystem : public IExecuteSystem, public ISetPoolSystem
{
private:
	Pool* _pool;
	float _accelerationDampening = 0.9f;

public:

	void SetPool(Pool* pool) override;
	void Execute() override;
};