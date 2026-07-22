#pragma once

class Ice :public KdGameObject
{
public:
	Ice() {};
	~Ice() override {};
	void Init() override;
	void Update() override;
	void PostUpdate() override;
	void DrawLit() override;

	void SetState(Math::Vector3 pos,Math::Vector3 dir,float speed)		// プレイヤーからの移動方向と速度の設定
	{
		m_pos = pos;
		m_dir = dir; 
		m_speed = speed;
	} 
	bool GetIsGrab() { return m_isgrab; }				// 氷に当たり判定があるかどうか
	void SetIsGrab(bool isgrab) { m_isgrab = isgrab; }  // 掴むんだり離したりしたときの当たり判定の変化
private:

	std::shared_ptr<KdSquarePolygon> m_polygon;

	Math::Vector3 m_pos = Math::Vector3::Zero;	// 現在の座標
	Math::Vector3 m_dir = Math::Vector3::Zero;	// 移動方向

	Math::Vector3 m_scale = { 0.5,0.5,0.5 };
	
	float m_speed = 0.0f;						// 移動速度
	bool  m_isgrab = false;						//現在掴まれているかの判定
	float m_gravity = 0.0f;						//重力
	const float m_gravityAcc = 0.008f;			//重力加速度
};