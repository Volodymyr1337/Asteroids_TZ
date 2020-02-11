#include "BoundsWrappingSystem.h"
#include "MovementComponent.h"
#include "BackgroundComponent.h"
#include "PositionComponent.h"
#include "GameConfig.h"
#include "vec2.h"

void BoundsWrappingSystem::SetPool(Pool * pool)
{
	_group = pool->GetGroup(Matcher_AllOf(MovementComponent));
	vec2f screenMidPoint = vec2f(GameConfig::Instance().windowWidth / 2, GameConfig::Instance().windowHeight / 2);
	_maxBounds = vec2f(screenMidPoint.x + GameConfig::Instance().mapWidth/2, screenMidPoint.y + GameConfig::Instance().mapHeight / 2);
	_minBounds = vec2f(screenMidPoint.x - GameConfig::Instance().mapWidth/2, screenMidPoint.y - GameConfig::Instance().mapHeight /2);
}

void BoundsWrappingSystem::Execute()
{
	for (auto &e : _group->GetEntities()) {

		if (e->Has<PositionComponent>() && !e->Has<BackgroundComponent>())
		{
			vec2f currPos = e->Get<PositionComponent>()->position;
			if (currPos.x < _minBounds.x) 
			{
				currPos.x += GameConfig::Instance().mapWidth;
			}
			if (currPos.x > _maxBounds.x)
			{
				currPos.x -= GameConfig::Instance().mapWidth;
			}
			if (currPos.y < _minBounds.y)
			{
				currPos.y += GameConfig::Instance().mapHeight;
			}
			if (currPos.y > _maxBounds.y)
			{
				currPos.y -= GameConfig::Instance().mapHeight;
			}
			e->Replace<PositionComponent>(currPos);
		}
	}
}
