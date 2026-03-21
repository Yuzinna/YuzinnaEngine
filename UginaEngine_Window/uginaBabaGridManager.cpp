#include "uginaBabaGridManager.h"
#include "uginaSceneManager.h"
#include "uginaScene.h"
#include "uginaLayer.h"
#include "uginaGameObject.h"
#include "uginaBabaWordComponent.h"
#include "uginaTransform.h"
#include <string>
#include "uginaTilemapRenderer.h"
namespace ugina
{
	std::vector<BabaRule> BabaGridManager::mCurrentRules;
	std::stack<TurnState> BabaGridManager::mHistory;

	void BabaGridManager::SaveState()
	{
		TurnState currentTurn;
		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene == nullptr) return;

		for (int i = 0; i < (int)enums::eLayerType::End; ++i)
		{
			Layer* layer = activeScene->GetLayer((enums::eLayerType)i);
			if (layer == nullptr) continue;
			for (auto obj : layer->GetGameObjects())
			{
				auto baba = obj->GetComponent<BabaGridComponent>();
				if (baba)
				{
					ObjectState state;
					state.obj = obj;
					state.gridIndex = baba->GetGridIndex();
					currentTurn.push_back(state);
				}
			}
		}
		mHistory.push(currentTurn);
	}

	void BabaGridManager::Undo()
	{
		if (mHistory.empty()) return;

		TurnState lastTurn = mHistory.top();
		mHistory.pop();

		for (const auto& state : lastTurn)
		{
			auto baba = state.obj->GetComponent<BabaGridComponent>();
			if (baba)
			{
				moveComponent(baba, state.gridIndex);
			}
		}

		// 상태가 바뀌었으니 규칙도 다시 파싱
		ParseRules();
	}

	// 단어 타입을 문자열 이름으로 변환하는 도우미 (BABA -> L"BABA")
	std::wstring GetWordName(eWordType type)
	{
		switch (type)
		{
		case eWordType::BABA: return L"BABA";
		case eWordType::ROCK: return L"ROCK";
		case eWordType::WALL: return L"WALL";
		case eWordType::FLAG: return L"FLAG";
		default: return L"";
		}
	}

	// 단어 타입을 속성으로 변환하는 도우미 (YOU -> eBabaProperty::YOU)
	eBabaProperty GetWordProperty(eWordType type)
	{
		switch (type)
		{
		case eWordType::YOU: return eBabaProperty::YOU;
		case eWordType::PUSH: return eBabaProperty::PUSH;
		case eWordType::STOP: return eBabaProperty::STOP;
		case eWordType::WIN: return eBabaProperty::WIN;
		case eWordType::SINK: return eBabaProperty::SINK;
		default: return eBabaProperty::NONE;
		}
	}

	void BabaGridManager::ParseRules()
	{
		mCurrentRules.clear();
		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene == nullptr) return;

		std::vector<BabaWordComponent*> allWords;
		// 1. 맵 전체에서 모든 단어 컴포넌트를 수집
		for (int i = 0; i < (int)enums::eLayerType::End; ++i)
		{
			Layer* layer = activeScene->GetLayer((enums::eLayerType)i);
			if (layer == nullptr) continue;
			for (auto obj : layer->GetGameObjects())
			{
				auto word = obj->GetComponent<BabaWordComponent>();
				if (word) allWords.push_back(word);
			}
		}

		// 2. 각 단어를 기준으로 가로/세로 문장 검사
		for (auto word : allWords)
		{
			if (word->GetCategory() != eWordCategory::NOUN) continue;

			BabaGridComponent* wordGrid = word->GetOwner()->GetComponent<BabaGridComponent>();
			if (wordGrid == nullptr) continue;

			math::Vector2 pos = wordGrid->GetGridIndex();
			
			// 검사 방향: 오른쪽(1,0), 아래쪽(0,1)
			math::Vector2 dirs[2] = { math::Vector2(1,0), math::Vector2(0,1) };
			for (int d = 0; d < 2; ++d)
			{
				math::Vector2 dir = dirs[d];
				
				// IS(Verb) 체크
				auto isWords = GetGridAt(pos + dir);
				for (auto isWordObj : isWords)
				{
					auto isWordComp = isWordObj->GetOwner()->GetComponent<BabaWordComponent>();
					if (isWordComp && isWordComp->GetWordType() == eWordType::IS)
					{
						// 세 번째 단어(Property 또는 NOUN) 체크
						auto thirdWords = GetGridAt(pos + dir * 2.0f);
						for (auto thirdWordObj : thirdWords)
						{
							auto thirdWordComp = thirdWordObj->GetOwner()->GetComponent<BabaWordComponent>();
							if (thirdWordComp)
							{
								BabaRule rule;
								rule.subject = GetWordName(word->GetWordType());

								if (thirdWordComp->GetCategory() == eWordCategory::PROPERTY)
								{
									rule.property = GetWordProperty(thirdWordComp->GetWordType());
									mCurrentRules.push_back(rule);
								}
								else if (thirdWordComp->GetCategory() == eWordCategory::NOUN)
								{
									rule.transformTo = GetWordName(thirdWordComp->GetWordType());
									mCurrentRules.push_back(rule);
								}
							}
						}
					}
				}
			}
		}
		// 규칙이 바뀌었으니 바로 적용
		ApplyRules();
	}

	void BabaGridManager::ApplyRules()
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene == nullptr) return;

		// 1. 모든 객체의 속성 초기화 (단, WORD 속성은 유지)
		for (int i = 0; i < (int)enums::eLayerType::End; ++i)
		{
			Layer* layer = activeScene->GetLayer((enums::eLayerType)i);
			if (layer == nullptr) continue;
			for (auto obj : layer->GetGameObjects())
			{
				auto baba = obj->GetComponent<BabaGridComponent>();
				if (baba)
				{
					bool isWord = baba->HasProperty(eBabaProperty::WORD);
					baba->ClearProperties();
					if (isWord) baba->AddProperty(eBabaProperty::WORD); // 글자는 기본적으로 밀 수 있음
					if (isWord) baba->AddProperty(eBabaProperty::PUSH); 
				}
			}
		}

		// 2. 현재 파싱된 규칙들을 모든 대상에 적용
		for (const auto& rule : mCurrentRules)
		{
			for (int i = 0; i < (int)enums::eLayerType::End; ++i)
			{
				Layer* layer = activeScene->GetLayer((enums::eLayerType)i);
				if (layer == nullptr) continue;
				for (auto obj : layer->GetGameObjects())
				{
					auto baba = obj->GetComponent<BabaGridComponent>();
					if (baba && baba->GetName() == rule.subject)
					{
						if (rule.property != eBabaProperty::NONE)
							baba->AddProperty(rule.property);
						
						// TODO: NOUN to NOUN (BABA IS ROCK) 변신 로직은 나중에 구현
					}
				}
			}
		}
	}

	std::vector<BabaGridComponent*> BabaGridManager::GetGridAt(math::Vector2 gridIndex)
	{
		std::vector<BabaGridComponent*> results;
		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene == nullptr) return results;

		for (int i = 0; i < (int)enums::eLayerType::End; ++i)
		{
			Layer* layer = activeScene->GetLayer((enums::eLayerType)i);
			if (layer == nullptr) continue;

			const std::vector<GameObject*> objects = layer->GetGameObjects();
			for (GameObject* obj : objects)
			{
				if (obj == nullptr || !obj->IsActive()) continue;

				BabaGridComponent* babaComp = obj->GetComponent<BabaGridComponent>();
				if (babaComp && (int)babaComp->GetGridIndex().x == (int)gridIndex.x && (int)babaComp->GetGridIndex().y == (int)gridIndex.y)
				{
					results.push_back(babaComp);
				}
			}
		}
		return results;
	}

	bool BabaGridManager::HasProperty(math::Vector2 gridIndex, eBabaProperty property)
	{
		auto comps = GetGridAt(gridIndex);
		for (auto comp : comps)
		{
			if (comp->HasProperty(property)) return true;
		}
		return false;
	}

	std::vector<BabaGridComponent*> BabaGridManager::GetComponentsWithProperty(math::Vector2 gridIndex, eBabaProperty property)
	{
		std::vector<BabaGridComponent*> results;
		auto comps = GetGridAt(gridIndex);
		for (auto comp : comps)
		{
			if (comp->HasProperty(property)) results.push_back(comp);
		}
		return results;
	}

	bool BabaGridManager::TryMove(BabaGridComponent* comp, math::Vector2 direction)
	{
		if (comp == nullptr) return false;

		math::Vector2 nextGridPos = comp->GetGridIndex() + direction;

		// 1. 다음 칸에 있는 BabaGridComponent들 확인
		std::vector<BabaGridComponent*> targets = GetGridAt(nextGridPos);

		// 2. 가로막는 것이 있는지 확인
		for (BabaGridComponent* target : targets)
		{
			// STOP 속성이 있으면 이동 불가
			if (target->HasProperty(eBabaProperty::STOP))
			{
				return false;
			}

			// PUSH 속성이 있으면 밀어본다 (재귀)
			if (target->HasProperty(eBabaProperty::PUSH))
			{
				// 연쇄적으로 밀기에 실패하면 나도 못 움직임
				if (!TryMove(target, direction))
				{
					return false;
				}
			}
		}

		// 3. 방해물이 없거나 다 밀어냈다면 이동 수행
		moveComponent(comp, nextGridPos);
		
		// 4. 이동 후 규칙을 다시 파싱 (중요!)
		ParseRules();

		return true;
	}

	void BabaGridManager::moveComponent(BabaGridComponent* comp, math::Vector2 nextGridPos)
	{
		comp->SetGridIndex(nextGridPos);
		
		// 화면상의 좌표도 업데이트 (이동 시 즉시 반영)
		Transform* tr = comp->GetOwner()->GetComponent<Transform>();
		if (tr)
		{
			math::Vector2 screenPos;
			screenPos.x = nextGridPos.x * TilemapRenderer::TileSize.x;
			screenPos.y = nextGridPos.y * TilemapRenderer::TileSize.y;
			tr->SetPosition(screenPos);
		}
	}
}
