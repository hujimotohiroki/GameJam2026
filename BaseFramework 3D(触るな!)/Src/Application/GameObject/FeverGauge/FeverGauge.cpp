#include "FeverGauge.h"

void FeverGauge::Init()
{
	if (!m_spGauge)
	{
		m_spGauge = std::make_shared<KdTexture>();
		m_spGauge->Load("Asset/Textures/UI/Gauge/Gauge.png");
	}
	if (!m_spGaugeFrame)
	{
		m_spGaugeFrame = std::make_shared<KdTexture>();
		m_spGaugeFrame->Load("Asset/Textures/UI/Gauge/GaugeFrame.png");
	}
}

void FeverGauge::Update()
{
	if (GetAsyncKeyState('W') & 0x8000) m_gauge += 0.05f;
	if (GetAsyncKeyState('S') & 0x8000) m_gauge -= 0.05f;
	m_gauge = std::clamp(m_gauge, 0.0f, m_gaugeMax);
}

void FeverGauge::DrawSprite()
{
	const float posX = 0.0f;
	const float posY = 0.0f;

	const int drawW = 100;
	const int drawH = 20;

	const float scale = 5.0f;
	// const float scaleX = 5.0f;
	// const float scaleY = 3.0f;

	float rate = m_gauge / m_gaugeMax;

	const int fillW = (int)drawW * rate;

	Math::Rectangle src;
	src.x = 0;
	src.y = 0;
	src.width  = (int)m_spGauge->GetWidth() * rate;
	src.height = m_spGauge->GetHeight();

	// 拡大後サイズ
	const int drawScaleW = (int)(drawW * scale);
	const int drawScaleH = (int)(drawH * scale);

	const int fillScaleW = (int)(fillW * scale);

	// ゲージ
	if (fillW > 0)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spGauge,
			(int)(posX + fillScaleW * 0.5f),
			(int)(posY),
			fillScaleW,
			drawScaleH,
			&src);
	}

	// 枠
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spGaugeFrame,
		(int)(posX + drawScaleW * 0.5f),(int)(posY),
		drawScaleW,drawScaleH);
}