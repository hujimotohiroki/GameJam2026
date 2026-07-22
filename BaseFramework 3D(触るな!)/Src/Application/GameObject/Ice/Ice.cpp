#include "Ice.h"
#include "../../Scene/SceneManager.h"
void Ice::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Ice.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Ice::Update()
{
	/*if (m_isGrab)
	{
		m_scale *= 0.99f;
		if (m_scale < 0.01f)
		{
			m_isExpired = true;
			m_isGrab = false;
		}
	}*/
	m_gravity -= m_gravityAcc;
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
	ray.m_range = 0.1 - m_gravity;

	//当たり判定をしたいタイプを設定
	ray.m_type = KdCollider::TypeGround;

	//レイに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retRayList;
	for (auto& obj : SceneManager::Instance().GetObjList()) {
		obj->Intersects(ray, &retRayList);
	}

	//レイに当たったリストから一番近いオブジェクトを探す
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

	//スフィア判定
	KdCollider::SphereInfo sphere;

	//スフィアの中心座標を設定
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Radius = 0.1f;

	//デバッグ
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeEvent;//おばあちゃん近くの判定タイプと同一にする


	for (auto& obj : SceneManager::Instance().GetObjList()) {
		if (obj->Intersects(sphere, nullptr))//球に当たったオブジェクトがあるなら
		{
			//スコア加算

			//氷を消す
			m_isExpired = true;
		}
	}

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	m_mWorld = scaleMat * transMat;
}

void Ice::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
