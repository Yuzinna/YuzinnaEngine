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
		// 1. Undo 처리 (Z 키)
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			UndoManager::Undo();
			return;
		}

		// 2. 내가 현재 'YOU'인지 확인 (규칙이 없으면 조종 불가)
		eWordType myType = RuleManager::GetTypeByName(GetOwner()->GetName());
		if (!RuleManager::HasRule(myType, eWordType::You))
			return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* ani = GetOwner()->GetComponent<Animator>();
		if (tr == nullptr || ani == nullptr) return;


		// 현재 화면 좌표를 타일 크기로 나누어 현재 그리드 좌표를 계산
		math::Vector2 pos = tr->GetPosition();
		math::Vector2 tileSize = TilemapRenderer::TileSize;
		if (tileSize.x <= 0 || tileSize.y <= 0) tileSize = math::Vector2(48.0f, 48.0f);

		math::Vector2 currentGrid;
		currentGrid.x = std::round(pos.x / tileSize.x);
		currentGrid.y = std::round(pos.y / tileSize.y);

		math::Vector2 nextGrid = currentGrid;
		std::wstring animName = L"";

		// 2. 입력 처리 (방향키가 아닌 WASD 사용 중임 확인)
		if (Input::GetKeyDown(eKeyCode::D)) // Right
		{
			nextGrid.x += 1.0f;
			animName = L"BabaRight_";
		}
		else if (Input::GetKeyDown(eKeyCode::A)) // Left
		{
			nextGrid.x -= 1.0f;
			animName = L"BabaLeft_";
		}
		else if (Input::GetKeyDown(eKeyCode::S)) // Down
		{
			nextGrid.y += 1.0f;
			animName = L"BabaDown_";
		}
		else if (Input::GetKeyDown(eKeyCode::W)) // Up
		{
			nextGrid.y -= 1.0f;
			animName = L"BabaUp_";
		}

		if (nextGrid == currentGrid) return;

		Vector2 direction = nextGrid - currentGrid;
		std::vector<GameObject*> pushList;
		math::Vector2 checkGrid = nextGrid;
		bool canMove = true;

		// 3. 장애물 및 밀기 판정 (Chain check)
		while (true)
		{
			std::vector<GameObject*> targets = GridManager::GetObjectsAt(checkGrid);
			if (targets.empty()) break; // 빈 공간이면 이동 가능

			bool hasStop = false;
			bool hasPush = false;
			GameObject* pushTarget = nullptr;

			for (GameObject* target : targets)
			{
				eWordType targetType = RuleManager::GetTypeByName(target->GetName());
				bool isWord = (target->GetComponent<Word>() != nullptr);

				// STOP 속성이 하나라도 있으면 못 감
				if (RuleManager::HasRule(targetType, eWordType::Stop))
					hasStop = true;
				
				// PUSH 속성이나 단어 블록이면 밀기 리스트에 추가
				if (RuleManager::HasRule(targetType, eWordType::Push) || isWord)
				{
					hasPush = true;
					pushTarget = target;
				}
			}

			if (hasStop)
			{
				canMove = false;
				break;
			}

			if (hasPush && pushTarget)
			{
				pushList.push_back(pushTarget);
				checkGrid += direction; // 다음 칸도 확인
			}
			else
			{
				// PUSH도 STOP도 아니면 (예: 배경) 통과 가능
				break;
			}
		}

		// 4. 최종 이동 실행
		if (canMove)
		{
			// 이동하기 직전에 현재 전체 맵의 상태를 저장 (Undo용)
			UndoManager::SaveState();

			// 뒤에서부터 순서대로 밀기
			for (int i = (int)pushList.size() - 1; i >= 0; --i)
			{
				Vector2 objPos = pushList[i]->GetComponent<Transform>()->GetPosition();
				Vector2 objGrid(std::round(objPos.x / tileSize.x), std::round(objPos.y / tileSize.y));
				GridManager::MoveObject(pushList[i], objGrid + direction);
			}

			// 자신 이동
			mVersion = (mVersion + 1) % 4;
			ani->PlayAnimation(animName + std::to_wstring(mVersion), true);
			GridManager::MoveObject(GetOwner(), nextGrid);

			// 이동 후 규칙을 즉시 업데이트
			RuleManager::UpdateRules();

			// --- 승리 판정 (Win Check) ---
			auto currentObjects = GridManager::GetObjectsAt(nextGrid);
			for (GameObject* obj : currentObjects)
			{
				if (obj == GetOwner()) continue;

				eWordType objType = RuleManager::GetTypeByName(obj->GetName());
				if (RuleManager::HasRule(objType, eWordType::Win))
				{
					MessageBox(NULL, L"YOU WIN!", L"Baba Is You", MB_OK);
					
					// 다음 스테이지 해금 및 월드맵으로 복귀
					MapManager::UnlockNextStage();
					SceneManager::LoadScene(L"StageSelectScene");
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
