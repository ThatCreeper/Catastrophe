#include "Player.h"
#include <GameState.h>
#include <box3d/box3d.h>

void Player::OnSpawn() {
	b3WorldDef worldDef = b3DefaultWorldDef();
	mWorld = b3CreateWorld(&worldDef);

	b3BodyDef groundDef = b3DefaultBodyDef();
	groundDef.type = b3_staticBody;
	groundDef.position = b3Vec3(0, -20, 0);
	b3BodyId groundBody = b3CreateBody(mWorld, &groundDef);

	b3BoxHull groundBox = b3MakeBoxHull(50, 10, 50);
	b3ShapeDef groundShapeDef = b3DefaultShapeDef();
	groundShapeDef.baseMaterial.restitution = 0.9f;
	b3CreateHullShape(groundBody, &groundShapeDef, &groundBox.base);



	b3BodyDef playerBodyDef = b3DefaultBodyDef();
	playerBodyDef.type = b3_dynamicBody;
	playerBodyDef.position = b3Vec3(0, 10, 10);
	mPlayerBody = b3CreateBody(mWorld, &playerBodyDef);

	b3BoxHull playerBodyBox = b3MakeBoxHull(1, 1, 1);
	b3ShapeDef playerBodyBoxDef = b3DefaultShapeDef();
	b3CreateHullShape(mPlayerBody, &playerBodyBoxDef, &playerBodyBox.base);
}

void Player::OnRemove() {
	b3DestroyWorld(mWorld);
}

void Player::update() {
	b3World_Step(mWorld, DELTA, 4);

	// position.z += GetKeyAxis (KEY_W, KEY_S) * DELTA * 20;
	// position.x += GetKeyAxis (KEY_A, KEY_D) * DELTA * 20;
	// position.y += GetKeyAxis (KEY_Q, KEY_E) * DELTA * 20;

	b3Vec3 physPos = b3Body_GetPosition(mPlayerBody);
	position = float3(physPos.x, physPos.y, physPos.z);

	s.camRot.y += GetKeyAxis (KEY_LEFT, KEY_RIGHT) * DELTA * 50;
	s.camRot.x += GetKeyAxis (KEY_UP, KEY_DOWN) * DELTA * 50;

	s.camPos = position;
}

void Player::render() {
	DrawRectangle (-8, -8, 16, 16, YELLOW);
}

void Player::gui() {
	base::gui();
}
