#include "Play.h"
#include "Bullet.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Collision.h"
#include <Novice.h>
#include <random>
#include <chrono>

Play::Play()
{
	player_ = new Player();

	camera_ = new Camera();

	for (int i = 0; i < kMaxEnemyAmount; i++) {
		enemy_[i] = new Enemy(640.0f);
	}

	enemyKillCount = 0;
	level = 0;
	maxSpawnCoolTime = 146;
	spawnCoolTime = 0;

	score = 0;

}

Play::~Play()
{
	delete player_;
	for (int i = 0; i < kMaxEnemyAmount; i++) {
		delete enemy_[i];
	}
}

void Play::EnemySpawn()
{
	for (int i = 0; i < kMaxEnemyAmount; i++) {


		//時間からシードを生成
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = now.time_since_epoch();
		auto seed = static_cast<unsigned int>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count());
		// シードを使って乱数エンジンを初期化
		std::mt19937 engine(seed);

		// 画面からエネミーがはみ出ない範囲の乱数を生成
		std::uniform_int_distribution<int> dist(int(enemy_[i]->GetWidth() / 2), int(kPlayWindouWidth - enemy_[i]->GetWidth() / 2)); 

		// ランダムな整数を生成
		int random_number = dist(engine);


		//出現してない敵を出現
		if (!enemy_[i]->GetIsAlive()) {
			enemy_[i]->SetPos({ float(random_number), kWindowHeight + enemy_[i]->GetWidth() });
			enemy_[i]->SetIsAlive(true);
			spawnCoolTime = maxSpawnCoolTime - level * 12;
			break;
		}
	}
}

void Play::ChengeScene(NowScene& nowScene, const char* keys, const char* preKeys)
{
	if (!player_->GetIsAlive() && keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		nowScene = TITLE;
		delete this;
	}
}

void Play::Update(const  char* keys, const char* preKeys)
{
	preKeys = preKeys;

	//毎フレームスコアとタイマーを加算
	if (player_->GetIsAlive()) {
		score++;
	}


	//レンダリングパイプラインのためのカメラ
	Matrix3x3 cameraMatrix = camera_->MakeAffineMatrix(camera_->GetCameraScale(), 0.0f, camera_->GetCameraPos());

	Matrix3x3 viewMatrix = camera_->Inverse3x3(cameraMatrix);

	Matrix3x3 orthoMatrix = camera_->MakeOrthographicMatrix(-kPlayWindouWidth / 2, kWindowHeight / 2, kPlayWindouWidth / 2, -kWindowHeight / 2);

	Matrix3x3 viewportMatrix = camera_->MakeViewPortMatrix(0, 0, kPlayWindouWidth, kWindowHeight);

	camera_->GetvpvpMatrix() = camera_->Multiply(viewMatrix, orthoMatrix);

	camera_->GetvpvpMatrix() = camera_->Multiply(camera_->GetvpvpMatrix(), viewportMatrix);
	

	//プレイヤーの更新処理
	player_->Update(keys);


	//ランダムにスポーンタイマーを減らす
	if (spawnCoolTime > 0) {
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = now.time_since_epoch();
		auto seed = static_cast<unsigned int>(
			std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count());
		// シードを使って乱数エンジンを初期化
		std::mt19937 engine(seed); // 高品質な乱数エンジン
		std::uniform_int_distribution<int> dist(1, 3); // 1～3の範囲の乱数を生成

		// ランダムな整数を生成
		int random_number = dist(engine);
		spawnCoolTime-= random_number;
	}

	//スポーンタイマーが0なら敵を出現
	if (spawnCoolTime <= 0) {
		EnemySpawn();
	}

	//敵の更新処理
	for (int i = 0; i < kMaxEnemyAmount; i++) {
		enemy_[i]->Update(player_);
	}


	//敵の弾とプレイヤーの当たり判定
	for (int i = 0; i < kMaxEnemyAmount; i++) {
		for (int j = 0; j < kMaxEnemyBullet; j++) {
			if (IsHit(enemy_[i]->bullet_[j]->GetPos(), enemy_[i]->bullet_[j]->GetRadius(), player_->GetPos(), player_->GetWidth() / 2)) {
				if (player_->GetIsAlive() && enemy_[i]->bullet_[j]->GetIsShot()) {
					player_->SetIsAlive(false);
					enemy_[i]->bullet_[j]->SetIsShot(false);
					//スコアが高かったら記録
					for (int k = 0; k < 5; k++) {
						if (Scene::score[k] < score) {
							for (int l = 4; l > k; l--) {
								Scene::score[l] = Scene::score[l - 1];
							}
							Scene::score[k] = score;
							break;
						}
						
					}
				}
			}
		}
	}

	//敵とプレイヤーの弾の当たり判定
	for (int i = 0; i < kMaxPlayerBullet; i++) {
		for (int j = 0; j < kMaxEnemyAmount; j++) {
			if (IsHit(player_->bullet_[i]->GetPos(), player_->bullet_[i]->GetRadius(), enemy_[j]->GetPos(), enemy_[j]->GetWidth() / 2)) {
				if (enemy_[j]->GetIsAlive() && player_->bullet_[i]->GetIsShot()) {
					enemy_[j]->SetIsAlive(false);
					player_->bullet_[i]->SetIsShot(false);
					//スコアを加算
					score += 10000;
					//レベルアップのためのカウント
					enemyKillCount++;
				}
			}
		}
	}

	//敵をキルするとレベルがアップ
	if (enemyKillCount >= (level * 2) + 3) {
		if (level < 10) {
			level++;
		}
		enemyKillCount = 0;
	}

}

