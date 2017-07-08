#include "Player.hpp"
#include <rnfs.h>

class Shot : public Task
{
private:
	Vec2 m_pos;
	Circle m_col;
public:
	Shot() {}
	Shot(Vec2 pos) : Task()
		, m_pos(pos) {}

};

Player::Player()
{
	SPEED = 6.0;
	m_pos = Vec2(Window::Width() / 2, Window::Height() / 2);
	m_vel = Vec2(0, 0);
	m_col = Circle(m_pos, 3.0);
	m_anim = Rect(0,0,32,32);	//仮
}

void Player::Update()
{
		//移動ルーチン 要改善
	bool right = Input::KeyRight.pressed;
	bool left  = Input::KeyLeft.pressed;
	bool down  = Input::KeyDown.pressed;
	bool up    = Input::KeyUp.pressed;
	double move = (right && (up || down)) || (left && (up || down)) ? SPEED*0.71 : SPEED;

	m_vel = Vec2(0, 0);

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

	m_pos += m_vel;

	m_col = Circle(m_pos, 3.0);
}

void Player::Draw()
{
	m_col.draw(Palette::White);
}
