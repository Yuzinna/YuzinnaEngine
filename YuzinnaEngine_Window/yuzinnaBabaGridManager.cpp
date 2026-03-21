#include "yuzinnaBabaGridManager.h"
#include "yuzinnaSceneManager.h"
#include "yuzinnaScene.h"
#include "yuzinnaLayer.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaBabaWordComponent.h"
#include "yuzinnaTransform.h"
#include <string>
#include "yuzinnaTilemapRenderer.h"
namespace yuzinna
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

		// ?곹깭媛 諛붾뚯뿀?쇰땲 洹쒖튃???ㅼ떆 ?뚯떛
		ParseRules();
	}

	// ?⑥뼱 ??낆쓣 臾몄옄???대쫫?쇰줈 蹂?섑븯???꾩슦誘?(BABA -> L"BABA")
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

	// ?⑥뼱 ??낆쓣 ?띿꽦?쇰줈 蹂?섑븯???꾩슦誘?(YOU -> eBabaProperty::YOU)
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
		// 1. 留??꾩껜?먯꽌 紐⑤뱺 ?⑥뼱 而댄룷?뚰듃瑜??섏쭛
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

		// 2. 媛??⑥뼱瑜?湲곗??쇰줈 媛濡??몃줈 臾몄옣 寃??
		for (auto word : allWords)
		{
			if (word->GetCategory() != eWordCategory::NOUN) continue;

			BabaGridComponent* wordGrid = word->GetOwner()->GetComponent<BabaGridComponent>();
			if (wordGrid == nullptr) continue;

			math::Vector2 pos = wordGrid->GetGridIndex();
			
			// 寃??諛⑺뼢: ?ㅻⅨ履?1,0), ?꾨옒履?0,1)
			math::Vector2 dirs[2] = { math::Vector2(1,0), math::Vector2(0,1) };
			for (int d = 0; d < 2; ++d)
			{
				math::Vector2 dir = dirs[d];
				
				// IS(Verb) 泥댄겕
				auto isWords = GetGridAt(pos + dir);
				for (auto isWordObj : isWords)
				{
					auto isWordComp = isWordObj->GetOwner()->GetComponent<BabaWordComponent>();
					if (isWordComp && isWordComp->GetWordType() == eWordType::IS)
					{
						// ??踰덉㎏ ?⑥뼱(Property ?먮뒗 NOUN) 泥댄겕
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
		// 洹쒖튃??諛붾뚯뿀?쇰땲 諛붾줈 ?곸슜
		ApplyRules();
	}

	void BabaGridManager::ApplyRules()
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene == nullptr) return;

		// 1. 紐⑤뱺 媛앹껜???띿꽦 珥덇린??(?? WORD ?띿꽦? ?좎?)
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
					if (isWord) baba->AddProperty(eBabaProperty::WORD); // 湲?먮뒗 湲곕낯?곸쑝濡?諛 ???덉쓬
					if (isWord) baba->AddProperty(eBabaProperty::PUSH); 
				}
			}
		}

		// 2. ?꾩옱 ?뚯떛??洹쒖튃?ㅼ쓣 紐⑤뱺 ??곸뿉 ?곸슜
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
						
						// TODO: NOUN to NOUN (BABA IS ROCK) 蹂??濡쒖쭅? ?섏쨷??援ы쁽
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

		// 1. ?ㅼ쓬 移몄뿉 ?덈뒗 BabaGridComponent???뺤씤
		std::vector<BabaGridComponent*> targets = GetGridAt(nextGridPos);

		// 2. 媛濡쒕쭑??寃껋씠 ?덈뒗吏 ?뺤씤
		for (BabaGridComponent* target : targets)
		{
			// STOP ?띿꽦???덉쑝硫??대룞 遺덇?
			if (target->HasProperty(eBabaProperty::STOP))
			{
				return false;
			}

			// PUSH ?띿꽦???덉쑝硫?諛?대낯??(?ш?)
			if (target->HasProperty(eBabaProperty::PUSH))
			{
				// ?곗뇙?곸쑝濡?諛湲곗뿉 ?ㅽ뙣?섎㈃ ?섎룄 紐??吏곸엫
				if (!TryMove(target, direction))
				{
					return false;
				}
			}
		}

		// 3. 諛⑺빐臾쇱씠 ?녾굅????諛?대깉?ㅻ㈃ ?대룞 ?섑뻾
		moveComponent(comp, nextGridPos);
		
		// 4. ?대룞 ??洹쒖튃???ㅼ떆 ?뚯떛 (以묒슂!)
		ParseRules();

		return true;
	}

	void BabaGridManager::moveComponent(BabaGridComponent* comp, math::Vector2 nextGridPos)
	{
		comp->SetGridIndex(nextGridPos);
		
		// ?붾㈃?곸쓽 醫뚰몴???낅뜲?댄듃 (?대룞 ??利됱떆 諛섏쁺)
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
