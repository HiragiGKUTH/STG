#pragma once
#include <Siv3D.hpp>
#include <rnfs.h>

	//移動パターン用Enum
enum MovePattern
{
	Linier,
	Sin,
};

class Enemy : public Task
{
private:
		//タスク管理のための宣言
	TaskCall m_update;
	TaskCall m_draw;
	TaskSend m_sender;
	TaskReceive m_receiver;
		//敵に関するデータ
	Vec2 m_pos;
	Vec2 m_vel;
	Circle m_col;
	Rect m_anim;
	int m_hp;

	int cnt;
	int state;

		//敵の行動パターンのための構造体
	typedef struct pattern
	{
		int timing;
		int kind;
		Vec2 pos;
	}t_MovePattern;

	Array<t_MovePattern> movepattern;
private:
	void Init_Pattern();
public:
	Enemy();
	void Update();
	void Draw();
};
