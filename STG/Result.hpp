#include "Define.hpp"

class Result : public MyGame::Scene
{
private:

public:
	Result();
	void init() override;
	void update() override;
	void draw() const override;
};