void Play::Draw()
{
	//スクリーン座標系に変換して描画
	player_->SetScreen(camera_->Transform(player_->GetPos(), camera_->GetvpvpMatrix()));

	for (int i = 0; i < kMaxPlayerBullet; i++) {
		player_->bullet_[i]->SetScreen(camera_->Transform(player_->bullet_[i]->GetPos(), camera_->GetvpvpMatrix()));
	}


	for (int i = 0; i < kMaxEnemyAmount; i++) {
		for (int j = 0; j < kMaxEnemyBullet; j++) {
			enemy_[i]->bullet_[j]->SetScreen(camera_->Transform(enemy_[i]->bullet_[j]->GetPos(), camera_->GetvpvpMatrix()));
		}
		enemy_[i]->SetScreen(camera_->Transform(enemy_[i]->GetPos(), camera_->GetvpvpMatrix()));
		enemy_[i]->Draw();
	}

	player_->Draw();


	//画面右側にUIを表示
	Novice::DrawBox(kPlayWindouWidth, 0, kPlayWindouWidth - kUiWindouWidth, kWindowHeight, 0.0f, 0x000000ff, kFillModeSolid);
	Novice::ScreenPrintf(kPlayWindouWidth + kUiWindouWidth / 2 - 40, 0, "%011d", score);
	Novice::ScreenPrintf(kPlayWindouWidth + kUiWindouWidth / 2 - 35,200 ,"Move:AD");
	Novice::ScreenPrintf(kPlayWindouWidth + kUiWindouWidth / 2 - 50,240 ,"Shot:SPACE");
	Novice::ScreenPrintf(kPlayWindouWidth + kUiWindouWidth / 2 - 50,320 ,"level:%d",level);
	for (int i = 0; i < 5; i++) {
		if (!player_->GetIsAlive() && score == Scene::score[i]) {
			Novice::DrawBox(kPlayWindouWidth, (i * 20) + 360, kUiWindouWidth, 20, 0.0f, 0x88000088, kFillModeSolid);
		}
		Novice::ScreenPrintf(kPlayWindouWidth + kUiWindouWidth / 2 - 90, (i * 20) + 360, "Ranking: %011d", Scene::score[i]);
	}
	if (!player_->GetIsAlive()) {
		Novice::ScreenPrintf(kPlayWindouWidth + kUiWindouWidth / 2 - 60, 540, "Space to Title");
	}
}


