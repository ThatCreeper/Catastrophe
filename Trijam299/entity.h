#pragma once

#include "flux.h"
#include "raylib.h"
#include "imgui.h"
#include "helpers.h"

struct World;
struct entity {
	flux::Group tw;
	bool mRemoved = false;
	// int zLayer = 0;
	float3 position = 0;
	float3 rotation = 0;
	World *mWorld = nullptr;

	virtual ~entity() {
		if (!mRemoved) OnRemove();
	};
	entity() {}

	virtual void OnSpawn() {}
	virtual void OnRemove() {}

	virtual void update() {
		tw.update(GetFrameTime());
	}
	virtual void render() {}
	virtual void gui() {
		UIM_F3_DRAG( position );
		UIM_F3_DRAG( rotation );
	}

	virtual void trueGui() = 0;

	inline bool baseGuiHeader(const char *name) {
		const char *processed = TextFormat("%s %d##%d", name, ((int)(intptr_t)this) & 0x1FF, ((int)(intptr_t)this));
		return ImGui::TreeNode(processed);
	}
};

#define ENT_GUI_BEGIN( name ) if ( !guiHeader( name ) ) return
#define ENT_GUI_END() ImGui::TreePop()
#define DEFINE_ENT( name, baseClass ) \
	public: \
	\
	using base = baseClass; \
	inline void trueGui() override \
	{ \
		if ( !baseGuiHeader( #name ) ) return; \
		this->gui(); \
		ImGui::TreePop(); \
	}
