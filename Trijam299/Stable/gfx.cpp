#include "global.h"

void DrawKeybindBar(const char *left, const char *right, bool bg) {
	int SCRWID = GetScreenWidth();
	int SCRHEI = GetScreenHeight();

	if (bg)
		DrawRectangle(0, SCRHEI - 30, SCRWID, 30, Fade(BLACK, 0.7f));
	DrawLine(0, SCRHEI - 31, SCRWID, SCRHEI - 31, WHITE); // I dislike the number "31" here, but it is correct. Sad.
	DrawText(left, 10, SCRHEI - 25, 20, WHITE);
	int rlen = MeasureText(right, 20);
	DrawText(right, SCRWID - 10 - rlen, SCRHEI - 25, 20, WHITE);
}

void DrawCrosshair( float x, float y, float size )
{
	DrawLine( x - size, y, x + size, y, RED );
	DrawLine( x, y - size, x, y + size, GREEN );
}
