#include "Player.h"
#include"../../Scene/SceneManager.h"
#include"../Ice/Ice.h"

void Player::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Data/Texture/male_hero_free/male_hero.png");

	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon->SetSplit(10, 8);

	m_animeInfo.start = 10;		// 開始コマ
	m_animeInfo.end = 19;		// 終了コマ
	m_animeInfo.count = 0;		// 現在のカウント数
	m_animeInfo.speed = 0.2f;	// アニメーションの速度
}

void Player::Update()
{
	UINT oldDirType = m_animType;		// 前回の方向タイプを保存しておく
	if (oldDirType == m_animType)
	{
		m_animType = 0;					//ビット列をクリア
	}

	if (m_moveFlg == true)
	{
		m_animType |= AnimType::Move;
	}
	else
	{
		m_animType |= AnimType::Idle;
	}

	if (m_animType != 0 && m_animType != oldDirType)
	{
		ChangeAnimation();
	}
	else
	{
		m_animType = oldDirType;
	}

	m_animeInfo.count += m_animeInfo.speed;
	int animeCnt = static_cast<int>(m_animeInfo.start + m_animeInfo.count);

	if (animeCnt > m_animeInfo.end)
	{
		animeCnt = m_animeInfo.start;
		m_animeInfo.count = 0;
	}

	m_polygon->SetUVRect(animeCnt);

	m_dir = {};

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_moveFlg = true;
		m_dir = { -1,0,0 };
		m_scale.x = -1.0f;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_moveFlg = true;
		m_dir = { 1,0,0 };
		m_scale.x = 1.0f;
	}
	else
	{
		m_moveFlg = false;
	}

	if (GetAsyncKeyState('T') & 0x8000)
	{
		std::shared_ptr<Ice> ice;
		ice = std::make_shared<Ice>();
		ice->Init();
		ice->SetState(m_pos + Math::Vector3(0, 0.15, 0), m_dir, m_speed);
		SceneManager::Instance().AddObject(ice);
	}

	m_pos += m_dir * m_speed;

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

//アニメーションの切替
void Player::ChangeAnimation()
{
	m_animeInfo.count = 0;
	m_animeInfo.speed = 0.2f;

	if (m_animType & AnimType::Idle)
	{
		m_animeInfo.start = 10;		// 開始コマ
		m_animeInfo.end = 19;		// 終了コマ
	}
	if (m_animType & AnimType::Move)
	{
		m_animeInfo.start = 30;		// 開始コマ
		m_animeInfo.end = 39;		// 終了コマ
	}
}
