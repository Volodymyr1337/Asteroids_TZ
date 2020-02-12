#include "InitializeAsteroidsSystem.h"
#include "EntitasPP/Pool.hpp"
#include "ResourceComponent.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "AsteroidComponent.h"
#include "SpaceShipComponent.h"
#include "GameConfig.h"
#include "AsteroidFactory.h"
#include "Dispatcher.h"
#include <iostream>

void InitializeAsteroidsSystem::SetPool(Pool* pool)
{
	_pool = pool;
	getScreenSize(_screenX, _screenY);
}

void InitializeAsteroidsSystem::Initialize()
{

	vec2f spaceShipPos;
	for (auto &spaceShip : _pool->GetEntities())
	{
		if (spaceShip->Has<SpaceShipComponent>())
		{
			spaceShipPos = spaceShip->Get<PositionComponent>()->position;
			break;
		}
	}

	for (unsigned int i = 0; i < GameConfig::Instance().numAsteroids; i++)
	{
		SpawnAsteroid(spaceShipPos);
	}

	Dispatcher::Instance().onAsteroidDestroyed = nullptr;
	Dispatcher::Instance().onAsteroidDestroyed += [&](int numAsteroids) {
		if (GameConfig::Instance().numAsteroids > numAsteroids)
		{
			SpawnAsteroid(spaceShipPos);
		}		
	};
}

void InitializeAsteroidsSystem::SpawnAsteroid(vec2f spaceShipPos)
{
	float x = _screenX * ((float)rand() / RAND_MAX);
	float y = _screenY * ((float)rand() / RAND_MAX);
	vec2f position(x, y);
	float distance = position.dist(spaceShipPos);

	if (distance < 100)
	{
		vec2f newPos = (position - spaceShipPos).normalize() * 100;
		position += newPos;
	}
	AsteroidFactory::create(_pool, position, 2, "Resources/big_asteroid.png");
}
