#include "Manager.hpp"

Select::Select()
{

}

void Select::init()
{
		//ID,name,difficulity,clear
	m_items =
	{
		Item{ 0,L"テスト弾幕1",1,false },
		Item{ 1,L"テスト弾幕2",2,false },
		Item{ 2,L"テスト弾幕3",2,false },
		Item{ 3,L"テスト弾幕4",5,false },
	};

	for (auto i : step(m_items.size()))
	{
		Vec2 tmp;
		tmp.x = left_border;
		tmp.y = upper_border + (i * FontAsset(L"SelectItems").height);
		m_pos.push_back(tmp);
	}
}

void Select::update()
{
	//選択されている項目を右にズラす
	if (Input::KeyUp.clicked) m_select--;
	if (Input::KeyDown.clicked) m_select++;
	m_select %= m_items.size();
	for (auto i : step(m_items.size()))
	{
		if (i == m_select)
			m_pos[i].x = left_border - 10;
		else
			m_pos[i].x = left_border;
	}
		//項目が確定されたら弾幕情報を記録してシーンチェンジ
	if (Input::KeyZ.clicked)
	{
		m_data->ID = m_items[m_select].ID;
		changeScene(L"GameMain");
	}
}

void Select::draw() const
{
	for (auto i : step(m_items.size()))
		FontAsset(L"SelectItems")(m_items[i].name).draw(m_pos[i]);
}