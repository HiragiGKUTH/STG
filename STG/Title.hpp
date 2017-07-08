#include "Define.hpp"

class Title : public MyGame::Scene
{
private:
	Array<Vec2> m_pos;
	Array<String> m_strings;
	int m_select;
	String m_title;
public:
	Title();
	void init() override;
	void update() override;
	void draw() const override;
};