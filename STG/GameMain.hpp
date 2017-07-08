#include "Define.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "BackGround.hpp"

class GameMain : public MyGame::Scene
{
private:
	Player *m_player;
	Enemy *m_enemy;
	BackGround *m_background;

public:
	GameMain();
	void init() override;
	void update() override;
	void draw() const override;
};