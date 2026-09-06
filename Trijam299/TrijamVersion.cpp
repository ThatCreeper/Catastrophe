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

struct Player;
struct State
{
	int scrWid = 0;
	int scrHei = 0;
	float2 camPos = 0;
	float camScale = 1;
	Player *localPlayer;

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
		UIM_F2_DRAG( camPos );
		UIM_F_DRAG( camScale );

		ImGui::End();
	}
} s;

struct Player : entity
{
	DEFINE_ENT( Player, entity );

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
		base::gui();
	}
};

struct Camera : entity
{
	DEFINE_ENT( Camera, entity );

	void update() override
	{
		position = position.lerp( s.localPlayer->position, DELTA * 10 );

		s.camPos = position;
	}
};

#define ENABLE_POSTPROCESS 0

bool TrijamRunGame() {
	bool restart = false;
	s.reset();

	s.scrWid = GetScreenWidth();
	s.scrHei = GetScreenHeight();
#if ENABLE_POSTPROCESS
	RenderTexture2D render = LoadRenderTexture( s.scrWid, s.scrHei );
#endif

	gWorld.add( s.localPlayer = new Player() );
	gWorld.add( new Camera );

	while ( !WindowShouldClose() )
	{
		if ( GetScreenWidth() != s.scrWid || GetScreenHeight() != s.scrHei )
		{
			s.scrWid = GetScreenWidth();
			s.scrHei = GetScreenHeight();

#if ENABLE_POSTPROCESS
			UnloadRenderTexture( render );
			render = LoadRenderTexture( s.scrWid, s.scrHei );
#endif
		}

		// flux::update(GetFrameTime());
		gFlux.update( DELTA );

		gWorld.update();

#if ENABLE_POSTPROCESS
		BeginTextureMode( render );
#else
		BeginDrawing();
#endif
		ClearBackground( DARKGRAY );
		rlPushMatrix();
		rlTranslatef( s.scrWid / 2.f, s.scrHei / 2.f, 0 );
		rlScalef( s.camScale, s.camScale, 1 );
		rlTranslatef(-s.camPos.x, -s.camPos.y, 0);

		DrawCrosshair( 0, 0, 16 );
		gWorld.render();

		rlPopMatrix();
#if ENABLE_POSTPROCESS
		EndTextureMode();

		BeginDrawing();

		//BeginShaderMode(s.s.blur);
		//SetShaderValueTexture(s.s.blur, s.s.uniform_blur_lut, s.t.baselut);

		DrawTexturePro( render.texture, { 0, 0, (float)s.scrWid, -(float)s.scrHei }, { 0, 0, (float)s.scrWid, (float)s.scrHei }, { 0, 0 }, 0, WHITE );

		//EndShaderMode();
#endif

		rlImGuiBegin();

#ifndef NDEBUG
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
#if ENABLE_POSTPROCESS
	UnloadRenderTexture( render );
#endif
	SaveGlobState();
	s.close();

	return restart;
}

}
