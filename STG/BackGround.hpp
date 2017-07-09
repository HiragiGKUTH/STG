#pragma once
#include <Siv3D.hpp>
#include <rnfs.h>

class BackGround : public Task
{
private:
	Vec2 m_pos;
public:
	BackGround();
	void Update();
	void Draw();
};

