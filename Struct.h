#pragma once


//プレイ画面の横幅
const int kPlayWindouWidth = 488;

//UI画面の横幅
const int kUiWindouWidth = 200;

//UIとプレイ画面の横幅を全体の横幅とする
const int kWindowWidth = kPlayWindouWidth + kUiWindouWidth;

//画面の立幅
const int kWindowHeight = 800;

//プレイヤーの弾のMAX数
const int kMaxPlayerBullet = 32;

//敵の弾のMAX数
const int kMaxEnemyBullet = 4;

//敵のMAX数
const int kMaxEnemyAmount = 64;

struct Vector2 {
	float x;
	float y;
};
struct Matrix2x2 {
	float m[2][2];
};

struct Matrix3x3 {
	float m[3][3];
};

enum NowScene {
	TITLE,
	PLAY,
};

enum Select {
	MENU,
	ENDLESS,
	SCORE,
};