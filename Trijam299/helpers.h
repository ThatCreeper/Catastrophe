#pragma once

#include <string_view>
#include <cmath>
#include <cstdint>

inline int Overflow(int x, int min, int max) {
	if (x < min)
		return max;
	if (x > max)
		return min;
	return x;
}

inline int Overflow(int x, int max) {
	return Overflow(x, 0, max);
}

inline float Clamp(float x, float min = 0, float max = 1) {
	if (x < min)
		return min;
	if (x > max)
		return max;
	return x;
}

inline int Max(int a, int b) {
	if (a > b)
		return a;
	return b;
}

inline float Max(float a, float b) {
	if (a > b)
		return a;
	return b;
}

inline int Min(int a, int b) {
	if (a < b)
		return a;
	return b;
}

inline float Min(float a, float b) {
	if (a < b)
		return a;
	return b;
}

inline int Clamp(int x, int min, int max) {
	if (x < min)
		return min;
	if (x > max)
		return max;
	return x;
}

inline float Clamp(float x, int min, int max) {
	return Clamp(x, (float)min, (float)max);
}

inline float Dist(float ax, float ay, float bx, float by) {
	float xd = ax - bx;
	float yd = ay - by;
	return sqrtf(xd * xd + yd * yd);
}

inline float Dist(float x, float y) {
	return sqrtf(x * x + y * y);
}

inline float LerpUnclamped(float from, float to, float x, float max) {
	float t = x / max;
	return from + (to - from) * t;
}

inline float LerpUnclamped( float from, float to, float x ) {
	return from + ( to - from ) * x;
}

inline float Lerp( float from, float to, float x )
{
	return LerpUnclamped( from, to, Clamp( x ) );
}

inline float LerpDistRound(float from, float to, float x, float max, float dist) {
	float l = LerpUnclamped(from, to, x, max);
	if (std::abs(l - to) < dist)
		return to;
	return l;
}

// X from 0 to 1
inline float SInterp(float x) {
	return (1 - cosf(PI * x)) / 2;
}

inline float SInterp(float x, float max) {
	return SInterp(x / max);
}

inline float SInterp(float from, float to, float x, float max) {
	float i = SInterp(x, max);
	return from + (to - from) * i;
}

inline float NonPeriodic( float seed, float ratea, float x )
{
	float starta = std::hash<float>()( seed );
	float startb = std::hash<float>()( seed + 1 );
	
	float raw = sinf( starta + ratea * x * 5 ) + sinf( startb + ratea * PI * 2 );

	float normalized = ( raw / 4 ) + 0.5f;

	return normalized;
}

#define DELTA (GetFrameTime())

#define UIM_F_DRAG( f ) ImGui::DragFloat( #f, &f );
#define UIM_F_RO( f ) ImGui::Text( #f " = %f", f );
#define UIM_I_RO( i ) ImGui::Text( #i " = %d", i );
#define UIM_IX_RO( i ) ImGui::Text( #i " = 0x%x", i );
#define UIM_F2_DRAG( v ) ImGui::DragFloat2( #v, &v.x );

struct float2
{
	float x, y;

	inline float2( float v ) : x( v ), y( v ) {}
	inline float2( float x, float y ) : x( x ), y( y ) {}

	inline float2 operator +( const float2 &o ) const
	{
		return { x + o.x, y + o.y };
	}
	inline float2 operator -( const float2 &o ) const
	{
		return { x - o.x, y - o.y };
	}
	inline float2 operator *( const float2 &o ) const
	{
		return { x * o.x, y * o.y };
	}
	inline float2 operator /( const float2 &o ) const
	{
		return { x / o.x, y / o.y };
	}

	inline float2 lerp( float2 other, float t ) const
	{
		return { Lerp( x, other.x, t ), Lerp( y, other.y, t ) };
	}

	inline float2 round() const
	{
		return { std::round( x ), std::round( y ) };
	}
	inline float2 floor() const
	{
		return { std::floor( x ), std::floor( y ) };
	}
};
