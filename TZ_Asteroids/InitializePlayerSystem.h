#pragma once
#include "EntitasPP/ISystem.hpp"

using namespace EntitasPP;

class InitializePlayerSystem : public IInitializeSystem, public ISetPoolSystem
{

private:
	Pool* _pool;

	int _screenX;
	int _screenY;

public:
	void SetPool(Pool* pool) override;
	void Initialize() override;

};

