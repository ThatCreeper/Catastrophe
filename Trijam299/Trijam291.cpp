#include "global.h"
#include "rlImGui.h"

// WHATEVER YOU DO, DO NOT ADD CLASSES PLEASE FOR THE LOVE OF GOD. OR, IF YOU DO, THINK ABOUT IT. THINK "DO I NEED THIS". THINK THAT AND THEN SAY /NO/!

// nerddddd - caden 2/28/2026

namespace TrijamVersion { bool TrijamRunGame(); }

int main() {
	LoadGlobState();

	SetTraceLogLevel( LOG_WARNING );
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE /*| FLAG_MSAA_4X_HINT*/);
	InitWindow(DEFAULTSCRWID, DEFAULTSCRHEI, "Weaken Spot");
	
#ifdef _WINDOWS
	if ( GetWindowScaleDPI().x == 2 )
	{
		CloseWindow();
		SetConfigFlags( FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE /*| FLAG_MSAA_4X_HINT*/ );
		InitWindow( DEFAULTSCRWID, DEFAULTSCRHEI, "Weaken Spot" );
	}
#endif
	
	
	rlImGuiSetup(true);
	InitAudioDevice();

	LoadSounds();
	
	SetExitKey(KEY_NULL);

	// SetTargetFPS(30);

	TrijamVersion::TrijamRunGame();

END:
	rlImGuiShutdown();
	CloseWindow();
}
