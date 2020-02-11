// Asteroids.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
#include "Framework.h"
#include "EntitasPP/IComponent.hpp"
#include "EntitasPP/Pool.hpp"
#include "ViewComponent.h"
#include "ResourceComponent.h"
#include "InitializePlayerSystem.h"
#include "InitializeAimSystem.h"
#include "InitializeAsteroidsSystem.h"
#include "InitializeBackgroundSystem.h"
#include "RenderViewSystem.h"
#include "MovementSystem.h"
#include "InstantiateViewSystem.h"
#include "UserInputSystem.h"
#include "BoundsWrappingSystem.h"
#include "BackgroundWrappingSystem.h"
#include "ReplaceAccelerationSystem.h"
#include "HomingMissileSystem.h"
#include "CollisionSystem.h"
#include "DestroySystem.h"
#include "SpaceShipComponent.h"
#include "AccelerationComponent.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "AsteroidComponent.h"
#include "AimComponent.h"
#include "EntitasPP/SystemContainer.hpp"
#include "GameConfig.h"
#include "Dispatcher.h"
#include "vec2.h"

using namespace EntitasPP;
using namespace std;

class MyFramework : public Framework {

private:

	Pool* _pool;
	shared_ptr<SystemContainer> _systemContainer;
	vector<std::shared_ptr<ISystem>> _systems;

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = GameConfig::Instance().windowWidth;
		height = GameConfig::Instance().windowHeight;
		fullscreen = false;
	}

	virtual bool Init()
	{
		_pool = new Pool();
		_systemContainer = make_shared<SystemContainer>();

		auto usrInptSystem		= _pool->CreateSystem<UserInputSystem>();
		auto playerSystem		= _pool->CreateSystem<InitializePlayerSystem>();
		auto asteroidsSystem	= _pool->CreateSystem<InitializeAsteroidsSystem>();
		auto aimSystem			= _pool->CreateSystem<InitializeAimSystem>();
		auto initBgSystem		= _pool->CreateSystem<InitializeBackgroundSystem>();
		auto instViewSystem		= _pool->CreateSystem<InstantiateViewSystem>();
		auto movementSystem		= _pool->CreateSystem<MovementSystem>();
		auto boundsWrapSystem	= _pool->CreateSystem<BoundsWrappingSystem>();
		auto bgWrappingSystem	= _pool->CreateSystem<BackgroundWrappingSystem>();
		auto collisionSystem	= _pool->CreateSystem<CollisionSystem>();
		auto replAccSystem		= _pool->CreateSystem<ReplaceAccelerationSystem>();
		auto hmMissileSystem	= _pool->CreateSystem<HomingMissileSystem>();
		auto destroySystem		= _pool->CreateSystem<DestroySystem>();
		auto renderViewSystem	= _pool->CreateSystem<RenderViewSystem>();

		_systems.push_back(usrInptSystem);
		_systems.push_back(playerSystem);
		_systems.push_back(asteroidsSystem);
		_systems.push_back(aimSystem);
		_systems.push_back(initBgSystem);
		_systems.push_back(instViewSystem);
		_systems.push_back(renderViewSystem);
		_systems.push_back(movementSystem);
		_systems.push_back(boundsWrapSystem);
		_systems.push_back(bgWrappingSystem);
		_systems.push_back(collisionSystem);
		_systems.push_back(replAccSystem);
		_systems.push_back(hmMissileSystem);
		_systems.push_back(destroySystem);

		for (auto system : _systems)
		{
			_systemContainer->Add(system);
		}

		_systemContainer->Initialize();
		
		return true;
	}

	virtual void Close() { }

	virtual bool Tick() {
		Time::Instance().Update();
		drawTestBackground();
		//
		// TODO RESTART system
		//
		if (_pool->GetGroup(Matcher_AllOf(SpaceShipComponent))->GetSingleEntity() == nullptr)
		{
			auto entities = _pool->GetEntities();
			for (unsigned int i = 0; i < entities.size(); i++)
			{
				_pool->DestroyEntity(entities[i]);
			}
			_pool->ClearGroups();
			for (auto system : _systems)
			{
				if (std::dynamic_pointer_cast<ISetPoolSystem>(system) != nullptr)
				{
					(std::dynamic_pointer_cast<ISetPoolSystem>(system)->SetPool(_pool));
				}
			}

			_systemContainer->Initialize();
		}

		_systemContainer->Execute();
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		Dispatcher::Instance().onMouseMove(vec2f(x, y));		
	}
	
	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		Dispatcher::Instance().onMouseButtonClick(button, isReleased);
	}

	virtual void onKeyPressed(FRKey k) {
		Dispatcher::Instance().onKeyPressed(k);
	}

	virtual void onKeyReleased(FRKey k)	{
		Dispatcher::Instance().onKeyReleased(k);
	}

	virtual const char* GetTitle() override
	{
		return "asteroids";
	}
};

int main(int argc, char *argv[])
{
	GameConfig::Instance().Initialize(argc, argv);
	return run(new MyFramework);
}


