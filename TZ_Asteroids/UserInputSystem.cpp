#include "UserInputSystem.h"
#include "EntitasPP/Pool.hpp"
#include "SpaceShipComponent.h"
#include "PositionComponent.h"
#include "ViewComponent.h"
#include "GameConfig.h"
#include "ProjectileComponent.h"
#include "BulletComponent.h"
#include "AimComponent.h"
#include "MovementComponent.h"
#include "ResourceComponent.h"
#include "AsteroidComponent.h"
#include "AccelerationComponent.h"
#include "HomingMissileComponent.h"
#include "AbilityComponent.h"
#include "Dispatcher.h"
#include <iostream>

void UserInputSystem::SetPool(Pool * pool)
{
	_pool = pool;
}

void UserInputSystem::Initialize()
{
	showCursor(false);
	Dispatcher::Instance().onMouseButtonClick = nullptr;
	Dispatcher::Instance().onMouseButtonClick += [&](FRMouseButton&& button, bool&& isReleased) {
		
		if (!isReleased && FRMouseButton::LEFT == button) {
			vec2f spaceShipPos;
			for (auto &spaceShip : _pool->GetEntities())
			{
				if (spaceShip->Has<SpaceShipComponent>())
				{
					spaceShipPos = spaceShip->Get<PositionComponent>()->position;
					vec2f shipSize = spaceShip->Get<ViewComponent>()->spriteSize;
					spaceShipPos.x += shipSize.x / 2.f;
					spaceShipPos.y += shipSize.y / 2.f;
					break;
				}
			}

			float velocity = GameConfig::Instance().bulletSpeed;
			vec2f bulletDirection = (spaceShipPos - _mousePos).normalize() * -velocity;

			auto group = _pool->GetGroup(Matcher_AllOf(BulletComponent));
			int projectileQuantity = group->GetEntities().size();
			if (projectileQuantity >= GameConfig::Instance().numAmmo)
			{
				for (auto &e : group->GetEntities())
				{
					int id = e->Get<BulletComponent>()->id;
					id--;
					if (id <= 0)
					{
						e->Replace<BulletComponent>(GameConfig::Instance().numAmmo);
						e->Replace<PositionComponent>(spaceShipPos);
						e->Replace<MovementComponent>(bulletDirection);
					}
					else
					{
						e->Replace<BulletComponent>(id);
					}
				}
			}
			else
			{
				int projectileId = ++projectileQuantity;
				auto entity = _pool->CreateEntity();
				entity->Add<ResourceComponent>("Resources/bullet.png");
				entity->Add<PositionComponent>(spaceShipPos);
				entity->Add<MovementComponent>(bulletDirection);
				entity->Add<BulletComponent>(projectileId);
				entity->Add<ProjectileComponent>();
				Sprite* sprite = createSprite(entity->Get<ResourceComponent>()->path);
				int sizeX;
				int sizeY;
				getSpriteSize(sprite, sizeX, sizeY);
				vec2f spriteSize(sizeX, sizeY);
				entity->Add<ViewComponent>(sprite, spriteSize, (int)RENDER_QUEUE::PROJECTILE);
			}
		}
		if (isReleased && FRMouseButton::RIGHT == button)
		{
			auto spaceShip = _pool->GetGroup(Matcher_AllOf(SpaceShipComponent))->GetSingleEntity();
			if (spaceShip->Has<AbilityComponent>() && spaceShip->Get<AbilityComponent>()->abilityType == ABILITY_TYPE::HOMING_MISSILE)
			{
				auto asteroids = _pool->GetGroup(Matcher_AllOf(AsteroidComponent))->GetEntities();
				for (auto &asteroid : asteroids)
				{
					vec2f asteroidPos = asteroid->Get<PositionComponent>()->position;
					vec2f size = asteroid->Get<ViewComponent>()->spriteSize;
					vec2f minBounds = vec2f(0, 0);
					vec2f maxBounds = vec2f(size.x, size.y);
					minBounds += asteroidPos;
					maxBounds += asteroidPos;
					if (_mousePos.x > minBounds.x && _mousePos.x < maxBounds.x && _mousePos.y > minBounds.y && _mousePos.y < maxBounds.y)
					{
						auto missile = _pool->CreateEntity();
						missile->Add<HomingMissileComponent>(asteroid);
						missile->Add<ResourceComponent>("Resources/enemy.png");
						Sprite* sprite = createSprite(missile->Get<ResourceComponent>()->path);
						int sprtWidth;
						int sprtHeight;
						getSpriteSize(sprite, sprtWidth, sprtHeight);
						missile->Add<ViewComponent>(sprite, vec2f(sprtWidth, sprtHeight), (int)RENDER_QUEUE::PROJECTILE);
						vec2f shipPos = spaceShip->Get<PositionComponent>()->position;
						missile->Add<PositionComponent>(shipPos);
						vec2f missileDirection = (asteroidPos - shipPos).normalize() * GameConfig::Instance().homingMissileSpeed;
						missile->Add<MovementComponent>(missileDirection);
						missile->Add<ProjectileComponent>();
						break;
					}
				}
			}
			
		}
	};

	Dispatcher::Instance().onMouseMove = nullptr;
	Dispatcher::Instance().onMouseMove += [&](vec2f&& mousePos) {
		_mousePos = mousePos;

		auto aim = _pool->GetGroup(Matcher_AllOf(AimComponent))->GetSingleEntity();
		vec2f sprtSize = aim->Get<ViewComponent>()->spriteSize;
		vec2f currPos(mousePos);
		currPos.x -= sprtSize.x / 2.f;
		currPos.y -= sprtSize.y / 2.f;
		aim->Replace<PositionComponent>(currPos);
	};

	Dispatcher::Instance().onKeyPressed = nullptr;
	Dispatcher::Instance().onKeyPressed += [&](FRKey&& k) {
		pressedKeys.push_back(k);
	};

	Dispatcher::Instance().onKeyReleased = nullptr;
	Dispatcher::Instance().onKeyReleased += [&](FRKey&& k) {

		std::vector<FRKey>::iterator it = pressedKeys.begin();
		while (it != pressedKeys.end())
		{
			if (*it == k)
			{
				it = pressedKeys.erase(it);
			}
			else
				it++;
		}
	};
}

