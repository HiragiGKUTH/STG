#include "GameDefine.hpp"

#include "Player.hpp"
#include <rnfs.h>

class Shot_p : public Task
{
private:
	Vec2 m_pos;
	Vec2 m_vel;
	double SPEED;
	Circle m_col;
	TaskCall m_update;
	TaskCall m_draw;

	int m_kind;
public:
	Shot_p(Vec2 pos,double speed,int kind) : Task()
		, m_pos(pos)
		, m_kind(kind)
		, m_update(this,&Shot_p::Update,CallGroup_Update)
		, m_draw(this,&Shot_p::Draw,CallGroup_Draw,CallPriority_Player_Shot)
		, SPEED(speed){}
private:
	void Update()
	{
		m_vel = Vec2(0, -SPEED);
		m_pos += m_vel;
		m_col = Circle(m_pos, 8.0);
		if (m_pos.y < 0) this->Destroy();
	}

	void Draw()
	{
		m_col.draw(Palette::Azure);
	}
};

Player::Player() : Task()
	, m_update(this, &Player::Update,CallGroup_Update)
	, m_draw(this, &Player::Draw,CallGroup_Draw,CallPriority_Player)
{
	m_sender.Register(this);

	m_SPEED = 6.0;
	m_pos = Vec2(Window::Width() / 2, Window::Height() / 2);
	m_vel = Vec2(0, 0);
	m_col = Circle(m_pos, 24.0);
	m_anim = Rect(0, 0, 32, 32);	//仮
}

void Player::Update()
{
		//初期設定
	bool right = Input::KeyRight.pressed;
	bool left  = Input::KeyLeft.pressed;
	bool down  = Input::KeyDown.pressed;
	bool up    = Input::KeyUp.pressed;
	bool z	   = Input::KeyZ.pressed;
	bool shift = Input::KeyShift.pressed;
	double move = (right && (up || down)) || (left && (up || down)) ? m_SPEED*0.71 : m_SPEED;
	move *= shift ? 0.4 : 1.0;
	m_vel = Vec2(0, 0);
	m_cnt++;

		//移動ルーチン 要改善
	if (right)			m_vel = Vec2(move, 0);
	if (left)			m_vel = Vec2(-move, 0);
	if (up)				m_vel = Vec2(0, -move);
	if (down)			m_vel = Vec2(0, move);
	if (right && up)	m_vel = Vec2(move, -move);
	if (right && down)	m_vel = Vec2(move, move);
	if (left && up)		m_vel = Vec2(-move, -move);
	if (left && down)	m_vel = Vec2(-move, move);
		//左右、上下が同時に押されるなら止める
	if (up && down)		m_vel = Vec2(m_vel.x, 0);
	if (right && left)	m_vel = Vec2(0, m_vel.y);
		//実際の移動
	m_pos += m_vel;

		//ショット登録
	if (z && m_cnt%6 == 0) Create<Shot_p>(m_pos, 16.0,0);

	m_col = Circle(m_pos, 24.0);
}

void Player::Draw()
{
	m_col.draw(Palette::White);
}
