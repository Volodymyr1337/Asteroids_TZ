#include "ReplaceAccelerationSystem.h"
#include "AccelerationComponent.h"
#include "vec2.h"

void ReplaceAccelerationSystem::SetPool(Pool* pool)
{
	_pool = pool;
}

void ReplaceAccelerationSystem::Execute()
{
	std::vector<EntityPtr> entities = _pool->GetGroup(Matcher_AllOf(AccelerationComponent))->GetEntities();

	for (auto &e : entities)
	{
		vec2f acceleration = e->Get<AccelerationComponent>()->acceleration;
		acceleration *= 1.f - Time::Instance().deltaTime / _accelerationDampening;
		e->Replace<AccelerationComponent>(acceleration);
	}

}
