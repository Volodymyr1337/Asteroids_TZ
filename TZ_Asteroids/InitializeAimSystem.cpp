#include "InitializeAimSystem.h"
#include "ResourceComponent.h"
#include "PositionComponent.h"
#include "AimComponent.h"
#include "EntitasPP/Pool.hpp"

void InitializeAimSystem::SetPool(Pool * pool)
{
	_pool = pool;
}

void InitializeAimSystem::Initialize()
{
	auto entity = _pool->CreateEntity();
	entity->Add<ResourceComponent>("Resources/circle.tga");
	entity->Add<PositionComponent>(vec2f(0, 0));
	entity->Add<AimComponent>();
}
