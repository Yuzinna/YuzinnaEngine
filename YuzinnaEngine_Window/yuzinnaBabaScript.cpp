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
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaSceneManager.h"

namespace yuzinna
{
	BabaScript::BabaScript()
		: mVersion(0)
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
		// 1. 내가 현재 'YOU'인지 확인 (어떤 오브젝트든 상관없이 규칙에 따름)
		eWordType myType = RuleManager::GetTypeByName(GetOwner()->GetName());
		bool isYou = RuleManager::HasRule(myType, eWordType::You);
		bool isWin = RuleManager::HasRule(myType, eWordType::Win);

		// --- [추가] YOU이자 WIN인 경우 즉시 승리 ---
		if (isYou && isWin)
		{
			MessageBox(NULL, L"YOU IS WIN!", L"Baba Is You", MB_OK);
			MapManager::UnlockNextStage();
			SceneManager::LoadScene(L"StageSelectScene");
			return;
		}

		if (!isYou) return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* ani = GetOwner()->GetComponent<Animator>();
		if (tr == nullptr) return;

		// 입력 감지 (모든 YOU 오브젝트가 동일한 프레임에 입력을 받음)
		math::Vector2 pos = tr->GetPosition();
		math::Vector2 tileSize = TilemapRenderer::TileSize;
		if (tileSize.x <= 0 || tileSize.y <= 0) tileSize = math::Vector2(48.0f, 48.0f);

		math::Vector2 currentGrid(std::round(pos.x / tileSize.x), std::round(pos.y / tileSize.y));
		math::Vector2 nextGrid = currentGrid;
		std::wstring animPrefix = GetOwner()->GetName(); // 이름에 따른 애니메이션 처리 (Baba, Wall 등)
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

			for (GameObject* target : targets)
			{
				eWordType targetType = RuleManager::GetTypeByName(target->GetName());
				if (RuleManager::HasRule(targetType, eWordType::Stop)) hasStop = true;
				if (RuleManager::HasRule(targetType, eWordType::Push) || target->GetComponent<Word>())
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
			// UndoManager가 내부적으로 중복 저장을 방지함
			UndoManager::SaveState();

			// 이동이 발생한 모든 그리드 좌표를 저장할 리스트
			std::vector<math::Vector2> affectedGrids;

			// 뒤에서부터 순서대로 밀기
			for (int i = (int)pushList.size() - 1; i >= 0; --i)
			{
				Vector2 objPos = pushList[i]->GetComponent<Transform>()->GetPosition();
				Vector2 objGrid(std::round(objPos.x / tileSize.x), std::round(objPos.y / tileSize.y));
				Vector2 targetGrid = objGrid + direction;

				GridManager::MoveObject(pushList[i], targetGrid);
				affectedGrids.push_back(targetGrid); // 밀려난 위치 저장
			}

			// 애니메이션 처리
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

			// 자신 이동
			GridManager::MoveObject(GetOwner(), nextGrid);
			affectedGrids.push_back(nextGrid); // 내 이동 위치 저장

			// 이동 후 규칙 즉시 업데이트
			RuleManager::UpdateRules();

			// --- [개선] SINK 판정 (모든 영향받은 그리드 검사) ---
			for (const math::Vector2& grid : affectedGrids)
			{
				auto objectsAtGrid = GridManager::GetObjectsAt(grid);
				if (objectsAtGrid.size() < 2) continue; // 겹쳐있지 않으면 스킵

				bool hasSink = false;
				for (GameObject* obj : objectsAtGrid)
				{
					eWordType type = RuleManager::GetTypeByName(obj->GetName());
					if (RuleManager::HasRule(type, eWordType::Sink))
					{
						hasSink = true;
						break;
					}
				}

				if (hasSink)
				{
					// SINK 속성이 있는 칸의 모든 오브젝트 파괴
					for (GameObject* obj : objectsAtGrid)
					{
						object::Destroy(obj);
					}
				}
			}

			// --- 승리 판정 (Win Check) ---
			// (나 자신이 파괴되었을 수도 있으므로 GetObjectsAt으로 다시 확인)
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
						MessageBox(NULL, L"YOU WIN!", L"Baba Is You", MB_OK);
						MapManager::UnlockNextStage();
						SceneManager::LoadScene(L"StageSelectScene");
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
	}
}
