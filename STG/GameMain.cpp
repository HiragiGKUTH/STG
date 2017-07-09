#include "GameDefine.hpp"
#include "GameMain.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "BackGround.hpp"


GameMain::GameMain()
{
	
}

void GameMain::init()
{
	Create<Player>();
	Create<Enemy>();
	Create<BackGround>();
}

void GameMain::update()
{
	TaskCall::All::Update(CallGroup::CallGroup_Update);
}

void GameMain::draw() const
{
	TaskCall::All::Update(CallGroup::CallGroup_Draw);
}

