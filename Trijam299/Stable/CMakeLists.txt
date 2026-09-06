target_include_directories( Trijam299 PRIVATE . )

target_sources( Trijam299
	PRIVATE
		enet.h
		flux.cpp
		flux.h
		flux_easings.h
		gfx.cpp
		gfx.h
		sound.cpp
		sound.h
		standard.h
		version.h
		#version_debug.h
		version_norm.cpp
		version_norm.h
)
