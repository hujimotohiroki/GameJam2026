#include "GameScene.h"
#include"../SceneManager.h"
#include"../../GameObject/`Player/Player.h"
#include"../../GameObject/Ice/Ice.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('P') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	player->Init();
	m_objList.push_back(player);
	std::shared_ptr<Ice> ice;
	ice = std::make_shared<Ice>();
	ice->Init();
	m_objList.push_back(ice);
}
