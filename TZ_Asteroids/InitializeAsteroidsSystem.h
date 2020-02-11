#pragma once
#include "EntitasPP/ISystem.hpp"

using namespace EntitasPP;

class InitializeAsteroidsSystem : public IInitializeSystem, public ISetPoolSystem
{
private:
	Pool* _pool;
	const float _minVelocity = 40;
	const float _maxVelocity = 60;

	int _screenX;
	int _screenY;

public:
	void SetPool(Pool* pool) override;
	void Initialize() override;
};
