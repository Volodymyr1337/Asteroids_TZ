#include "BackgroundWrappingSystem.h"
#include "MovementComponent.h"
#include "BackgroundComponent.h"
#include "PositionComponent.h"
#include "ViewComponent.h"
#include "vec2.h"
#include <iostream>

void BackgroundWrappingSystem::SetPool(Pool * pool)
{
	_group = pool->GetGroup(Matcher_AllOf(MovementComponent));
}

void BackgroundWrappingSystem::Initialize()
{
	auto entity = _group->GetEntities()[0];
	vec2f spriteSize = entity->Get<ViewComponent>()->spriteSize;
	int screenX = 0;
	int screenY = 0;
	getScreenSize(screenX, screenY);
	_backgroundQt = vec2f(screenX / spriteSize.x + 4, screenY / spriteSize.y + 4);
	_bgSize = vec2f(_backgroundQt.x * spriteSize.x, _backgroundQt.y * spriteSize.y);
	_maxBounds = vec2f((_backgroundQt.x - 1) * spriteSize.x, (_backgroundQt.y - 1) * spriteSize.y);
	_minBounds = vec2f(-spriteSize.x*2, -spriteSize.y*2);
}

void BackgroundWrappingSystem::Execute()
{
	for (auto &e : _group->GetEntities())
	{
		if (e->Has<PositionComponent>() && e->Has<BackgroundComponent>())
		{
			vec2f currPos = e->Get<PositionComponent>()->position;
			if (currPos.x < _minBounds.x)
			{
				currPos.x += _bgSize.x;
			}
			if (currPos.x > _maxBounds.x)
			{
				currPos.x -= _bgSize.x;
			}
			if (currPos.y < _minBounds.y)
			{
				currPos.y += _bgSize.y;
			}
			if (currPos.y > _maxBounds.y)
			{
				currPos.y -= _bgSize.y;
			}
			e->Replace<PositionComponent>(currPos);
		}
	}
}
