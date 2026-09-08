add_subdirectory( Entity )
add_subdirectory( ImGui )
add_subdirectory( Stable )

target_include_directories( Trijam299 PRIVATE . )

target_sources( Trijam299
	PRIVATE
		cpp.hint
		entity.h
		global.h
		FrameTools.cpp
		FrameTools.h
		GameState.cpp
		GameState.h
		globstate.cpp
		globstate.h
		helpers.h
		RenderUtil.cpp
		RenderUtil.h
		resource_mess.h
		TrijamVersion.cpp
		Trijam291.cpp
		world.cpp
		world.h
)
