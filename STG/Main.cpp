#include <Siv3D.hpp>

#include "Manager.hpp"

void Main()
{
	Manager mygame;

	mygame.Init();

	while (System::Update())
	{
		mygame.Update_Draw();
	}
}
