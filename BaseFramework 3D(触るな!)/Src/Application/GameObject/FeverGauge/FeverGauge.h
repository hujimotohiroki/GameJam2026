#pragma once

class FeverGauge : public KdGameObject
{
public:

	FeverGauge() {}
	~FeverGauge () override {}

	void Init() override;
	void Update() override;
	void DrawSprite() override;

private:

	std::shared_ptr<KdTexture> m_spGauge		= nullptr;
	std::shared_ptr<KdTexture> m_spGaugeFrame	= nullptr;

	float m_gauge = 0.0f;
	float m_gaugeMax = 1.0f;

};