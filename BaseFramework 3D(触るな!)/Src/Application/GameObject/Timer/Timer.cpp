#include "Timer.h"
#include "../../main.h"

Timer::Timer(float time)
{
	// タイマーの時間を設定
	m_time = time;
}

void Timer::Init()
{
	// 初回　Init() でのみロードする
	if (!m_spNumbersTexture)
	{
		m_spNumbersTexture = KdAssets::Instance().m_textures.GetData("Asset/Textures/UI/Numbers.png");
	}
}

void Timer::Update()
{
	// タイマーが停止中、またはタイムアップの場合は処理しない
	if (m_state == State::Stopped || m_state == State::TimeUp)return;

	// デルタタイム取得
	const float _deltaTime = Application::Instance().GetDeltaTime();

	// 0秒になるまで時間を減らす
	if (m_time > 0.0f)
	{
		m_time -= _deltaTime;

		if (m_time < 0.0f)
		{
			m_time = 0.0f;
		}
	}
	else
	{
		m_state = State::TimeUp;
	}
}

void Timer::DrawSprite()
{
	// タイマーを切り上げで文字列に変換
	std::string _timeText = std::to_string(static_cast<int>(std::ceil(m_time)));

	// テクスチャ描画
	DrawNumber(_timeText);
}

void Timer::DrawNumber(const std::string& numberText)
{
	// 描画開始位置
	int _drawX = static_cast<int>(m_drawPos.x);
	int _drawY = static_cast<int>(m_drawPos.y);

	// 1文字ずつ描画
	for (char c : numberText)
	{
		// 数字以外なら描画しない
		if (c < '0' || c > '9')continue;

		// '0'～'9'を 0～9 の数値へ変換
		const int _number = c - '0';

		// スプライトシートから切り抜く範囲
		Math::Rectangle _srcRect =
		{
			_number * kSrcWidth,
			0,
			kSrcWidth,
			kSrcHeight
		};

		// 描画
		KdShaderManager::Instance().m_spriteShader.DrawTex(
			m_spNumbersTexture,	// 描画するテクスチャ
			_drawX,				// 描画位置X
			_drawY,				// 描画位置Y
			kDrawWidth,			// 描画サイズ幅
			kDrawHeight,		// 描画サイズ高さ
			&_srcRect,			// スプライトシートから切り抜く範囲
			&m_drawColor,		// 描画色
			{ 0.0f, 1.0f }		// 基準点(左上)
		);

		// 次の数字の描画位置へ移動
		_drawX += kDrawWidth + kSpace;
	}
}

void Timer::SetPos(const Math::Vector3& pos)
{
	m_drawPos = Math::Vector2(pos.x, pos.y);
}

Math::Vector3 Timer::GetPos() const
{
	return Math::Vector3(m_drawPos.x, m_drawPos.y, 0.0f);
}