#include "Collision.h"
#include <math.h>

//距離を計算して返す関数
float Distance(Vector2 main, Vector2 target)
{
	return (sqrtf(powf(main.x - target.x, 2) + powf(main.y - target.y, 2)));
}

//当たっているか返す関数
int IsHit(Vector2 main, float mainRadius, Vector2 target, float targetRadius)
{
	if (Distance(main, target) <= mainRadius + targetRadius) {
		return true;
	}
	else {
		return false;
	}
}
