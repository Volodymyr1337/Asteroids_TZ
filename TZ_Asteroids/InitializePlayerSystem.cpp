#include "InitializePlayerSystem.h"
#include "EntitasPP/Pool.hpp"
#include "ResourceComponent.h"
#include "PositionComponent.h"
#include "SpaceShipComponent.h"
#include "vec2.h"

void InitializePlayerSystem::SetPool(Pool* pool)
{
	_pool = pool;
	getScreenSize(_screenX, _screenY);
}

void InitializePlayerSystem::Initialize()
{
	auto e = _pool->CreateEntity();
	e->Add<ResourceComponent>("Resources/spaceship.png");
	e->Add<PositionComponent>(vec2f(_screenX/2.f, _screenY/2.f));
	e->Add<SpaceShipComponent>();
}
