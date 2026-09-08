#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include "external/glad.h"
#include "RenderUtil.h"
#include "FrameTools.h"
#include "global.h"
#include "entity.h"
#include "world.h"
#include "resource_mess.h"
#include "GameState.h"
#include <Player.h>

Textures gTex;
Shaders gShd;
GameState s;

namespace TrijamVersion {
	bool TrijamRunGame() {
		bool restart = false;
		gTex.Load();
		gShd.Load();
		s = {};

		RenderUtil::InitRenderTexture();

		s.world.add( s.localPlayer = new Player() );

		while ( !WindowShouldClose() )
		{
			RenderUtil::UpdateRenderTexture();

			// flux::update(GetFrameTime());
			//gFlux.update( DELTA );

			s.world.update();

			RenderUtil::BeginDrawingFrame();

			ClearBackground( DARKGRAY );
			FrameTools::SetupCamera(s.camPos, s.camRot);

			DrawCrosshair3D( 0, 0, 0, 1 );
			s.world.render();

			FrameTools::PopCamera();
			RenderUtil::EndMainDrawing();

			rlImGuiBegin();
			s.DrawDebugUI();
			rlImGuiEnd();

			RenderUtil::EndDrawingFrame();
		}

		RenderUtil::CloseRenderTexture();
		SaveGlobState();
		s.close();

		return restart;
	}

}
