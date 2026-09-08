#pragma once

#include "helpers.h"
#include "world.h"
#include "resource_mess.h"
#include "RenderUtil.h"

extern struct GameState s;

struct Player;
struct GameState
{
	float3 camPos = 0;
	float3 camRot = 0;
	float camScale = 1;
	Player *localPlayer;
	World world;

	void reset()
	{
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

		UIM_I_RO( RenderUtil::scrWid );
		UIM_I_RO( RenderUtil::scrHei );
		UIM_F3_DRAG( camPos );
		UIM_F3_DRAG(camRot);
		UIM_F_DRAG( camScale );

		ImGui::End();
	}

	void DrawDebugUI() {
		#ifndef NDEBUG
		gTex.Gui();
		gShd.Gui();
		ImGui::Begin ("Entities");
		world.forEach<entity> ([] (entity * e) {
			e->trueGui();
		});
		ImGui::End();
		gui();
		#endif
	}
};
