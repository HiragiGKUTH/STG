#include "GameDefine.hpp"

#include "Player.hpp"
#include "Enemy.cpp"
#include <rnfs.h>

class Shot_p : public Task
{
private:
		//タスクシステム用
	TaskCall m_update;
	TaskCall m_draw;
	TaskSend m_sender;

	Vec2 m_pos;		//座標
	Vec2 m_vel;		//速度
	double m_SPEED;	//速さ
	double m_ang;	//角度
	Circle m_col;	//当たり判定半径

	int m_cnt;		//カウンタ
	int m_kind;		//挙動の種類
	bool m_hit;		//何かに当たったかどうかのフラグ
public:
	Shot_p(Vec2 pos,double speed,double ang,int kind) : Task()
		, m_pos(pos)
		, m_SPEED(speed)
		, m_ang(ang)
		, m_kind(kind)
		, m_update(this,&Shot_p::Update,CallGroup_Update)
		, m_draw(this,&Shot_p::Draw,CallGroup_Draw,CallPriority_Player_Shot)
	{
		m_sender.Register(this);
	}
private:
	void Update()
	{
		m_cnt++;
		m_vel = m_vel.Up;
		m_vel.rotate(m_ang);
		m_pos.moveBy(m_vel*m_SPEED);
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
	m_receiver.Register<Shot_e>(this,&Player::HitCheck);

	m_SPEED = 6.0;
	m_pos = Vec2(Window::Width() / 2, Window::Height() / 2);
	m_vel = Vec2(0, 0);
	m_col = Circle(m_pos, 24.0);
	m_anim = Rect(0, 0, 32, 32);	//仮
}

void Player::HitCheck(Shot_e & shot_e)
{
	if (this->m_col.intersects(shot_e.GetCol)) shot_e.SetDestroy();
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
	move *= shift ? 0.5 : 1.0;
	m_vel = Vec2(0, 0);
	m_cnt++;

		//移動ルーチン
	m_vel.x += right ? move : left ? -move : 0;			//キー入力で制御
	m_vel.y += down  ? move : up   ? -move : 0;
	m_vel = up && down    ? Vec2(m_vel.x, 0) : m_vel;	//左右、上下が同時に押されるなら止める
	m_vel = right && left ? Vec2(0, m_vel.y) : m_vel;
	m_pos += m_vel;										//実際の移動

		//ショット登録
	if (z && m_cnt%6 == 0) Create<Shot_p>(m_pos, 16.0,Radians(0),0);

	m_col = Circle(m_pos, 12.0);
}

void Player::Draw()
{
	m_col.draw(Palette::White);
}
