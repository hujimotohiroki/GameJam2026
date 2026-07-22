#pragma once

#include"../BaseScene/BaseScene.h"

class Timer;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init()  override;

private:
	// タイマーの弱参照
	std::weak_ptr<Timer> m_wpTimer;
};
