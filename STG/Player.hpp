#pragma once
#include <Siv3D.hpp>

class Player
{
private:
	Vec2 m_pos;
public:
	Player();
	void Update();
	void Draw();
};