#pragma once
#include "Object.h"
#include "Struct.h"

class Bullet;

class Player : public Object{

public:
	Player();
	~Player();

	void Update(const char *keys);
	void Draw();

	//弾
	Bullet* bullet_[kMaxPlayerBullet];
};

