#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaSceneManager.h"
#include "yuzinnaPlayScene.h"
#include "yuzinnaTitleScene.h"
#include "yuzinnaToolScene.h"
#include "yuzinnaGameScene.h"
#include "yuzinnaBabaScene.h"

namespace yuzinna
{
	void LoadScenes()
	{
		//SceneManager::CreateScene<TitleScene>(L"TitleScene");
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<ToolScene>(L"ToolScene");
		//SceneManager::CreateScene<GameScene>(L"GameScene");
		SceneManager::CreateScene<BabaScene>(L"BabaScene");

		//SceneManager::LoadScene(L"ToolScene");
		//SceneManager::LoadScene(L"PlayScene");
		//SceneManager::LoadScene(L"GameScene");
		SceneManager::LoadScene(L"BabaScene");
		
	}
}