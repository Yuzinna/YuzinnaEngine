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
		// 카메라처럼 씬 전체에서 유지되어야 하는 요소만 여기서 1번 생성
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

		// 2. Undo 히스토리 초기화
		UndoManager::Clear();

		// 3. 현재 스테이지 맵 로딩
		std::vector<std::wstring> map = MapManager::GetMap(MapManager::GetCurrentStage());
		MapLoader::LoadMap(map);

		// 4. 카메라를 맵의 정중앙으로 이동
		if (map.size() > 0 && map[0].size() > 0 && renderer::mainCamera != nullptr)
		{
			float mapWidth = (float)map[0].size() * 48.0f;  // 48.0f = TileSize
			float mapHeight = (float)map.size() * 48.0f;

			Transform* cameraTr = renderer::mainCamera->GetOwner()->GetComponent<Transform>();
			if (cameraTr != nullptr)
			{
				cameraTr->SetPosition(math::Vector2(mapWidth / 2.0f, mapHeight / 2.0f));
			}
		}

		// 5. 규칙 갱신
		RuleManager::UpdateRules();

		Scene::OnEnter();
	}

	#include "yuzinnaInput.h"

	void PlayScene::Update()
	{
		// 1. Undo 처리 (Z 키) - 씬 전체에서 딱 한 번만 실행
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			UndoManager::Undo();
		}

		Scene::Update();

		// 2. 모든 오브젝트의 이동 처리가 끝난 후, 다음 프레임에서 다시 Undo 저장이 가능하도록 리셋
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
		// 씬을 나갈 때도 혹시 모를 잔상을 위해 오브젝트들을 정리할 수 있습니다.
		Scene::OnExit();
	}
}
