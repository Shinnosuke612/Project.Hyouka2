#pragma once
#include "Struct.h"
class Object {
protected:
	//位置
	Vector2 pos_;
	//表示用の位置
	Vector2 screenPos_;
	//サイズ
	float width_;
	float height_;
	//スピード
	float speed_;
	//色
	unsigned int color_;
	//弾用の変数
	int shotCoolTime;

	int isAlive_;

public:
	int GetIsAlive() { return isAlive_; }
	float GetWidth() { return width_; }
	Vector2 GetPos() { return pos_; }

	Vector2 SetPos(Vector2 pos) { return pos_ = pos; }
	Vector2 SetScreen(Vector2 screenPos) { return screenPos_ = screenPos; }
	int SetIsAlive(int isAlive) { return isAlive_ = isAlive; }

};

