#pragma once

//********************************************************
// インスタンス生成時にタイマーの時間を設定する
// weak_ptr でタイマーを所持するシーンがタイマーの状態を取得することができる
// 
// 左上揃えになってるけど、使ってる画像が上下に幅があるせいで
// 思うような挙動にならないので、描画位置を調整する必要がある
//********************************************************

class Timer :public KdGameObject
{
public:

	// タイマーの時間を設定する
	Timer(float time);
	~Timer()								override = default;

public:
	// === 基本ライフサイクル ===========================================
	void Init()								override;
	void Update()							override;
	void DrawSprite()						override;
	// ===============================================================

public:
	// === 外部から状態の取得・操作 ======================================
	enum class State
	{
		Running,	// タイマーが動作中
		Stopped,	// タイマーが停止中
		TimeUp,		// タイムアップ
	};
	float GetTime()		const { return m_time; }
	State GetState()	const { return m_state; }
	void RequestStop() { m_state = State::Stopped; }
	void RequestStart() { m_state = State::Running; }
	// ===============================================================

public:
	// === ゲッターセッター群 ===========================================
	void SetPos(const Math::Vector3& pos)	override;
	Math::Vector3 GetPos() const			override;
	void SetColor(const Math::Color& color) { m_drawColor = color; }
	Math::Color GetColor() const { return m_drawColor; }
	// ===============================================================

private:
	// === 内部関数群 ==================================================
	void DrawNumber(const std::string& numberText);	// 数字の描画
	// ===============================================================

private:
	// ==== メンバ変数 =================================================
	float						m_time = 0.0f;							// タイマーの時間
	State						m_state = State::Running;				// タイマーの状態
	std::shared_ptr<KdTexture>	m_spNumbersTexture;						// 数字のテクスチャ
	Math::Vector2				m_drawPos{};							// 描画位置
	Math::Color					m_drawColor{ 1.0f, 1.0f, 1.0f, 1.0f };	// 描画色
	// ===============================================================

	// === 定数宣言（画像変更があった場合ここを対応させる） ==================

	// スプライトシート内の数字1つ分のサイズ
	static constexpr int kSrcWidth = 205;
	static constexpr int kSrcHeight = 512;

	// 実際に画面へ表示するサイズ
	static constexpr int kDrawWidth = 80;
	static constexpr int kDrawHeight = 200;

	// 数字同士の間隔
	static constexpr int kSpace = 5;
	// ===============================================================
};