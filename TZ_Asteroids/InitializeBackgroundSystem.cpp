#include "InitializeBackgroundSystem.h"
#include "ResourceComponent.h"
#include "PositionComponent.h"
#include "BackgroundComponent.h"
#include "ViewComponent.h"
#include "GameConfig.h"
#include "MovementComponent.h"
#include "EntitasPP/Pool.hpp"
#include <iostream>

void InitializeBackgroundSystem::SetPool(Pool * pool)
{
	_pool = pool;
}

void InitializeBackgroundSystem::Initialize()
{
	Sprite* sprt = createSprite("Resources/background.png");
	int sizeX;
	int sizeY;
	int screenX;
	int screenY;
	getScreenSize(screenX, screenY);
	getSpriteSize(sprt, sizeX, sizeY);
	int asteroidsQtX = screenX / sizeX + 4;
	int asteroidsQtY = screenY / sizeY + 4;

	for (int y = -2; y < asteroidsQtY; y++)
	{
		for (int x = -2; x < asteroidsQtX; x++)
		{
			auto entity = _pool->CreateEntity();
			entity->Add<ResourceComponent>("Resources/background.png");

			Sprite* sprite = createSprite(entity->Get<ResourceComponent>()->path);
			int sizeX;
			int sizeY;
			getSpriteSize(sprite, sizeX, sizeY);
			vec2f spriteSize(sizeX, sizeY);
			vec2f position;
			position.x = x * sizeX;
			position.y = y * sizeY;
			
			entity->Add<BackgroundComponent>();
			entity->Add<PositionComponent>(position);
			entity->Add<MovementComponent>(vec2f(0, 0));
			entity->Add<ViewComponent>(sprite, spriteSize, (int)RENDER_QUEUE::BACKGROUND);
		}
	}
}
