#include "Enemy.hpp"
#include <math>

class Shot_e : public Task
{
private:
    TaskCall m_update;
    TaskCall m_draw;
    TaskSend m_sender;

	Vec2 m_pos;
	Vec2 m_vel;
	double m_SPEED;
    double m_ang;
	Circle m_col;
public:
	Shot_e() {}
	Shot_e(Vec2 pos,double speed,double ang,int kind) : Task()
		, m_pos(pos)
        , m_kind(kind)
        , m_ang(ang)
		, m_update(this,&Shot::Update,CallGroup_Update)
		, m_draw(this,&Shot::Draw,CallGroup_Draw,CallPriority_Player_Shot)
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
Enemy::Enemy() : Task()
    , m_update(this, &Player::Update,CallGroup_Update)
    , m_draw(this, &Player::Draw,CallGroup_Draw,CallPriority_Enemy)
{
    m_pos = Vec2(Window::width(),120);
    m_vel = Vec2(0,0);
    m_col = Circle(m_pos,16.0);
    m_rect = Rect(0,0,32,32);
    cnt = 0;
    state = 0;

    Init_Pattern();
}

void Enemy::Init_Pattern()
{
    switch(m_data->ID)
    {
        case 0:
        {
            break;
        }

        case 1:
        {
            break;
        }

        case 2:
        {
            break;
        }

        case 3:
        {
            break;
        }

        default:
         break;
    }
}

void Enemy::Update()
{
    m_vel.x = sin(cnt)*400;
    m_pos += m_vel;
    m_col = Vec2(m_pos,16.0);
    cnt++;
        //適当なタイミングで弾幕を追加
    if(cnt%6 == 0) Create<Shot_e>(m_pos,m_SPEED,0.01*cnt,0);
}

void Enemy::Draw()
{
    m_col.draw();
}
