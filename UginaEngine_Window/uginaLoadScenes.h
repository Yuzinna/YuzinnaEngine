#pragma once
#include "..\\UginaEngine_SOURCE\\uginaSceneManager.h"
#include "uginaPlayScene.h"
#include "uginaTitleScene.h"
#include "uginaToolScene.h"
#include "uginaGameScene.h"
#include "uginaBabaScene.h"

namespace ugina
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