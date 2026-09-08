#pragma once

#include <entity.h>

struct Player : entity {
	DEFINE_ENT( Player, entity );

	void update() override;

	void render() override;

	void gui() override;
};
