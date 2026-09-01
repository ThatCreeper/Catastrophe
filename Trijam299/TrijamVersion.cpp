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
		ImGui::Begin( "State" );

		UIM_I_RO( GetFPS() );
		UIM_F_RO( DELTA );

		UIM_I_RO( scrWid );
		UIM_I_RO( scrHei );

		ImGui::End();
	}
} s;

struct Player : entity
{
	DEFINE_ENT( Player );

	void update() override
	{
		if ( IsKeyDown( KEY_LEFT ) )
			position.x -= DELTA * 100;
		if ( IsKeyDown( KEY_RIGHT ) )
			position.x += DELTA * 100;
	}

	void render() override
	{
		DrawRectangle( -8, -8, 16, 16, YELLOW );
	}

	void gui() override
	{
		entity::gui();
	}
};

bool TrijamRunGame() {
	int fadein = 0;
	bool restart = false;
	s.reset();

	s.scrWid = GetScreenWidth();
	s.scrHei = GetScreenHeight();
	RenderTexture2D render = LoadRenderTexture( s.scrWid, s.scrHei );

	gWorld.add( new Player() );

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

		ClearBackground( DARKGRAY );

		gWorld.render();

		EndTextureMode();

		BeginDrawing();
		rlImGuiBegin();

		//BeginShaderMode(s.s.blur);
		//SetShaderValueTexture(s.s.blur, s.s.uniform_blur_lut, s.t.baselut);

		DrawTexturePro( render.texture, { 0, 0, (float)s.scrWid, -(float)s.scrHei }, { 0, 0, (float)s.scrWid, (float)s.scrHei }, { 0, 0 }, 0, WHITE );

		//EndShaderMode();

#if _DEBUG
		gTex.Gui();
		gShd.Gui();
		ImGui::Begin( "Entities" );
		gWorld.forEach<entity>( []( entity *e ) { e->trueGui(); } );
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
