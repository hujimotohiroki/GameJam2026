#include "Ice.h"
#include "../../Scene/SceneManager.h"
void Ice::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Ice.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

}

void Ice::Update()
{
	m_gravity -= m_gravityacc;
	m_pos += m_dir * m_speed;
	m_pos.y += m_gravity;
}

void Ice::PostUpdate()
{
	//レイ判定
	KdCollider::RayInfo ray;

	//レイの発射座標を設定
	ray.m_pos = m_pos;
	static const float enableStepHigh = 0.1f;//おそらく段差はないが計算のずれのために少しの段差なら超えれるようにしておく
	ray.m_pos.y += enableStepHigh;

	//レイの長さを設定
	ray.m_range = 0.1-m_gravity;

	//当たり判定をしたいタイプを設定
	ray.m_type = KdCollider::TypeGround;

	//デバッグ
	//m_pDebugWire->AddDebugSphere(Rearsphere.m_sphere.Center, Frontsphere.m_sphere.Radius);

	//球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retRayList;
	for (auto& obj : SceneManager::Instance().GetObjList()) {
		obj->Intersects(ray, &retRayList);
	}

	//球に当たったリストから一番近いオブジェクトを探す
	float maxOverlap = 0;
	bool hit = false;
	for (auto& ret : retRayList) {
		if (maxOverlap < ret.m_overlapDistance) {
			maxOverlap = ret.m_overlapDistance;
			m_pos = ret.m_hitPos;
			hit = true;
		}
	}
	if (hit)
	{
		m_gravity = 0;
		m_dir.y = 0;
		m_dir.Normalize();
	}
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	m_mWorld = scaleMat * transMat;
}

void Ice::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
