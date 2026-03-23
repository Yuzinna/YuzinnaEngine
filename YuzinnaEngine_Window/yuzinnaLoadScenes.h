#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaSceneManager.h"
#include "yuzinnaPlayScene.h"
#include "yuzinnaTitleScene.h"
#include "yuzinnaToolScene.h"
#include "yuzinnaGameScene.h"

namespace yuzinna
{
	void LoadScenes()
	{
		// SceneManager::CreateScene<TitleScene>(L"TitleScene");
		 SceneManager::CreateScene<PlayScene>(L"PlayScene");
		 //SceneManager::CreateScene<ToolScene>(L"ToolScene");
		// SceneManager::LoadScene(L"TitleScene");
		 //SceneManager::LoadScene(L"ToolScene");

		 SceneManager::LoadScene(L"PlayScene");

	}
}
