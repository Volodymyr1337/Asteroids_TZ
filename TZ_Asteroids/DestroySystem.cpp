#include "DestroySystem.h"
#include "DestroyComponent.h"
#include "ProjectileComponent.h"
#include "AsteroidComponent.h"
#include "ViewComponent.h"
#include "Dispatcher.h"


void DestroySystem::SetPool(Pool * pool)
{
	_pool = pool;
}

void DestroySystem::Execute()
{
	std::vector<EntityPtr> entities = _pool->GetGroup(Matcher_AllOf(DestroyComponent))->GetEntities();
	int size = entities.size();
	for (unsigned int i = 0; i < size; i++)
	{
		bool isAsteroid = entities[i]->Has<AsteroidComponent>();
		_pool->DestroyEntity(entities[i]);
		if (isAsteroid)
		{
			Dispatcher::Instance().onAsteroidDestroyed(_pool->GetGroup(Matcher_AllOf(AsteroidComponent))->Count());
		}
	}
}

DestroySystem::~DestroySystem()
{
	delete _pool;
}