void UserInputSystem::Execute()
{
	if (pressedKeys.size() == 0)
		return;

	for (auto &spaceShip : _pool->GetEntities())
	{
		for (auto &k : pressedKeys)
		{
			if (!spaceShip->Has<SpaceShipComponent>())
			{
				vec2f acceleration(0, 0);
				if (FRKey::UP == k)
				{
					acceleration.y = GameConfig::Instance().spaceshipAcceleration;
				}
				if (FRKey::DOWN == k)
				{
					acceleration.y = -GameConfig::Instance().spaceshipAcceleration;
				}
				if (FRKey::LEFT == k)
				{
					acceleration.x = GameConfig::Instance().spaceshipAcceleration;
				}
				if (FRKey::RIGHT == k)
				{
					acceleration.x = -GameConfig::Instance().spaceshipAcceleration;
				}
				if (spaceShip->Has<AccelerationComponent>())
				{
					vec2f newAcceleration = spaceShip->Get<AccelerationComponent>()->acceleration;
					newAcceleration.x = acceleration.x != 0 ? acceleration.x : newAcceleration.x;
					newAcceleration.y = acceleration.y != 0 ? acceleration.y : newAcceleration.y;
					spaceShip->Replace<AccelerationComponent>(newAcceleration);
				}
				else
				{
					spaceShip->Add<AccelerationComponent>(acceleration);
				}
			}
		}
	}
}

UserInputSystem::~UserInputSystem()
{
	delete _pool;
}
