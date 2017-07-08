#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Manager.hpp"

#include "Title.hpp"
#include "Select.hpp"
#include "GameMain.hpp"
#include "Result.hpp"

bool Manager::Init()
{
	//System Setting
	Window::Resize(1280, 720);

	//Register Assets
	FontAsset::Register(L"Title", 64);
	FontAsset::Register(L"TitleSelect", 32);
	FontAsset::Register(L"SelectItems", 14);


	//Add scenes
	scene.add<Title>(L"Title");
	scene.add<Select>(L"Select");
	return true;
}

bool Manager::Update_Draw()
{
	scene.updateAndDraw();
	return true;
}