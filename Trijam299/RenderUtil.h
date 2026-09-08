#pragma once

namespace RenderUtil
{
	extern int scrWid;
	extern int scrHei;

	void InitRenderTexture();
	void UpdateRenderTexture();
	void CloseRenderTexture();

	void BeginDrawingFrame();
	void EndMainDrawing();
	void EndDrawingFrame();
}

