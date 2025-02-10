#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "Collision.h"
#include <math.h>
#include <Novice.h>

Enemy::Enemy(float PosX)
{
	width_ = 32.0f;
	height_ = 32.0f;
	pos_ = { PosX, kWindowHeight + width_ };
	screenPos_ = { 0.0f,0.0f };
	speed_ = 4.0f;
	bulletSpeed_ = 8.0f;
	color_ = 0xffffffff;
	shotCoolTime = 0;
	isAlive_ = false;

	for (int i = 0; i < kMaxEnemyBullet; i++) {
		bullet_[i] = new Bullet(pos_);
	}

}

Enemy::~Enemy()
{
	for (int i = 0; i < kMaxEnemyBullet; i++) {
		delete bullet_[i];
	}
}

void Enemy::Update(Player* player)
{

	//生きていたら
	if (isAlive_) {

		//毎フレームクールタイムを減らす
		if (shotCoolTime > 0) {
			shotCoolTime--;
		}

		//画面上から100下の位置に来るまで移動
		if (pos_.y >= kWindowHeight - 100) {
			pos_.y -= speed_;
			//移動中は撃たない
			shotCoolTime = 20;
		}



		//クールタイムが0なら発射されていない弾を探して発射
		if (shotCoolTime == 0) {
			//プレイヤーが生きてるとき
			if (player->GetIsAlive()) {
				for (int i = 0; i < kMaxEnemyBullet; i++) {
					if (!bullet_[i]->GetIsShot()) {
						//プレイヤーとの距離を取得
						float distance = Distance(pos_, player->GetPos());
						//弾の発射位置を合わせる
						bullet_[i]->SetPos(pos_);
						bullet_[i]->SetIsShot(true);
						//プレイヤーの方向へ弾が行くようにする
						bullet_[i]->SetSpeed({ (player->GetPos().x - pos_.x) / distance * bulletSpeed_,
											   (player->GetPos().y - pos_.y) / distance * bulletSpeed_ });
						shotCoolTime = 80;
						break;

					}
				}
			}
		}

	}


	//弾の更新処理
	for (int i = 0; i < kMaxEnemyBullet; i++) {
		if (bullet_[i]->GetIsShot()) {
			bullet_[i]->Update();
		}
	}
}

void Enemy::Draw()
{

	//生きている時敵機を描画
	if (isAlive_) {
		Novice::DrawBox(int(screenPos_.x - width_ / 2), int(screenPos_.y - height_ / 2), int(width_), int(height_), 0.0f, color_, kFillModeSolid);
	}

	//敵の弾を描画
	for (int i = 0; i < kMaxEnemyBullet; i++) {
		if (bullet_[i]->GetIsShot()) {
			bullet_[i]->Draw();
		}
	}

}
