#include "Player.h"
#include <GameState.h>

void Player::update() {
	position.z += GetKeyAxis (KEY_W, KEY_S) * DELTA * 20;
	position.x += GetKeyAxis (KEY_A, KEY_D) * DELTA * 20;
	position.y += GetKeyAxis (KEY_Q, KEY_E) * DELTA * 20;

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
