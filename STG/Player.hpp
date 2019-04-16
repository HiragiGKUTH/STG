#pragma once
#include <Siv3D.hpp>
#include <rnfs.h>

enum p_ShotKind
{
	Straight,
	Traciking,
};

class Player : public Task
{
private:
	TaskCall m_update;
	TaskCall m_draw;
	TaskSend m_sender;
	TaskReceive m_receiver;

	Vec2 m_pos;		//���W
	Vec2 m_vel;		//�ړ�����
	Circle m_col;	//�����蔻�蔼�a
	Rect m_anim;	//�A�j���[�V�����̂��߂̕�
	
	int m_cnt;		//�J�E���^
	int m_state;		//���
	int m_animcnt;	//�A�j���[�V�����p�J�E���^
	float m_SPEED;

public:
	Player();
	void Update();
	void Draw();
	void HitCheck(Shot_e & shot_e);
};