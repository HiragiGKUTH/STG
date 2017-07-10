#include "BackGround.hpp"
#include "GameDefine.hpp"

BackGround::BackGround() : Task()
	, m_update(this,&BackGround::Update,CallPriority_BackGround)
	, m_draw(this,&BackGround::Draw,CallGroup_Draw,CallPriority_BackGround)
{
	m_pos = Vec2(0, 0);
	m_img.resize(Window::Size());
}

void BackGround::Update()
{
	m_pos.y++;
//	m_drawtex = Texture(m_img);
}

void BackGround::Draw()
{
	FontAsset(L"SelectItem")(L"BackGround Class Enables").drawAt(Window::Width() / 2, Window::Height() / 2);
}
