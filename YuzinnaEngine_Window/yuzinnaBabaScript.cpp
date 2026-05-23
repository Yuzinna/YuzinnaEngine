#include "yuzinnaBabaScript.h"
#include "yuzinnaInput.h"
#include "yuzinnaTransform.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaGridManager.h"
#include "yuzinnaTilemapRenderer.h"
#include "yuzinnaAnimator.h"
#include "yuzinnaRuleManager.h"
#include "yuzinnaWord.h"
#include "yuzinnaUndoManager.h"
#include "yuzinnaMapManager.h"
#include "yuzinnaAudioManager.h"
#include "yuzinnaTime.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaSceneManager.h"

namespace yuzinna
{
	BabaScript::BabaScript()
		: mVersion(0)
		, mWinTimer(0.0f)
		, mbWin(false)
	{
	}

	BabaScript::~BabaScript()
	{
	}

	void BabaScript::Initialize()
	{
	}

	void BabaScript::Update()
	{
		// --- 승리 연출 중이면 대기 ---
		if (mbWin)
		{
			mWinTimer += Time::DeltaTime();
			if (mWinTimer >= 2.0f) // 2초 후 씬 전환
			{
				SceneManager::LoadScene(L"StageSelectScene");
			}
			return;
		}

		// 1. 내가 현재 'YOU'인지 확인
		eWordType myType = RuleManager::GetTypeByName(GetOwner()->GetName());
		bool isYou = RuleManager::HasRule(myType, eWordType::You);
		bool isWin = RuleManager::HasRule(myType, eWordType::Win);

		// --- YOU이자 WIN인 경우 승리 연출 시작 ---
		if (isYou && isWin)
		{
			mbWin = true;
			MapManager::UnlockNextStage();
			AudioManager::PlaySFX(L"WinSFX");
			return;
		}

		if (!isYou) return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* ani = GetOwner()->GetComponent<Animator>();
		if (tr == nullptr) return;

		// 입력 감지
		math::Vector2 pos = tr->GetPosition();
		math::Vector2 tileSize = TilemapRenderer::TileSize;
		if (tileSize.x <= 0 || tileSize.y <= 0) tileSize = math::Vector2(48.0f, 48.0f);

		math::Vector2 currentGrid(std::round(pos.x / tileSize.x), std::round(pos.y / tileSize.y));
		math::Vector2 nextGrid = currentGrid;
		std::wstring animPrefix = GetOwner()->GetName(); 
		std::wstring animDir = L"";

		if (Input::GetKeyDown(eKeyCode::D)) { nextGrid.x += 1.0f; animDir = L"Right"; }
		else if (Input::GetKeyDown(eKeyCode::A)) { nextGrid.x -= 1.0f; animDir = L"Left"; }
		else if (Input::GetKeyDown(eKeyCode::S)) { nextGrid.y += 1.0f; animDir = L"Down"; }
		else if (Input::GetKeyDown(eKeyCode::W)) { nextGrid.y -= 1.0f; animDir = L"Up"; }

		if (nextGrid == currentGrid) return;

		Vector2 direction = nextGrid - currentGrid;
		std::vector<GameObject*> pushList;
		math::Vector2 checkGrid = nextGrid;
		bool canMove = true;

		// 3. 장애물 및 밀기 판정
		while (true)
		{
			std::vector<GameObject*> targets = GridManager::GetObjectsAt(checkGrid);
			if (targets.empty()) break; 

			bool hasStop = false;
			bool hasPush = false;
			GameObject* pushTarget = nullptr;

			// --- [수정] 충돌/상호작용 판정 상세화 ---
			for (GameObject* target : targets)
			{
				eWordType targetType = RuleManager::GetTypeByName(target->GetName());
				bool isStop = RuleManager::HasRule(targetType, eWordType::Stop);
				bool isPush = RuleManager::HasRule(targetType, eWordType::Push) || target->GetComponent<Word>();
				bool isSink = RuleManager::HasRule(targetType, eWordType::Sink);
				bool isShut = RuleManager::HasRule(targetType, eWordType::Shut);
				bool isOpen = RuleManager::HasRule(targetType, eWordType::Open);

				// 현재 이동하려는 객체(또는 밀리고 있는 객체)의 속성 확인
				GameObject* movingObj = pushList.empty() ? GetOwner() : pushList.back();
				eWordType movingType = RuleManager::GetTypeByName(movingObj->GetName());
				bool movingIsSink = RuleManager::HasRule(movingType, eWordType::Sink);
				bool movingIsOpen = RuleManager::HasRule(movingType, eWordType::Open);
				bool movingIsShut = RuleManager::HasRule(movingType, eWordType::Shut);

				// 상호작용 파괴가 일어나는지 확인 (SINK 혹은 OPEN/SHUT 쌍)
				bool willDestroy = (isSink || movingIsSink);
				if (!willDestroy)
				{
					if ((isOpen && movingIsShut) || (isShut && movingIsOpen))
						willDestroy = true;
				}

				// STOP이지만 파괴될 운명이라면 통과 허용
				if (isStop && !willDestroy) hasStop = true;

				if (isPush)
				{
					hasPush = true;
					pushTarget = target;
				}
			}

			if (hasStop) { canMove = false; break; }
			if (hasPush && pushTarget) { pushList.push_back(pushTarget); checkGrid += direction; }
			else break;
		}

		// 4. 이동 실행
		if (canMove)
		{
			UndoManager::SaveState();

			static float lastPlayTime = -1.0f;
			if (lastPlayTime != Time::DeltaTime())
			{
				AudioManager::PlaySFX(L"MoveSFX");
				lastPlayTime = Time::DeltaTime();
			}

			std::vector<math::Vector2> affectedGrids;

			for (int i = (int)pushList.size() - 1; i >= 0; --i)
			{
				Vector2 objPos = pushList[i]->GetComponent<Transform>()->GetPosition();
				Vector2 objGrid(std::round(objPos.x / tileSize.x), std::round(objPos.y / tileSize.y));
				Vector2 targetGrid = objGrid + direction;

				GridManager::MoveObject(pushList[i], targetGrid);
				affectedGrids.push_back(targetGrid);
			}

			if (ani)
			{
				if (GetOwner()->GetName() == L"Baba")
				{
					mVersion = (mVersion + 1) % 4;
					ani->PlayAnimation(L"Baba" + animDir + L"_" + std::to_wstring(mVersion), true);
				}
				else if (GetOwner()->GetName() == L"Skull")
				{
					ani->PlayAnimation(L"Skull" + animDir, true);
				}
			}

			GridManager::MoveObject(GetOwner(), nextGrid);
			affectedGrids.push_back(nextGrid);

			RuleManager::UpdateRules();

			// SINK, DEFEAT, OPEN/SHUT 판정
			for (const math::Vector2& grid : affectedGrids)
			{
				auto objectsAtGrid = GridManager::GetObjectsAt(grid);
				if (objectsAtGrid.empty()) continue;

				// 1. SINK 판정 (가장 강력함: 모든 것을 파괴)
				bool hasSink = false;
				for (GameObject* obj : objectsAtGrid)
				{
					eWordType type = RuleManager::GetTypeByName(obj->GetName());
					if (RuleManager::HasRule(type, enums::eWordType::Sink)) { hasSink = true; break; }
				}

				if (hasSink && objectsAtGrid.size() >= 2)
				{
					AudioManager::PlaySFX(L"DeathSFX");
					for (GameObject* obj : objectsAtGrid) object::Destroy(obj);
					continue; // 칸 전멸 시 다음 칸으로
				}

				// 2. DEFEAT 판정
				bool hasDefeat = false;
				for (GameObject* obj : objectsAtGrid)
				{
					if (obj->IsDead()) continue;
					eWordType type = RuleManager::GetTypeByName(obj->GetName());
					if (RuleManager::HasRule(type, enums::eWordType::Defeat)) { hasDefeat = true; break; }
				}

				if (hasDefeat)
				{
					for (GameObject* obj : objectsAtGrid)
					{
						if (obj->IsDead()) continue;
						eWordType type = RuleManager::GetTypeByName(obj->GetName());
						if (RuleManager::HasRule(type, enums::eWordType::You))
						{
							object::Destroy(obj);
							AudioManager::PlaySFX(L"DeathSFX");
						}
					}
				}

				// 3. OPEN / SHUT 판정 (1:1 쌍 파괴)
				std::vector<GameObject*> openObjs;
				std::vector<GameObject*> shutObjs;
				bool somethingOpened = false;

				for (GameObject* obj : objectsAtGrid)
				{
					if (obj->IsDead()) continue;
					eWordType type = RuleManager::GetTypeByName(obj->GetName());
					bool isOpen = RuleManager::HasRule(type, enums::eWordType::Open);
					bool isShut = RuleManager::HasRule(type, enums::eWordType::Shut);

					// 한 객체가 둘 다 가진 경우 즉시 파괴
					if (isOpen && isShut)
					{
						object::Destroy(obj);
						somethingOpened = true;
						continue;
					}

					if (isOpen) openObjs.push_back(obj);
					if (isShut) shutObjs.push_back(obj);
				}

				// 1:1 쌍으로 제거
				size_t pairCount = min(openObjs.size(), shutObjs.size());
				if (pairCount > 0)
				{
					somethingOpened = true;
					for (size_t i = 0; i < pairCount; ++i)
					{
						object::Destroy(openObjs[i]);
						object::Destroy(shutObjs[i]);
					}
				}

				if (somethingOpened)
				{
					AudioManager::PlaySFX(L"OpenSFX");
				}
			}

			// 파괴된 결과를 반영하여 규칙(BGM 정지 등) 재업데이트
			RuleManager::UpdateRules();

			// 승리 판정
			auto currentObjects = GridManager::GetObjectsAt(nextGrid);
			bool amIDead = true;
			for (GameObject* obj : currentObjects) { if (obj == GetOwner()) amIDead = false; }

			if (!amIDead)
			{
				for (GameObject* obj : currentObjects)
				{
					if (obj == GetOwner()) continue;
					eWordType objType = RuleManager::GetTypeByName(obj->GetName());
					if (RuleManager::HasRule(objType, eWordType::Win))
					{
						mbWin = true;
						MapManager::UnlockNextStage();
						AudioManager::StopBGM();
						AudioManager::PlaySFX(L"WinSFX");
						return;
					}
				}
			}
		}
	}

