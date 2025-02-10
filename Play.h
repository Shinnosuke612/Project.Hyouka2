#pragma once
#include "Scene.h"

class Player;
class Camera;
class Enemy;

class Play :public Scene {
private:
	//敵の出現のための変数
	int enemyKillCount;
	int level;
	int spawnCoolTime;
	int maxSpawnCoolTime;

	//スコアのための変数
	int timer;
	int score;

public:

	Player* player_;
	Camera* camera_;
	Enemy* enemy_[kMaxEnemyAmount];

	Play();
	~Play();

	void Update(const char *keys, const char* preKeys) override;
	void Draw() override;
	void EnemySpawn();
	void ChengeScene(NowScene& nowScene, const char* keys, const char* preKeys) override;
};

