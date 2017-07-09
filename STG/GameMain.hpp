#pragma once

#include "Define.hpp"

class GameMain : public MyGame::Scene
{
private:

public:
	GameMain();
	void init() override;
	void update() override;
	void draw() const override;
};