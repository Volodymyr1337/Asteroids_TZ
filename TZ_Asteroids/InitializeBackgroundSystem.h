#pragma once
#include "EntitasPP/ISystem.hpp"

using namespace EntitasPP;

class InitializeBackgroundSystem : public IInitializeSystem, public ISetPoolSystem
{
private:
	Pool* _pool;

public:
	void SetPool(Pool* pool) override;
	void Initialize() override;
};
