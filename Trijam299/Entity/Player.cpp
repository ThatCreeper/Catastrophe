#include "Player.h"
#include <GameState.h>
#include <box3d/box3d.h>
#include <box3dhelper.h>

void Player::OnSpawn() {
	b3WorldDef worldDef = b3DefaultWorldDef();
	mPhysWorld = b3CreateWorld(&worldDef);

	b3BodyDef groundDef = b3DefaultBodyDef();
	groundDef.type = b3_staticBody;
	groundDef.position = b3Vec3(0, -10, 0);
	b3BodyId groundBody = b3CreateBody(mPhysWorld, &groundDef);

	b3BoxHull groundBox = b3MakeBoxHull(50, 10, 50);
	b3ShapeDef groundShapeDef = b3DefaultShapeDef();
	//groundShapeDef.baseMaterial.restitution = 0.9f;
	b3CreateHullShape(groundBody, &groundShapeDef, &groundBox.base);



	b3BodyDef playerBodyDef = b3DefaultBodyDef();
	playerBodyDef.type = b3_dynamicBody;
	playerBodyDef.position = b3Vec3(0, 10, 10);
	playerBodyDef.motionLocks = b3MotionLocks {
		.angularX = true,
		.angularZ = true
	};
	mPlayerBody = b3CreateBody(mPhysWorld, &playerBodyDef);

	b3BoxHull playerBodyBox = b3MakeBoxHull(1, 1, 1);
	b3ShapeDef playerBodyBoxDef = b3DefaultShapeDef();
	b3CreateHullShape(mPlayerBody, &playerBodyBoxDef, &playerBodyBox.base);
}

void Player::OnRemove() {
	b3DestroyWorld(mPhysWorld);
}

void Player::update() {
	b3World_Step(mPhysWorld, DELTA, 4);

	float axisForward  = GetKeyAxis(KEY_W, KEY_S) * 20;
	float axisSideways = GetKeyAxis(KEY_A, KEY_D) * 20;
	// position.z += GetKeyAxis (KEY_W, KEY_S) * DELTA * 20;
	// position.x += GetKeyAxis (KEY_A, KEY_D) * DELTA * 20;
	// position.y += GetKeyAxis (KEY_Q, KEY_E) * DELTA * 20;

	b3Vec3 velocity = b3Body_GetLinearVelocity(mPlayerBody);
	// TODO: Doesn't actually make any sense.
	bool isOnGround = FloatRoughlyEquals(velocity.y, 0, 0.05);

	velocity.x = axisSideways * cos(s.camRot.y * DEG2RAD) - axisForward * sin(s.camRot.y * DEG2RAD);
	velocity.y -= 10 * DELTA;
	velocity.z = axisForward * cos(s.camRot.y * DEG2RAD) + axisSideways * sin(s.camRot.y * DEG2RAD);

	if (isOnGround && IsKeyDown(KEY_SPACE)) {
		velocity.y = 20;
	}


	b3Body_SetLinearVelocity(mPlayerBody, velocity);
	b3Body_SetAwake(mPlayerBody, true);

	position = b3ToFloat3(b3Body_GetPosition(mPlayerBody));

	s.camRot.y += GetKeyAxis(KEY_LEFT, KEY_RIGHT) * DELTA * 50;
	s.camRot.x += GetKeyAxis(KEY_UP, KEY_DOWN) * DELTA * 50;

	s.camPos = position;
}

void Player::render() {
	DrawCubeWires({ 0, 0, 0 }, 1, 1, 1, RED);
}

void Player::gui() {
	base::gui();

	float3 velocity = b3ToFloat3(b3Body_GetLinearVelocity(mPlayerBody)) + float3(0, 10 * DELTA, 0);
	UIM_F3_RO(velocity);
}
