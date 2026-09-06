#include "world.h"
#include <rlgl.h>

void World::add(entity* e)
{
	entities.emplace_back(e);
	e->spawnRenderer();
	e->init();
}

void World::remove(entity* e)
{
	e->onRemove();
	e->removed = true;
}

void World::clear()
{
	for (auto &e : entities) e->onRemove();
	entities.clear();
}

void World::update()
{
	for (auto &e : entities) {
		if (e->removed) continue;
		e->update();
	}
	std::erase_if(entities, [](const auto &e) { return e->removed; });
}

void World::render()
{
		std::vector<entity *> sortedEnts;
		sortedEnts.reserve( entities.size() );
		for ( auto &e : entities )
		{
			sortedEnts.push_back( e.get() );
		}

		std::stable_sort( sortedEnts.begin(), sortedEnts.end(), [](entity *l, entity *r)
			{
				return l->zLayer < r->zLayer;
			});

		for ( entity *e : sortedEnts )
		{
			if (e->removed) continue;
			rlPushMatrix();
			rlTranslatef( e->position.x, e->position.y, 0 );
			rlRotatef( e->rotation, 0, 0, 1 );
			e->render();
			rlPopMatrix();
		}
	}
