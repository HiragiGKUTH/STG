#pragma once

enum CallGroup
{
	CallGroup_Update,
	CallGroup_Draw,
};

enum CallPriority
{
	CallPriority_Enemy,
	CallPriority_Enemy_Shot,
	CallPriority_Player,
	CallPriority_Player_Shot,
	CallPriority_BackGround,
};
