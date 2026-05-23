#include "yuzinnaPlayScene.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaTransform.h"
#include "yuzinnaSpriteRenderer.h"
#include "yuzinnaObject.h"
#include "yuzinnaTexture.h"
#include "yuzinnaResources.h"
#include "yuzinnaCamera.h"
#include "yuzinnaRenderer.h"
#include "yuzinnaGridManager.h"
#include "yuzinnaBabaScript.h"
#include "yuzinnaAnimator.h"
#include "yuzinnaWord.h"
#include "yuzinnaObjectFactory.h"
#include "yuzinnaMapLoader.h"
#include "yuzinnaRuleManager.h"
#include "yuzinnaMapManager.h"
#include "yuzinnaUndoManager.h"
#include "yuzinnaAudioManager.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaInput.h"

namespace yuzinna
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Camera, Vector2(800.0f, 450.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;

		Scene::Initialize();
	}

	void PlayScene::OnEnter()
	{
		// 1. 기존 오브젝트들 모두 제거 (카메라 레이어 제외)
		for (int i = 0; i < (int)enums::eLayerType::End; ++i)
		{
			if ((enums::eLayerType)i == enums::eLayerType::Camera) continue;

			Layer* layer = GetLayer((enums::eLayerType)i);
			if (layer == nullptr) continue;

			const std::vector<GameObject*>& objs = layer->GetGameObjects();
			for (GameObject* obj : objs)
			{
				object::Destroy(obj);
			}
		}

		// 2. AudioManager를 통해 스테이지 BGM 재생
		AudioManager::PlayBGM(L"StageBGM", 0.2f);

		// 3. 맵 및 시스템 초기화
		UndoManager::Clear();
		std::vector<std::wstring> map = MapManager::GetMap(MapManager::GetCurrentStage());
		MapLoader::LoadMap(map);

		if (map.size() > 0 && map[0].size() > 0 && renderer::mainCamera != nullptr)
		{
			float mapWidth = (float)map[0].size() * 48.0f;
			float mapHeight = (float)map.size() * 48.0f;

			Transform* cameraTr = renderer::mainCamera->GetOwner()->GetComponent<Transform>();
			if (cameraTr != nullptr)
			{
				cameraTr->SetPosition(math::Vector2(mapWidth / 2.0f, mapHeight / 2.0f));
			}
		}

		RuleManager::UpdateRules();
		Scene::OnEnter();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			UndoManager::Undo();
		}

		Scene::Update();
		UndoManager::ResetCanSave();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PlayScene::OnExit()
	{
		// 씬 전환 시 BGM 정지
		AudioManager::StopBGM();
		Scene::OnExit();
	}
}
