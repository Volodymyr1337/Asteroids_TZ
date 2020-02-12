#pragma once
#include "EntitasPP/ISystem.hpp"
#include "EntitasPP/Pool.hpp"

using namespace EntitasPP;

class CollisionSystem : public IExecuteSystem, public ISetPoolSystem
{
private:
	Pool* _pool;

public:

	void SetPool(Pool* pool) override;
	void Execute() override;
	bool OnCollisionEnter(EntityPtr &entityA, EntityPtr &entityB);
	~CollisionSystem() override;
};

