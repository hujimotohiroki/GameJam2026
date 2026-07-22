#pragma once

class Player : public KdGameObject
{
public:

	enum AnimType
	{
		Idle = 1 << 0,	// 通常　0000 0001
		Move = 1 << 1,	// 移動　0000 0010
	};

	// アニメーション情報
	struct AnimationInfo
	{
		int   start;	// 開始コマ
		int   end;		// 終了コマ
		float count;	// 現在のカウント数
		float speed;	// アニメーションの速度
	};

	Player() {}
	~Player() {}

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:

	//アニメーションの切替
	void ChangeAnimation();

	std::shared_ptr<KdSquarePolygon> m_polygon;

	AnimationInfo m_animeInfo;

	UINT m_animType = 0;

	Math::Vector3 m_pos = { 0,-1,0 };
	Math::Vector3 m_move = { 0,0,0 };
	Math::Vector3 m_scale = { 1,1,1 };

	bool m_moveFlg = false;

};