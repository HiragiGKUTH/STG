#include "Enemy.hpp"
#include "GameDefine.hpp"
#include <cmath>

class Shot_e : public Task
{
private:
    TaskCall m_update;
    TaskCall m_draw;
    TaskSend m_sender;

	Vec2 m_pos;
	Vec2 m_vel;
	double m_SPEED;
    double m_ang;
	Circle m_col;
	int m_kind;
public:
	Shot_e(Vec2 pos, double speed, double ang, int kind) : Task()
		, m_pos(pos)
		, m_SPEED(speed)
        , m_kind(kind)
        , m_ang(ang)
		, m_update(this,&Shot_e::Update,CallGroup_Update)
		, m_draw(this,&Shot_e::Draw,CallGroup_Draw,CallPriority_Enemy_Shot){}
private:
	void Update()
	{
		m_vel.x = cos(m_ang);
		m_vel.y = sin(m_ang);
		m_pos += m_vel*m_SPEED;
		m_col = Circle(m_pos, 4.0);
		if (m_pos.y < 0 || Window::Height() < m_pos.y
			|| m_pos.x < 0 || Window::Width() < m_pos.x) {
			this->Destroy();
		}
	}

	void Draw()
	{
		m_col.draw(Palette::White);
	}
};

Enemy::Enemy(int kind) : Task()
    , m_update(this, &Enemy::Update,CallGroup_Update)
    , m_draw(this, &Enemy::Draw,CallGroup_Draw,CallPriority_Enemy)
{
    m_pos = Vec2(Window::Width()/2,120);
    m_vel = Vec2(0,0);
    m_col = Circle(m_pos,16.0);
    m_anim = Rect(0,0,32,32);
	m_kind = kind;
    m_cnt = 0;
	m_pattern_cnt = 0;
	m_pattern_seek = 0;
	m_pattern_tmp = 0;
	m_pattern_loop = false;
    m_state = 0;
		//行動パラメータを読み込み、設定
    InitPattern();
}

void Enemy::InitPattern(){
	MoveData tmp;						//プッシュ用
	CSVReader pattern(L"Assets/csv/EnemyMovePattern.csv");
	const int DATAROW = 6;				//一つのデータの大きさ
	size_t row = DATAROW * m_kind + 1;	//列を参照すべき位置に移動させる
	size_t column = 1;

		//データの終端まで読み込み
	for (auto j : step(pattern.columns(row)-1)){
		j++;
		tmp.start = pattern.get<int>(row, j);	//開始フレーム
		tmp.dur = pattern.get<int>(row+1, j);	//移動時間
			//移動先の座標を指定
		if (pattern.get<String>(row + 2, j) == L"UpperRnd")	//上半分のランダムな位置
			tmp.target = RandomVec2(Window::Width(), Window::Height() / 2);
		if (pattern.get<String>(row + 2, j) == L"Rand")		//画面全体のランダムな位置
			tmp.target = RandomVec2(Window::Width(), Window::Height());
		if (pattern.get<String>(row + 2, j) == L"Center")	//画面中央
			tmp.target = Vec2(Window::Width()/2, Window::Height()/2);
			//移動方法を設定
		tmp.type = pattern.get<String>(row + 3, j) == L"sin" ? MovePattern::Sin : MovePattern::Cos;
		
			//移動全体のフレーム数を足していく
		m_pattern_len = tmp.start + tmp.dur;
		m_movedata.push_back(tmp);
	}
	m_pattern_loop = pattern.get<String>(row + 4, 1) == L"TRUE" ? true : false;
}

void Enemy::Update(){
	ManagePattern();

    m_col = Circle(m_pos,16.0);
    m_cnt++;
}

void Enemy::ManagePattern(){
		//弾幕パターン制御
	switch (m_kind){
		case 0:{	//テスト弾幕1 さとり妖怪のアレ
			if (m_cnt % 1 == 0) {
				int way = 4;
				for (int i = 0; i < way; i++)
					Create<Shot_e>(m_pos, (double)(m_cnt % 30)/40 + 2, Radians((360 / way)*i)+Radians(m_cnt), 0);
			}
			break;
		}
		case 1:{	//テスト弾幕2 分からん。
			if (m_cnt % 1 == 0) {
				int way = 4;
				for (int i = 0; i < way; i++)
					Create<Shot_e>(m_pos, (double)(m_cnt % 30) / 40 + 2, Radians((360 / way)*i)+m_cnt*0.3, 0);
			}
			break;
		}
		case 2: {
			//ココに追加
			break;
		}
		case 3: {
			//ココに追加
			break;
		}
		case 4: {
			//ココに追加
			break;
		}
		case 5: {
			//ココに追加
			break;
		}
		case 6: {
			//ココに追加
			break;
		}
		case 7: {
			//ココに追加
			break;
		}
	}

		//移動制御
	if (m_pattern_loop) {
		m_pattern_cnt %= m_pattern_len;
		if (m_pattern_seek >= m_movedata.size() - 1) {
			m_pattern_seek = 0;
			m_pattern_cnt = 0;
			m_pattern_tmp = 0;
		}
	}//アニメーションループが有効ならば戻す


		//移動開始時間になったらtmpを初期化
	if (m_pattern_cnt == m_movedata[m_pattern_seek].start) m_pattern_tmp = 0;
		//経過時間が移動時間に等しくなったら(=移動が終了したら)seekをすすめる
	if (m_pattern_tmp == m_movedata[m_pattern_seek].dur) m_pattern_seek++;
		//もし現在のフレーム数が移動すべき時間内であれば,移動させる
	if (m_movedata[m_pattern_seek].start <= m_pattern_cnt && m_pattern_cnt < m_movedata[m_pattern_seek].start + m_movedata[m_pattern_seek].dur)
		Move(m_movedata[m_pattern_seek],m_pattern_tmp);

	Println(m_pattern_cnt , L" Animation count");
	Println(m_pattern_tmp , L" Template count");
	Println(m_pattern_seek , L" Seek count");
	Println(m_movedata[m_pattern_seek].start , L" startframe");
	Println(m_movedata[m_pattern_seek].dur , L" durationframe");
	m_pattern_cnt++;	//アニメーション用カウンタ
	m_pattern_tmp++;	//アニメーション内一時格納用(アニメーション開始からの経過フレーム数の格納用)
}

void Enemy::Move(MoveData arg,int pastframe)
{
	double distX = arg.target.x - m_pos.x;
	double distY = arg.target.y - m_pos.y;

	m_pos.x += distX / 20;
	m_pos.y += distY / 20;
}

void Enemy::Draw()
{
    m_col.draw(Palette::Aqua);
}
