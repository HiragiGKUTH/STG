#include <Siv3D.hpp>
#include <HamFramework.hpp>

#pragma once
struct CommonData
{
	int g_cnt = 0;	//ゲーム全体のカウンタ
	int ID;			//撃つべき弾幕の情報
					//ウィンドウ情報
	const int WINDOW_X = 1280;
	const int WINDOW_Y = 720;
};

using MyGame = SceneManager<String, CommonData>;