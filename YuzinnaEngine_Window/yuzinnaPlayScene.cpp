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
		// 메인 카메라 설정 (중앙 배치)
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(800.0f, 450.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;

		// 맵 데이터 정의
		// B: 바바, F: 깃발, W: 벽
		// b,i,y: Baba is You, f,i,n: Flag is Win, k,i,s: Wall is Stop
		std::vector<std::wstring> map = {
			L"WWWWWWWWWWWWWWWW",
			L"W..............W",
			L"W....B....kis..W", // 바바와 Wall is Stop 문장
			L"W..............W",
			L"WWWWWWWWWWWWWWWW", // 바바를 가두는 벽
			L"................",
			L".......F........", // 벽 바깥의 깃발
			L"......biy....fin"  // 기본 규칙 (Baba Is You, Flag Is Win)
		};

		// MapLoader를 통해 맵 생성 및 오토 타일링 적용
		MapLoader::LoadMap(map);

		// 게임 오브젝트 생성후에 레이어와 게임오브젝트들의 init함수를 호출
		Scene::Initialize();

		// 초기 규칙 설정
		RuleManager::UpdateRules();
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void PlayScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void PlayScene::OnExit()
	{
		Scene::OnExit();
	}
}
