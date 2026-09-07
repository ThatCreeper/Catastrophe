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
	float3 camPos = 0;
	float3 camRot = 0;
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
		UIM_F3_DRAG( camPos );
		UIM_F3_DRAG(camRot);
		UIM_F_DRAG( camScale );

		ImGui::End();
	}
} s;

struct Player : entity
{
	DEFINE_ENT( Player, entity );

	void update() override
	{
		if ( IsKeyDown( KEY_W ) )
			position.z -= DELTA * 20;
		if ( IsKeyDown( KEY_S ) )
			position.z += DELTA * 20;
		if ( IsKeyDown( KEY_A ) )
			position.x -= DELTA * 20;
		if ( IsKeyDown( KEY_D ) )
			position.x += DELTA * 20;
		if ( IsKeyDown( KEY_Q ) )
			position.y -= DELTA * 20;
		if ( IsKeyDown( KEY_E ) )
			position.y += DELTA * 20;

		if (IsKeyDown(KEY_LEFT))
			s.camRot.y -= DELTA * 50;
		if (IsKeyDown(KEY_RIGHT))
			s.camRot.y += DELTA * 50;
		if (IsKeyDown(KEY_UP))
			s.camRot.x -= DELTA * 50;
		if (IsKeyDown(KEY_DOWN))
			s.camRot.x += DELTA * 50;

		s.camPos = position;
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

struct Spot : entity
{
	DEFINE_ENT(Spot, entity);

	void update() override
	{
		rotation.y += DELTA * 360;
	}

	void render() override
	{
		DrawTexture(gTex.spot, 0, 0, WHITE);
	}
};

#define ENABLE_POSTPROCESS 1

bool TrijamRunGame() {
	bool restart = false;
	s.reset();

	s.scrWid = GetScreenWidth();
	s.scrHei = GetScreenHeight();
#if ENABLE_POSTPROCESS
	RenderTexture2D render = LoadRenderTexture( s.scrWid, s.scrHei );
#endif

	gWorld.add( s.localPlayer = new Player() );
	gWorld.add(new Spot);

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
		Camera3D cam = {
			.position = { 0, 0, 0 },
			.target = { 0, 0, -1 },
			.up = { 0, 1, 0 },
			.fovy = 75,
			.projection = CAMERA_PERSPECTIVE,
		};
		BeginMode3D(cam);
		rlPushMatrix();
		rlRotatef(s.camRot.x, 1, 0, 0);
		rlRotatef(s.camRot.y, 0, 1, 0);
		rlRotatef(s.camRot.z, 0, 0, 1);
		rlTranslatef(-s.camPos.x, -s.camPos.y, -s.camPos.z);

		DrawCrosshair3D( 0, 0, 0, 1 );
		gWorld.render();

		rlPopMatrix();
		EndMode3D();

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
