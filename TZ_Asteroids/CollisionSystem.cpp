#include "CollisionSystem.h"
#include "PositionComponent.h"
#include "ViewComponent.h"
#include "ResourceComponent.h"
#include "MovementComponent.h"
#include "AsteroidComponent.h"
#include "ProjectileComponent.h"
#include "SpaceShipComponent.h"
#include "AbilityComponent.h"
#include "DestroyComponent.h"
#include "AsteroidFactory.h"
#include <iostream>

void CollisionSystem::SetPool(Pool* pool)
{
	_pool = pool;
}

void CollisionSystem::Execute()
{
	std::vector<EntityPtr> entities = _pool->GetEntities();
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		auto &entityA = entities[i];
		for (unsigned int j = 0; j < entities.size(); j++)
		{
			auto &entityB = entities[j];

			if (entityA->GetUuid() == entityB->GetUuid())
			{
				continue;
			}
			if (entityA->Has<AsteroidComponent>() && entityB->Has<AsteroidComponent>())
			{
				if (entityA->Has<PositionComponent>() && entityB->Has<PositionComponent>())
				{
					if (entityA->Has<ViewComponent>() && entityB->Has<ViewComponent>())
					{
						if (OnCollisionEnter(entityA, entityB))
						{
							vec2f aDirection = entityA->Get<MovementComponent>()->direction;
							vec2f bDirection = entityB->Get<MovementComponent>()->direction;
							entityA->Replace<MovementComponent>(bDirection);
							entityB->Replace<MovementComponent>(aDirection);

							vec2f currPosA = entityA->Get<PositionComponent>()->position;
							vec2f currPosB = entityB->Get<PositionComponent>()->position;
							vec2f asteroidSize = entityB->Get<ViewComponent>()->spriteSize;

							float x = currPosA.x - currPosB.x;
							float y = currPosA.y - currPosB.y;
							if (abs(x) < asteroidSize.x)
							{
								float offsetDtX = asteroidSize.x - abs(x);
								float addOffsetX = offsetDtX / 2.f;
								if (x < 0)
								{
									currPosA.x -= addOffsetX;
									currPosB.x += addOffsetX;
								}
								if (x > 0)
								{
									currPosA.x += addOffsetX;
									currPosB.x -= addOffsetX;
								}
							}
							if (abs(y) < asteroidSize.y)
							{
								float offsetDtY = asteroidSize.y - abs(y);
								float addOffsetY = offsetDtY / 2.f;
								if (y < 0)
								{
									currPosA.y -= addOffsetY;
									currPosB.y += addOffsetY;
								}
								if (y > 0)
								{
									currPosA.y += addOffsetY;
									currPosB.y -= addOffsetY;
								}
							}
							entityA->Replace<PositionComponent>(currPosA);
							entityB->Replace<PositionComponent>(currPosB);
						}
					}
				}
			}

			if (entityA->Has<ProjectileComponent>() && entityB->Has<AsteroidComponent>())
			{
				if (entityA->Has<PositionComponent>() && entityB->Has<PositionComponent>())
				{
					if (entityA->Has<ViewComponent>() && entityB->Has<ViewComponent>())
					{
						if (OnCollisionEnter(entityA, entityB))
						{
							if (entityB->Get<AsteroidComponent>()->level > 1 && !entityB->Has<DestroyComponent>())
							{
								for (unsigned int i = 0; i < 2; i++)
								{
									EntityPtr smallAsteroid = AsteroidFactory::create(_pool, vec2f(0, 0), 1, "Resources/small_asteroid.png");
									vec2f asteroidPos = entityB->Get<PositionComponent>()->position;
									vec2f spriteSize = smallAsteroid->Get<ViewComponent>()->spriteSize;
									vec2f position(asteroidPos.x + spriteSize.x * i, asteroidPos.y + spriteSize.y * i);
									smallAsteroid->Replace<PositionComponent>(position);
								}
							}
							else
							{
								vec2f bonusPosition = entityB->Get<PositionComponent>()->position;
								float bonusChance = ((float)rand() / RAND_MAX);
								if (bonusChance <= GameConfig::Instance().abilityProbability)
								{
									auto entity = _pool->CreateEntity();
									entity->Add<ResourceComponent>("Resources/missile.png");
									Sprite* sprite = createSprite(entity->Get<ResourceComponent>()->path);
									int sprtWidth;
									int sprtHeight;
									getSpriteSize(sprite, sprtWidth, sprtHeight);
									entity->Add<ViewComponent>(sprite, vec2f(sprtWidth, sprtHeight), (int)RENDER_QUEUE::ABILITIES);
									entity->Add<PositionComponent>(bonusPosition);
									entity->Add<MovementComponent>(vec2f(0.f, 0.f));
									entity->Add<AbilityComponent>(ABILITY_TYPE::HOMING_MISSILE);
								}
							}
							if (!entityA->Has<DestroyComponent>())
							{
								entityA->Add<DestroyComponent>();
							}
							if (!entityB->Has<DestroyComponent>())
							{
								entityB->Add<DestroyComponent>();
							}
						}
					}
				}
			}
			if (entityA->Has<SpaceShipComponent>() && entityB->Has<AsteroidComponent>())
			{
				if (entityA->Has<PositionComponent>() && entityB->Has<PositionComponent>())
				{
					if (entityA->Has<ViewComponent>() && entityB->Has<ViewComponent>())
					{

						if (OnCollisionEnter(entityA, entityB))
						{
							entityA->Add<DestroyComponent>();
						}
					}
				}
			}

			if (entityA->Has<SpaceShipComponent>() && entityB->Has<AbilityComponent>())
			{
				if (entityA->Has<PositionComponent>() && entityB->Has<PositionComponent>())
				{
					if (entityA->Has<ViewComponent>() && entityB->Has<ViewComponent>())
					{
						if (OnCollisionEnter(entityA, entityB))
						{
							entityB->Add<DestroyComponent>();
							if (entityA->Has<AbilityComponent>())
							{
								entityA->Replace<AbilityComponent>(entityB->Get<AbilityComponent>()->abilityType);
							}
							else
							{
								entityA->Add<AbilityComponent>(entityB->Get<AbilityComponent>()->abilityType);
							}
						}
					}
				}
			}
		}
	}
}

bool CollisionSystem::OnCollisionEnter(EntityPtr &entityA, EntityPtr &entityB)
{
	vec2f eA_spriteSize = entityA->Get<ViewComponent>()->spriteSize;
	vec2f eA_position = entityA->Get<PositionComponent>()->position;
	float aXr = eA_spriteSize.x / 2.f;
	float aYr = eA_spriteSize.y / 2.f;
	eA_position.x += aXr;
	eA_position.y += aYr;
	vec2f eB_spriteSize = entityB->Get<ViewComponent>()->spriteSize;
	vec2f eB_position = entityB->Get<PositionComponent>()->position;
	float bXr = eB_spriteSize.x / 2.f;
	float bYr = eB_spriteSize.y / 2.f;
	eB_position.x += bXr;
	eB_position.y += bYr;
	float xCompare = (eA_position.x - eB_position.x) * (eA_position.x - eB_position.x);
	float yCompare = (eA_position.y - eB_position.y) * (eA_position.y - eB_position.y);

	return xCompare + yCompare < (aXr + bXr) * (aYr + bYr);
}
