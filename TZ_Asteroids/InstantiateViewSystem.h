#pragma once
#include "EntitasPP/ISystem.hpp"
#include "EntitasPP/Pool.hpp"

using namespace EntitasPP;

class InstantiateViewSystem : public IInitializeSystem, public ISetPoolSystem
{

private:
	std::shared_ptr<Group> _group;

public:
	void SetPool(Pool* pool) override;
	void Initialize() override;
};
