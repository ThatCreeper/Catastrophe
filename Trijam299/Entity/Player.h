#pragma once

#include <entity.h>
#include <box3d/id.h>

struct Player : entity {
	DEFINE_ENT( Player, entity );

	b3WorldId mWorld;
	b3BodyId mPlayerBody;

	void OnSpawn() override;
	void OnRemove() override;

	void update() override;

	void render() override;

	void gui() override;
};
