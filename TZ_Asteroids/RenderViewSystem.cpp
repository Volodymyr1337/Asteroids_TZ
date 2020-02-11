#include "RenderViewSystem.h"
#include "ViewComponent.h"
#include "PositionComponent.h"
#include "vec2.h"
#include <map>
#include <iostream>

void RenderViewSystem::SetPool(Pool * pool)
{
	_group = pool->GetGroup(Matcher_AllOf(ViewComponent));
}

void RenderViewSystem::Execute()
{
	std::map<int, std::vector<EntityPtr>> map;

	for (auto &entity : _group->GetEntities())
	{
		int renderOrder = entity->Get<ViewComponent>()->renderOrder;
		std::map<int, std::vector<EntityPtr>>::iterator it = map.find(renderOrder);
		if (it != map.end())
		{
			it->second.push_back(entity);
		}
		else
		{
			map.insert(std::pair<int, std::vector<EntityPtr>>(renderOrder, { entity }));
		}
	}
	for (std::map<int, std::vector<EntityPtr>>::iterator i = map.begin(); i != map.end(); ++i)
	{
		for (EntityPtr &entity : i->second)
		{
			Sprite* sprite = entity->Get<ViewComponent>()->sprite;

			if (entity->Has<PositionComponent>())
			{
				vec2f position = entity->Get<PositionComponent>()->position;
				drawSprite(sprite, position.x, position.y);
			}
		}
	}
}
