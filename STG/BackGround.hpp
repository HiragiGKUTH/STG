#pragma once
#include <Siv3D.hpp>
#include <rnfs.h>

class BackGround : public Task
{
private:
	TaskCall m_update;
	TaskCall m_draw;
	
	Vec2 m_pos;
	Image m_img;
	Texture m_drawtex;
public:
	BackGround();
	void Update();
	void Draw();
};

