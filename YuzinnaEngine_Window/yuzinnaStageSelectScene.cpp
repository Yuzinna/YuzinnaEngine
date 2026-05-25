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
		, mbAllClear(false)
	{
	}

	StageSelectScene::~StageSelectScene()
	{
	}

	void StageSelectScene::Initialize()
	{
		// ... (이동 없음)
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Camera, Vector2(396.0f, 216.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<AudioListener>();
		renderer::mainCamera = cameraComp;

		// ... (이동 없음)
		GameObject* bg = object::Instantiate<GameObject>(enums::eLayerType::BackGround, Vector2(396.0f, 216.0f));
		bg->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));
		bg->AddComponent<SpriteRenderer>(); 
		Animator* bgAni = bg->AddComponent<Animator>();
		graphics::Texture* mapTex = Resources::Find<graphics::Texture>(L"WorldMap");
		bgAni->CreateAnimation(L"MapLoop", mapTex, Vector2(0.0f, 0.0f), Vector2(792.0f, 432.0f), Vector2::Zero, 3, 0.5f, true);
		bgAni->PlayAnimation(L"MapLoop", true);

		// ... (이동 없음)
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

		// [수정] 씬에 다시 들어올 때 카메라 정보 완벽히 리셋 (위치 어긋남 해결)
		Layer* cameraLayer = GetLayer(enums::eLayerType::Camera);
		if (cameraLayer)
		{
			const std::vector<GameObject*>& cameraObjs = cameraLayer->GetGameObjects();
			if (!cameraObjs.empty())
			{
				GameObject* cameraObj = cameraObjs[0];
				Camera* cameraComp = cameraObj->GetComponent<Camera>();
				Transform* cameraTr = cameraObj->GetComponent<Transform>();

				if (cameraComp && cameraTr)
				{
					// 1. 메인 카메라 포인터 갱신
					renderer::mainCamera = cameraComp;
					
					// 2. 카메라 위치 강제 고정 (초기 중앙 위치)
					cameraTr->SetPosition(Vector2(396.0f, 216.0f));
					
					// 3. 카메라 내부 상태 리셋
					cameraComp->Initialize(); // 해상도 다시 계산
					cameraComp->SetTarget(nullptr); // 혹시 남았을지 모르는 타겟 제거
				}
			}
		}

		// AudioManager를 통해 전역 BGM 재생
		AudioManager::PlayBGM(L"MainBGM", 0.2f);

		// 모든 스테이지 클리어 여부 확인 (최대 해금 스테이지가 8이면 7번까지 다 깬 것)
		if (MapManager::GetMaxUnlockedStage() >= 8)
		{
			mbAllClear = true;
		}

		// 씬에 들어올 때마다 해금된 스테이지를 다시 체크하여 생성합니다.
		struct Pos { int x, y; };
		static std::vector<Pos> stageCoords = {
			{15, 8}, {16, 8}, {17, 8}, {17, 9}, {18, 9}, {18, 8}, {19, 8}, {19, 9}
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

		if (mbAllClear)
		{
			// ALL CLEAR 메세지 박스 렌더링
			int boxWidth = 600;
			int boxHeight = 300;
			int centerX = 800; 
			int centerY = 450; 

			int left = centerX - (boxWidth / 2);
			int top = centerY - (boxHeight / 2);
			int right = left + boxWidth;
			int bottom = top + boxHeight;

			// 배경 상자 (이중 테두리)
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(WHITE_BRUSH));
			Rectangle(hdc, left, top, right, bottom);
			Rectangle(hdc, left + 15, top + 15, right - 15, bottom - 15);

			// 텍스트 출력 설정
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(0, 0, 0));

			std::wstring clearText = L"ALL STAGE CLEAR!\n\nCongratulations!";
			
			// 1. 텍스트가 차지할 실제 크기를 먼저 계산 (DT_CALCRECT)
			RECT textRect = { 0, 0, boxWidth - 40, 0 };
			DrawText(hdc, clearText.c_str(), -1, &textRect, DT_CALCRECT | DT_CENTER | DT_WORDBREAK);
			
			int textHeight = textRect.bottom - textRect.top;
			
			// 2. 계산된 높이를 바탕으로 상자 중앙 좌표 계산
			RECT finalRect;
			finalRect.left = left + 20;
			finalRect.right = right - 20;
			finalRect.top = centerY - (textHeight / 2);
			finalRect.bottom = centerY + (textHeight / 2);
			
			// 3. 실제 출력 (가로 중앙 정렬)
			DrawText(hdc, clearText.c_str(), -1, &finalRect, DT_CENTER | DT_WORDBREAK);

			SelectObject(hdc, hOldBrush);
		}
	}
	void StageSelectScene::OnExit()
	{
		// 다음 씬으로 넘어가기 전 현재 BGM 정지
		AudioManager::StopBGM();

		Scene::OnExit();
	}
}
