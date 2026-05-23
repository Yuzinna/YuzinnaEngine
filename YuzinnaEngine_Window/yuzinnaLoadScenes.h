#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaSceneManager.h"
#include "yuzinnaPlayScene.h"
#include "yuzinnaTitleScene.h"
#include "yuzinnaToolScene.h"
#include "yuzinnaGameScene.h"
#include "yuzinnaStageSelectScene.h"
#include "yuzinnaMapManager.h"

namespace yuzinna
{
	void LoadScenes()
	{
		MapManager::Initialize();

		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<StageSelectScene>(L"StageSelectScene");
		Scene* acScene = SceneManager::GetActiveScene();
		SceneManager::LoadScene(L"StageSelectScene");
	}
}
