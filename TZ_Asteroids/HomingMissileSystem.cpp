#include "HomingMissileSystem.h"
#include "HomingMissileComponent.h"
#include "MovementComponent.h"
#include "PositionComponent.h"
#include "GameConfig.h"

void HomingMissileSystem::SetPool(Pool* pool)
{
	_pool = pool;
}

void HomingMissileSystem::Execute()
{
	auto missiles = _pool->GetGroup(Matcher_AllOf(HomingMissileComponent))->GetEntities();
	if (missiles.size() > 0)
	{
		for (auto &missile : missiles)
		{
			auto target = missile->Get<HomingMissileComponent>()->target;
			if (target != nullptr && target->Has<PositionComponent>())
			{
				auto missilePos = missile->Get<PositionComponent>()->position;
				auto targetPos = target->Get<PositionComponent>()->position;
				auto movementDirection = (targetPos - missilePos).normalize() * GameConfig::Instance().homingMissileSpeed;
				missile->Replace<MovementComponent>(movementDirection);
			}
		}
	}
}

HomingMissileSystem::~HomingMissileSystem()
{
	delete _pool;
}
