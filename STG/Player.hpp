#pragma once
#include <Siv3D.hpp>
#include <rnfs.h>

class Player
{
private:
	Vec2 m_pos;		//座標
	Vec2 m_vel;		//移動成分
	Circle m_col;	//当たり判定半径
	Rect m_anim;	//アニメーションのための物
	
	int cnt;		//カウンタ
	int state;		//状態
	int animcnt;	//アニメーション用カウンタ
	float SPEED;

		//プレイヤーショットのタスククラス
	class Shot;

public:
	Player();
	void Update();
	void Draw();
};