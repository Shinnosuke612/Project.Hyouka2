#pragma once
#include "Object.h"
#include "Struct.h"

class Bullet;
class Player;

class Enemy : public Object {
private:

	float bulletSpeed_;

public:

	Enemy(float PosX);
	~Enemy();

	void Update(Player *player);
	void Draw();



	Bullet* bullet_[kMaxEnemyBullet];

};

