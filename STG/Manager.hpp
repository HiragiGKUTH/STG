#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "Define.hpp"

class Manager
{
private:
	MyGame scene;

public:
	Manager() {}

	bool Init();
	bool Update_Draw();
};