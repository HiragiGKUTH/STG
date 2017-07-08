#include "GameMain.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "BackGround.hpp"


GameMain::GameMain()
{
	m_player = new Player();
	m_enemy = new Enemy();
	m_background = new BackGround();
}

void GameMain::init()
{

}

void GameMain::update()
{
	m_background->Update();
	m_enemy->Update();
	m_player->Update();
}

void GameMain::draw() const
{
	m_background->Draw();
	m_enemy->Draw();
	m_player->Draw();
}

