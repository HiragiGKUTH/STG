#pragma once
#include <Siv3D.hpp>
#include <rnfs.h>

class Player : public Task
{
private:
	TaskCall m_update;
	TaskCall m_draw;
	TaskSend m_sender;
	TaskReceive m_receiver;

	Vec2 m_pos;		//座標
	Vec2 m_vel;		//移動成分
	Circle m_col;	//当たり判定半径
	Rect m_anim;	//アニメーションのための物
	
	int m_cnt;		//カウンタ
	int m_state;		//状態
	int m_animcnt;	//アニメーション用カウンタ
	float m_SPEED;

public:
	Player();
	void Update();
	void Draw();
};