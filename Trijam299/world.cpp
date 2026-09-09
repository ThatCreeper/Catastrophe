#include "world.h"
#include <rlgl.h>

void World::add(entity* e)
{
	entities.emplace_back(e);
	e->mWorld = this;
	e->OnSpawn();
}

void World::remove(entity* e)
{
	e->OnRemove();
	e->mRemoved = true;
}

void World::clear()
{
	for (auto &e : entities) e->OnRemove();
	entities.clear();
}

void World::update()
{
	for (auto &e : entities) {
		if (e->mRemoved) continue;
		e->update();
	}
	std::erase_if(entities, [](const auto &e) { return e->mRemoved; });
}

void World::render()
{
	// NOTE: cadenr 9/9/2026 This code adds 2d entity sorting.
	// It has been removed because the engine is currently targetting 3d.

	// std::vector<entity *> sortedEnts;
	// sortedEnts.reserve( entities.size() );
	// for ( auto &e : entities )
	// {
	// 	sortedEnts.push_back( e.get() );
	// }
	//
	// std::stable_sort( sortedEnts.begin(), sortedEnts.end(), [](entity *l, entity *r)
	// 	{
	// 		return l->zLayer < r->zLayer;
	// 	});
	//
	// for ( entity *e : sortedEnts )
	for (const auto &e : entities)
	{
		if (e->mRemoved) continue;
		rlPushMatrix();
		rlTranslatef( e->position.x, e->position.y, e->position.z );
		rlRotatef( e->rotation.x, 1, 0, 0 );
		rlRotatef( e->rotation.y, 0, 1, 0 );
		rlRotatef( e->rotation.z, 0, 0, 1 );
		e->render();
		rlPopMatrix();
	}
}