	void BabaScript::LateUpdate()
	{
	}

	void BabaScript::Render(HDC hdc)
	{
		if (mbWin)
		{
			// 1. 화면 중앙 계산 (대략적인 윈도우 크기 1600x900 기준, 필요시 조정)
			// 실제 윈도우 크기를 정확히 가져오려면 GetClientRect 등을 쓸 수 있지만 
			// 여기선 중앙 근처에 고정 위치로 그립니다.
			int boxWidth = 400;
			int boxHeight = 200;
			int centerX = 800; // 화면 중앙 X
			int centerY = 450; // 화면 중앙 Y

			int left = centerX - (boxWidth / 2);
			int top = centerY - (boxHeight / 2);
			int right = left + boxWidth;
			int bottom = top + boxHeight;

			// 2. 배경 상자 그리기 (시스템 창 느낌의 회색/흰색 조합)
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(WHITE_BRUSH));
			Rectangle(hdc, left, top, right, bottom);

			// 테두리 강조
			Rectangle(hdc, left + 5, top + 5, right - 5, bottom - 5);

			// 3. 텍스트 출력
			std::wstring winText = L"YOU WIN!";
			
			// 폰트 설정 (생략 시 기본 폰트)
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(0, 0, 0));

			// 텍스트 중앙 정렬 출력
			RECT rect = { left, top, right, bottom };
			DrawText(hdc, winText.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			SelectObject(hdc, hOldBrush);
		}
	}
}
