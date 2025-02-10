#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Update(const char* keys, const char* preKeys)
{
	keys = keys;
	preKeys = preKeys;
}

void Scene::Draw()
{
}

void Scene::ChengeScene(NowScene& nowScene, const char* keys, const char* preKeys)
{
	nowScene = nowScene;
	keys = keys;
	preKeys = preKeys;
}
