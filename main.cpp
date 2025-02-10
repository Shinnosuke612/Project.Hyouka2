#include <Novice.h>
#include "Scene.h"
#include "Play.h"
#include "Title.h"

const char kWindowTitle[] = "LC1C_20_タカハシ_シンノスケ";

int Scene::score[5] = { 0 };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Scene *play = new Play();
	Scene *title = new Title();

	NowScene nowScene = TITLE;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		switch (nowScene)
		{
		case TITLE:
			//タイトルの処理
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				nowScene = PLAY;
				play = new Play();
			}
			title->Update(keys,preKeys);
			title->Draw();
			break;

		case PLAY:
			//プレイ画面の処理
			play->Update(keys,preKeys);
			play->Draw();
			play->ChengeScene(nowScene,keys,preKeys);
			break;
		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
