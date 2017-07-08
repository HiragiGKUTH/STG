#include "Title.hpp"

Title::Title()
{

}

void Title::init()
{

		//タイトルに関して初期化
	m_title = L"弾幕を避けるゲーム";

		//項目に関して初期化
	m_select = 0;
	m_strings =
	{
		{L"弾幕を選ぶ"},
		{L"ミュージックルーム"},
		{L"コンフィグ"},
		{L"終了"},
	};
	for (size_t i = 0; i < m_strings.size(); i++)
	{
		Vec2 tmp;
		tmp.x = 100 + (i * 16);
		tmp.y = 320 + (i * (FontAsset(L"TitleSelect").height + 10));
		m_pos.push_back(tmp);
	}
}

void Title::update()
{
		//選択されている項目を右にズラす
	if (Input::KeyUp.clicked) m_select--;
	if (Input::KeyDown.clicked) m_select++;
	m_select %= m_strings.size();
	for(size_t i = 0;i < m_strings.size();i++)
	{
		if (i == m_select)
			m_pos[i].x = 100 + (i * 16) + 20;
		else
			m_pos[i].x = 100 + (i * 16);
	}
	
		//選択された項目によってシーンを切り替える
	if (Input::KeyZ.clicked)
	{
		switch (m_select)
		{
			case 0: changeScene(L"Select"); break;
			case 1: changeScene(L"MusicRoom"); break;
			case 2: changeScene(L"Option"); break;
			case 3: System::Exit(); break;
		}
	}
}

void Title::draw() const
{
	FontAsset(L"Title")(m_title).draw(100, 60, Palette::Aquamarine);
	for (size_t i = 0; i < m_strings.size(); i++)
		FontAsset(L"TitleSelect")(m_strings[i]).draw(m_pos[i]);
}