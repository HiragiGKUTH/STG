#pragma once

enum CallGroup
{
	CallGroup_Update,
	CallGroup_Draw,
};

enum CallPriority
{
	CallPriority_BackGround,
	CallPriority_Player_Shot,
	CallPriority_Player,
	CallPriority_Enemy_Shot,
	CallPriority_Enemy,
};
