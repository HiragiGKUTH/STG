#include "Define.hpp"

class Select : public MyGame::Scene
{
private:
	//€–Ú‚Ì—v‘f
	typedef struct item_tag {
		int ID;
		String name;
		int diff;
		bool clear;
	}Item;

	//•¡”‚Ì’e–‹‚ğì¬—\’è‚È‚Ì‚Å”z—ñ‚É‚·‚éB
	Array<Item> m_items;
	Array<Vec2> m_pos;
	int m_select;
	const int left_border = 120;
	const int upper_border = 80;
public:
	Select();
	void init() override;
	void update() override;
	void draw() const override;
};
