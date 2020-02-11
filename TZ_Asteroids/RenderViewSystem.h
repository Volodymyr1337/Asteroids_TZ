#pragma once

#include "EntitasPP/ISystem.hpp"
#include "EntitasPP/Pool.hpp"

using namespace EntitasPP;

class RenderViewSystem : public IExecuteSystem, public ISetPoolSystem
{
private:
	std::shared_ptr<Group> _group;

public:

	void SetPool(Pool* pool) override;
	void Execute() override;
};

