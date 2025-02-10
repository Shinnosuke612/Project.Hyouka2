#include "Bullet.h"
#include "Object.h"
#include "Collision.h"
#include <Novice.h>

Bullet::Bullet(Vector2 pos)
{
	pos_ = pos;
	screenPos_ = { 0,0 };
	radius_ = 8.0f;
	speed_ = { 0.0f,0.0f };
	isShot_ = false;
	color_ = 0xffffffff;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	//画面外に出たら発射フラグをfalseに
	if (pos_.x <= -radius_ || pos_.y <= -radius_ ||
		pos_.x >= kPlayWindouWidth + radius_ || pos_.y >= kWindowHeight + radius_) {
		isShot_ = false;
	}

	//毎フレーム移動
	pos_.x += speed_.x;
	pos_.y += speed_.y;

}

void Bullet::Draw()
{

	//発射されていたら描画
	if (isShot_) {
		Novice::DrawEllipse(int(screenPos_.x), int(screenPos_.y), int(radius_), int(radius_), 0.0f, color_, kFillModeSolid);
	}
}
