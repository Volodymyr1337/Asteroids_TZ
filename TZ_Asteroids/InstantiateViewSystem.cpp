#include "InstantiateViewSystem.h"
#include "EntitasPP/Pool.hpp"
#include "ResourceComponent.h"
#include "ViewComponent.h"
#include "GameConfig.h"
#include "PositionComponent.h"
#include "SpaceShipComponent.h"
#include "AsteroidComponent.h"
#include "AimComponent.h"
#include "Framework.h"
#include <iostream>

void InstantiateViewSystem::SetPool(Pool* pool)
{
	_group = pool->GetGroup(Matcher_AllOf(ResourceComponent));
}

void InstantiateViewSystem::Initialize()
{
	for (auto &e : _group->GetEntities()) 
	{
		if (e->Has<ViewComponent>()) continue;

		Sprite* sprite = createSprite(e->Get<ResourceComponent>()->path);
		int sizeX;
		int sizeY;
		getSpriteSize(sprite, sizeX, sizeY);
		vec2f spriteSize(sizeX, sizeY);

		int order = 0;
		if (e->Has<SpaceShipComponent>())
		{
			order = (int)RENDER_QUEUE::SPACESHIP;
		}
		else if (e->Has<AsteroidComponent>())
		{
			order = (int)RENDER_QUEUE::ASTEROID;
		}
		else if (e->Has<AimComponent>())
		{
			order = (int)RENDER_QUEUE::AIM;
		}

		e->Add<ViewComponent>(sprite, spriteSize, order);
		
		if (e->Has<PositionComponent>())	// center alignment
		{
			vec2f currPos = e->Get<PositionComponent>()->position;			
			currPos.x -= sizeX / 2.f;
			currPos.y -= sizeY / 2.f;
			e->Replace<PositionComponent>(currPos);
		}
		
	}
}
