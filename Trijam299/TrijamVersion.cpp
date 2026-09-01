#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

#include "external/glad.h"

#include "global.h"
#include "entity.h"
#include "world.h"

namespace TrijamVersion
{

#include "resource_mess.h"

Textures gTex;
Shaders gShd;
flux::Group gFlux;
World gWorld;

struct State
{
	int scrWid = 0;
	int scrHei = 0;

	void reset()
	{
		gTex = {};
		gShd = {};
		gFlux = {};
		gWorld = {};

		gTex.Load();
		gShd.Load();
	}

	void close()
	{
		gTex.Unload();
		gShd.Unload();
	}

	void gui() {
#define F_DRAG( f ) ImGui::DragFloat( #f, &f );
#define F_RO( f ) ImGui::Text( #f " = %f", f );
#define I_RO( i ) ImGui::Text( #i " = %d", i );
#define IX_RO( i ) ImGui::Text( #i " = 0x%x", i );
		ImGui::Begin( "State" );

		I_RO( scrWid );
		I_RO( scrHei );

		ImGui::End();
	}
} s;

bool TrijamRunGame() {
	int fadein = 0;
	bool restart = false;
	s.reset();

	PlaySound( SND_START );

	s.scrWid = GetScreenWidth();
	s.scrHei = GetScreenHeight();
	RenderTexture2D render = LoadRenderTexture( s.scrWid, s.scrHei );

	while ( !WindowShouldClose() )
	{
		if ( GetScreenWidth() != s.scrWid || GetScreenHeight() != s.scrHei )
		{
			s.scrWid = GetScreenWidth();
			s.scrHei = GetScreenHeight();

			UnloadRenderTexture( render );
			render = LoadRenderTexture( s.scrWid, s.scrHei );
		}

		// flux::update(GetFrameTime());
		gFlux.update( DELTA );

		gWorld.update();

		BeginTextureMode( render );

		ClearBackground( BLACK );

		gWorld.render();

		EndTextureMode();

		BeginDrawing();
		rlImGuiBegin();

		ClearBackground( BLACK );

		//BeginShaderMode(s.s.blur);
		//SetShaderValueTexture(s.s.blur, s.s.uniform_blur_lut, s.t.baselut);

		DrawTexturePro( render.texture, { 0, 0, (float)s.scrWid, -(float)s.scrHei }, { 0, 0, (float)s.scrWid, (float)s.scrHei }, { 0, 0 }, 0, WHITE );

		//EndShaderMode();

#if _DEBUG
		gTex.Gui();
		gShd.Gui();
		ImGui::Begin( "Entities" );
		gWorld.forEach<entity>( []( entity *e ) { e->gui(); } );
		ImGui::End();
		s.gui();
#endif

		rlImGuiEnd();
		EndDrawing();
	}

END:
	UnloadRenderTexture( render );
	SaveGlobState();
	s.close();

	return restart;
}

}
