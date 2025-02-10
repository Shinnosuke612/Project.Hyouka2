#pragma once
#include "Struct.h"
class Scene {
public:
	static int score[5];

	Scene();
	~Scene();
	virtual void Update(const char* keys, const char* preKeys);
	virtual void Draw();

	virtual void ChengeScene(NowScene& nowScene, const char* keys, const char* preKeys);
};

