#pragma once
#include "Struct.h"

class Object;

class Bullet {
private:
	Vector2 pos_;
	Vector2 screenPos_;
	Vector2 speed_;
	float radius_;
	int isShot_;
	unsigned int color_;
public:
	Bullet(Vector2 pos);
	~Bullet();

	Vector2 GetPos() { return pos_; }
	float GetRadius() { return radius_; }
	int GetIsShot() { return isShot_; }

	Vector2 SetPos(Vector2 pos) { return pos_ = pos; }
	Vector2 SetScreen(Vector2 screenPos) { return screenPos_ = screenPos; }
	int SetIsShot(int isShot) { return isShot_ = isShot; }
	Vector2 SetSpeed(Vector2 speed) { return speed_ = speed; }

	void Update();
	void Draw();
};

