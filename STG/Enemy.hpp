#pragma once
#include <Siv3D.hpp>
#include <rnfs.h>

	//移動パターン
enum MovePattern{
	Sin,
	Cos,
};
	//ショットモード
enum e_ShotMode{
	Host,
	Child,
};

class Enemy : public Task
{
private:
		//タスク管理のための宣言
	TaskCall m_update;
	TaskCall m_draw;
	TaskSend m_sender;
	TaskReceive m_receiver;
		//敵に関するデータ
	Vec2 m_pos;			//座標
	Vec2 m_vel;			//速度
	Vec2 m_acc;			//加速度
	Circle m_col;		//あたり判定半径
	Rect m_anim;		//アニメーション用変数
	int m_hp;			//体力
	int m_kind;			//弾幕ID格納変数
	int m_cnt;			//カウンタ
	int m_state;		//状態
	int m_pattern_cnt;	//パターン内カウンタ
	int m_pattern_len;	//パターンの1ループのフレーム数
	int m_pattern_seek;	//現在のパターンを指し示す変数
	bool m_pattern_loop;//パターンはループするか否かを示す変数
	int m_pattern_tmp;	//一時的に保持するための変数

		//移動データの構造体
	typedef struct movedata_t {
		int type;		//移動方法
		int start;		//移動開始フレーム
		int dur;		//移動完了までのフレーム数
		Vec2 target;	//移動先の座標
		double a;		//移動時の加速度
		double vo;		//移動時の初速度
	}MoveData;
		//移動データの配列
	Array<MoveData> m_movedata;
private:
	void InitPattern();
	void ManagePattern();
	void Move(MoveData arg);
public:
	Enemy(int kind);
	void Update();
	void Draw();
};
