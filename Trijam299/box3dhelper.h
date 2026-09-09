#pragma once

#include <box3d/box3d.h>
#include "helpers.h"

inline b3Vec3 b3FromFloat3(float3 v) {
	return b3Vec3(v.x, v.y, v.z);
}

inline float3 b3ToFloat3(b3Vec3 v) {
	return float3(v.x, v.y, v.z);
}
