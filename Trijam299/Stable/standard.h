#pragma once

#ifdef __linux__
#define TRIGGER_DEBUGGER __builtin_debugtrap()
#else
#define TRIGGER_DEBUGGER __debugbreak()
#endif
