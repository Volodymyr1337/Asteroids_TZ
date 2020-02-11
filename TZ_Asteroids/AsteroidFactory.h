#pragma once
#include "EntitasPP/ISystem.hpp"
#include "EntitasPP/Pool.hpp"
#include "PositionComponent.h"
#include "ResourceComponent.h"
#include "MovementComponent.h"
#include "AsteroidComponent.h"
#include "ViewComponent.h"
#include "GameConfig.h"
#include "vec2.h"

class AsteroidFactory {
public:
	static EntityPtr create(EntitasPP::Pool* pool, vec2f position, int level, const char* resourceName)
	{
		const float PI = 3.14159265f;

		auto smallAsteroid = pool->CreateEntity();
		smallAsteroid->Add<ResourceComponent>(resourceName);
		Sprite* sprite = createSprite(smallAsteroid->Get<ResourceComponent>()->path);
		int sizeX;
		int sizeY;
		getSpriteSize(sprite, sizeX, sizeY);
		vec2f spriteSize(sizeX, sizeY);
		float velocity = (GameConfig::Instance().asteroidSpeed.y - GameConfig::Instance().asteroidSpeed.x) * ((float)rand() / RAND_MAX) + GameConfig::Instance().asteroidSpeed.x;
		float angle = 2 * PI * ((float)rand() / (RAND_MAX + 1));

		vec2f movementDirection = vec2f(cos(angle), sin(angle)) * velocity;

		smallAsteroid->Add<PositionComponent>(position);
		smallAsteroid->Add<MovementComponent>(movementDirection);
		smallAsteroid->Add<AsteroidComponent>(level);
		smallAsteroid->Add<ViewComponent>(sprite, spriteSize, (int)RENDER_QUEUE::ASTEROID);
		
		return smallAsteroid;
	}
};
