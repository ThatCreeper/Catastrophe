#include <RenderUtil.h>
#include <raylib.h>

namespace RenderUtil {
	RenderTexture2D renderTexture;
	int scrWid;
	int scrHei;

	void InitRenderTexture() {
		scrWid = GetScreenWidth();
		scrHei = GetScreenHeight();
		renderTexture = LoadRenderTexture( scrWid, scrHei );
	}

	void UpdateRenderTexture() {
		if ( GetScreenWidth() != scrWid || GetScreenHeight() != scrHei ) {
			scrWid = GetScreenWidth();
			scrHei = GetScreenHeight();

			UnloadRenderTexture( renderTexture );
			renderTexture = LoadRenderTexture( scrWid, scrHei );
		}
	}

	void CloseRenderTexture() {
		UnloadRenderTexture( renderTexture );
	}

	void BeginDrawingFrame() {
		BeginTextureMode( renderTexture );
	}

	void EndMainDrawing() {
		EndTextureMode();

		BeginDrawing();

		//BeginShaderMode(s.s.blur);
		//SetShaderValueTexture(s.s.blur, s.s.uniform_blur_lut, s.t.baselut);

		DrawTexturePro( renderTexture.texture, { 0, 0, (float)scrWid, -(float)scrHei }, { 0, 0, (float)scrWid, (float)scrHei }, { 0, 0 }, 0, WHITE );

		//EndShaderMode();
	}

	void EndDrawingFrame() {
		EndDrawing();
	}
}

