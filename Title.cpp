#include "Title.h"
#include "Play.h"
#include <Novice.h>

Title::Title()
{
	select = MENU;
}

Title::~Title()
{
}

void Title::Update(const char* keys, const char* preKeys)
{
	keys = keys;
	preKeys = preKeys;
}

void Title::Draw()
{

	//UIの表示
	if (select == MENU) {
		Novice::ScreenPrintf(224, 390, "MENU");
		Novice::ScreenPrintf(219, 420, "ENTER");
	}
	if (select == ENDLESS) {
		Novice::ScreenPrintf(214, 390, "ENDLESS");
		Novice::ScreenPrintf(234, 420, "S↓");
	}
	if (select == SCORE) {
		Novice::ScreenPrintf(219, 390, "SCORE");
		Novice::ScreenPrintf(234, 360, "W↑");
	}
	Novice::DrawBox(kPlayWindouWidth, 0, kPlayWindouWidth - kUiWindouWidth, kWindowHeight, 0.0f, 0x000000ff, kFillModeSolid);
}
