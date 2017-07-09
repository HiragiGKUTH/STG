#pragma once
#include <Siv3D.hpp>
#include <rnfs.h>

class Enemy : public Task
{
private:
	Vec2 m_pos;
public:
	Enemy();
	void Update();
	void Draw();
};