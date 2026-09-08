#include <FrameTools.h>
#include <raylib.h>
#include <rlgl.h>
#include <imgui.h>

namespace FrameTools {
	void SetupCamera (float3 position, float3 rotation) {
		Camera3D cam = {
			.position = { 0, 0, 0 },
			.target = { 0, 0, -1 },
			.up = { 0, 1, 0 },
			.fovy = 75,
			.projection = CAMERA_PERSPECTIVE,
		};
		BeginMode3D (cam);
		rlPushMatrix();
		rlRotatef (rotation.x, 1, 0, 0);
		rlRotatef (rotation.y, 0, 1, 0);
		rlRotatef (rotation.z, 0, 0, 1);
		rlTranslatef (-position.x, -position.y, -position.z);
	}

	void PopCamera() {
		rlPopMatrix();
		EndMode3D();
	}
}

