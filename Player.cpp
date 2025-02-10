#include "Player.h"
#include <Novice.h>
#include "Bullet.h"

Player::Player()
{
	//画面中央の少し下に出現させる
	pos_ = { kPlayWindouWidth / 2, 200.0f };
	screenPos_ = { 0.0f,0.0f };
	width_ = 32.0f;
	height_ = 32.0f;
	speed_ = 4.0f;
	color_ = 0xffffffff;
	isAlive_ = true;
	shotCoolTime = 0;

	for (int i = 0; i < kMaxPlayerBullet; i++) {
		bullet_[i] = new Bullet(pos_);
	}

}

Player::~Player()
{
	for (int i = 0; i < kMaxPlayerBullet; i++) {
		delete bullet_[i];
	}
}

void Player::Update(const char* keys)
{

	//プレイヤーが生きてたら
	if (isAlive_) {

		//ADで左右移動
		if (keys[DIK_D]) {
			if (pos_.x + speed_ <= kPlayWindouWidth - width_ / 2) {
				pos_.x += speed_;
			}
		}
		if (keys[DIK_A]) {
			if (pos_.x - speed_ >= width_ / 2) {
				pos_.x -= speed_;
			}
		}

		//毎フレームクールタイムを減らす
		if (shotCoolTime > 0) {
			shotCoolTime--;
		}

		//発射されていない弾を探して発射
		if (keys[DIK_SPACE]) {
			for (int i = 0; i < kMaxPlayerBullet; i++) {
				if (!bullet_[i]->GetIsShot() && shotCoolTime == 0) {
					//発射するとき位置を合わせる
					bullet_[i]->SetPos(pos_);
					bullet_[i]->SetIsShot(true);
					bullet_[i]->SetSpeed({ 0,9 });
					shotCoolTime = 10;
					break;
				}
			}
		}
		for (int i = 0; i < kMaxPlayerBullet; i++) {
			//弾の移動
			bullet_[i]->Update();
		}
	}
}

void Player::Draw()
{

	//生きていたら自機と弾を描画
	if (isAlive_) {
		Novice::DrawBox(int(screenPos_.x - width_ / 2), int(screenPos_.y - height_ / 2), int(width_), int(height_), 0.0f, color_, kFillModeSolid);
		for (int i = 0; i < kMaxPlayerBullet; i++) {
			bullet_[i]->Draw();
		}
	}
}


