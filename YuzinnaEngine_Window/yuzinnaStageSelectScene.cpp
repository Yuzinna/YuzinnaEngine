#include "yuzinnaStageSelectScene.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaTransform.h"
#include "yuzinnaSpriteRenderer.h"
#include "yuzinnaAnimator.h"
#include "yuzinnaObject.h"
#include "yuzinnaResources.h"
#include "yuzinnaWorldMapScript.h"
#include "yuzinnaCamera.h"
#include "yuzinnaRenderer.h"
#include "yuzinnaMapManager.h"
#include "yuzinnaAudioListener.h"
#include "yuzinnaAudioManager.h"

namespace yuzinna
{
	StageSelectScene::StageSelectScene()
		: mCursorScript(nullptr)
	{
	}

	StageSelectScene::~StageSelectScene()
	{
	}

	void StageSelectScene::Initialize()
	{
		// 1. 카메라 설정
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Camera, Vector2(396.0f, 216.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<AudioListener>();
		renderer::mainCamera = cameraComp;

		// 2. 월드맵 배경
		GameObject* bg = object::Instantiate<GameObject>(enums::eLayerType::BackGround, Vector2(396.0f, 216.0f));
		bg->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));
		bg->AddComponent<SpriteRenderer>(); 
		Animator* bgAni = bg->AddComponent<Animator>();
		graphics::Texture* mapTex = Resources::Find<graphics::Texture>(L"WorldMap");
		bgAni->CreateAnimation(L"MapLoop", mapTex, Vector2(0.0f, 0.0f), Vector2(792.0f, 432.0f), Vector2::Zero, 3, 0.5f, true);
		bgAni->PlayAnimation(L"MapLoop", true);

		// 3. 커서 생성
		GameObject* cursor = object::Instantiate<GameObject>(enums::eLayerType::Player, Vector2(12.0f, 12.0f));
		cursor->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));
		cursor->AddComponent<SpriteRenderer>();
		Animator* cursorAni = cursor->AddComponent<Animator>();
		graphics::Texture* cursorTex = Resources::Find<graphics::Texture>(L"WorldCursor");
		cursorAni->CreateAnimation(L"CursorLoop", cursorTex, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 3, 0.5f, true);
		cursorAni->PlayAnimation(L"CursorLoop", true);
		mCursorScript = cursor->AddComponent<WorldMapScript>();

		Scene::Initialize();
	}

	void StageSelectScene::OnEnter()
	{
		Scene::OnEnter();

		// AudioManager를 통해 전역 BGM 재생
		AudioManager::PlayBGM(L"MainBGM", 0.2f);

		// 씬에 들어올 때마다 해금된 스테이지를 다시 체크하여 생성합니다.
		struct Pos { int x, y; };
		static std::vector<Pos> stageCoords = {
			{15, 8}, {16, 8}, {17, 8}, {17, 9}, {18, 9}, {18, 8}
		};

		int maxStage = MapManager::GetMaxUnlockedStage();
		
		for (int i = 0; i <= maxStage; ++i)
		{
			if (i >= stageCoords.size()) break;

			if (mCursorScript && !mCursorScript->HasStage(i))
			{
				CreateStageIcon(i, stageCoords[i].x, stageCoords[i].y);
			}
		}

		if (mCursorScript)
		{
			mCursorScript->SetToStage(MapManager::GetCurrentStage());
		}
	}

	void StageSelectScene::CreateStageIcon(int stageNum, int gridX, int gridY)
	{
		Vector2 pos((float)gridX * 24.0f + 12.0f, (float)gridY * 24.0f + 12.0f);
		GameObject* stageObj = object::Instantiate<GameObject>(enums::eLayerType::Tile, pos);
		stageObj->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));
		stageObj->AddComponent<SpriteRenderer>();
		Animator* ani = stageObj->AddComponent<Animator>();
		
		std::wstring key = L"StageIcon_" + std::to_wstring(stageNum);
		graphics::Texture* stageTex = Resources::Find<graphics::Texture>(key);
		
		ani->CreateAnimation(L"StageLoop", stageTex, Vector2(0.0f, 0.0f), Vector2(24.0f, 24.0f), Vector2::Zero, 3, 0.5f, true);
		ani->PlayAnimation(L"StageLoop", true);

		if (mCursorScript)
		{
			mCursorScript->AddStage(stageNum, gridX, gridY);
		}
	}

	void StageSelectScene::Update()
	{
		Scene::Update();
	}
	void StageSelectScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void StageSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void StageSelectScene::OnExit()
	{
		// 다음 씬으로 넘어가기 전 현재 BGM 정지
		AudioManager::StopBGM();

		Scene::OnExit();
	}
}
