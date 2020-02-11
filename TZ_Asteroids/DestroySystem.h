#pragma once
#include "EntitasPP/ISystem.hpp"
#include "EntitasPP/Pool.hpp"

using namespace EntitasPP;

class DestroySystem : public IExecuteSystem, public ISetPoolSystem
{
private:
	Pool* _pool;

public:

	void SetPool(Pool* pool) override;
	void Execute() override;
};
