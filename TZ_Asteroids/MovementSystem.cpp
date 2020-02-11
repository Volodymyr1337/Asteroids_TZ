#include "MovementSystem.h"
#include "MovementComponent.h"
#include "PositionComponent.h"
#include "ViewComponent.h"
#include "AsteroidComponent.h"
#include "AccelerationComponent.h"
#include "vec2.h"
#include <iostream>

void MovementSystem::SetPool(Pool * pool)
{
	_group = pool->GetGroup(Matcher_AllOf(MovementComponent));
}

void MovementSystem::Execute()
{
	for (auto &e : _group->GetEntities())
	{
		if (e->Has<PositionComponent>())
		{
			vec2f currPos = e->Get<PositionComponent>()->position;
			MovementComponent* movementComponent = e->Get<MovementComponent>();
			vec2f newPos = movementComponent->direction * Time::Instance().deltaTime;
			currPos += newPos;
			if (e->Has<AccelerationComponent>())
			{
				currPos += e->Get<AccelerationComponent>()->acceleration;
			}
			e->Replace<PositionComponent>(currPos);
		}
	}
}
