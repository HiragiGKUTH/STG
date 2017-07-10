#include "Enemy.hpp"
#include "GameDefine.hpp"
#include <math.h>

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
	int m_kind;
public:
	Shot_e(Vec2 pos, double speed, double ang, int kind) : Task()
		, m_pos(pos)
		, m_SPEED(speed)
        , m_kind(kind)
        , m_ang(ang)
		, m_update(this,&Shot_e::Update,CallGroup_Update)
		, m_draw(this,&Shot_e::Draw,CallGroup_Draw,CallPriority_Enemy_Shot){}
private:
	void Update()
	{
		m_vel.x = cos(m_ang);
		m_vel.y = sin(m_ang);
		m_pos += m_vel*m_SPEED;
		m_col = Circle(m_pos, 4.0);
		if (m_pos.y < 0 || Window::Height() < m_pos.y
			|| m_pos.x < 0 || Window::Width() < m_pos.x) {
			this->Destroy();
		}
	}

	void Draw()
	{
		m_col.draw(HSV((int)(m_ang*10)%360));
	}
};

Enemy::Enemy() : Task()
    , m_update(this, &Enemy::Update,CallGroup_Update)
    , m_draw(this, &Enemy::Draw,CallGroup_Draw,CallPriority_Enemy)
{
    m_pos = Vec2(Window::Width()/2,120);
    m_vel = Vec2(0,0);
    m_col = Circle(m_pos,16.0);
    m_anim = Rect(0,0,32,32);
    cnt = 0;
    state = 0;

    Init_Pattern();
}

void Enemy::Init_Pattern()
{
    switch(0)
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
	int shot_cnt = 0;
   // m_vel.x = cos(cnt*0.03)*2;
    //m_pos += m_vel;
    m_col = Circle(m_pos,16.0);
    cnt++;
        //適当なタイミングで弾幕を追加
	if (cnt % 1 == 0)
	{
		double t_ang = 0.03*cnt;
		double t_speed = (double)(cnt % 10) / 20 + 3;
		const int way = 10;
		for (int i : step(way))
		{
			shot_cnt += 2;
			double c_ang = t_ang + (TwoPi / way)*i + t_ang/4;
			double rev_c_ang = -c_ang + t_ang/4;
			Create<Shot_e>(m_pos, t_speed, c_ang, 0);
			Create<Shot_e>(m_pos, t_speed, rev_c_ang, 0);
		}
	}
}

void Enemy::Draw()
{
    m_col.draw(Palette::Aqua);
}
