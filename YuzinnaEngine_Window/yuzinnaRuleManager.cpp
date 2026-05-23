#include "yuzinnaRuleManager.h"
#include "yuzinnaWord.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaSceneManager.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaScene.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaLayer.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaGridManager.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaTransform.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaTilemapRenderer.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaAudioManager.h"
namespace yuzinna
{
	std::vector<Rule> RuleManager::mRules = {};

	void RuleManager::UpdateRules()
	{
		std::vector<Rule> prevRules = mRules;
		mRules.clear();

		// 1. 모든 Word 컴포넌트 비활성화
		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene == nullptr) return;

		for (int i = 0; i < (int)eLayerType::Max; ++i)
		{
			Layer* layer = activeScene->GetLayer((eLayerType)i);
			if (layer == nullptr) continue;

			const std::vector<GameObject*>& objs = layer->GetGameObjects();
			for (GameObject* obj : objs)
			{
				Word* word = obj->GetComponent<Word>();
				if (word) word->SetActive(false);
			}
		}

		// 2. IS 단어 찾기 및 문장 검사
		for (int i = 0; i < (int)eLayerType::Max; ++i)
		{
			Layer* layer = activeScene->GetLayer((eLayerType)i);
			if (layer == nullptr) continue;

			const std::vector<GameObject*>& objs = layer->GetGameObjects();
			for (GameObject* obj : objs)
			{
				Word* isWord = obj->GetComponent<Word>();
				if (isWord && isWord->GetWordType() == eWordType::Is)
				{
					Transform* tr = obj->GetComponent<Transform>();
					Vector2 pos = tr->GetPosition();
					Vector2 tileSize = TilemapRenderer::TileSize;
					if (tileSize.x <= 0 || tileSize.y <= 0) tileSize = Vector2(48.0f, 48.0f);

					// 그리드 좌표
					Vector2 gridPos = Vector2(pos.x / tileSize.x, pos.y / tileSize.y);

					// --- 가로 검사 (좌-IS-우) ---
					auto leftObjs = GridManager::GetObjectsAt(gridPos + Vector2(-1.0f, 0.0f));
					auto rightObjs = GridManager::GetObjectsAt(gridPos + Vector2(1.0f, 0.0f));

					for (auto left : leftObjs)
					{
						Word* lWord = left->GetComponent<Word>();
						if (lWord && IsNoun(lWord->GetWordType()))
						{
							for (auto right : rightObjs)
							{
								Word* rWord = right->GetComponent<Word>();
								if (rWord && (IsNoun(rWord->GetWordType()) || IsProperty(rWord->GetWordType())))
								{
									mRules.push_back({ lWord->GetWordType(), eWordType::Is, rWord->GetWordType() });
									lWord->SetActive(true);
									isWord->SetActive(true);
									rWord->SetActive(true);
								}
							}
						}
					}

					// --- 세로 검사 (상-IS-하) ---
					auto upObjs = GridManager::GetObjectsAt(gridPos + Vector2(0.0f, -1.0f));
					auto downObjs = GridManager::GetObjectsAt(gridPos + Vector2(0.0f, 1.0f));

					for (auto up : upObjs)
					{
						Word* uWord = up->GetComponent<Word>();
						if (uWord && IsNoun(uWord->GetWordType()))
						{
							for (auto down : downObjs)
							{
								Word* dWord = down->GetComponent<Word>();
								if (dWord && (IsNoun(dWord->GetWordType()) || IsProperty(dWord->GetWordType())))
								{
									mRules.push_back({ uWord->GetWordType(), eWordType::Is, dWord->GetWordType() });
									uWord->SetActive(true);
									isWord->SetActive(true);
									dWord->SetActive(true);
								}
							}
						}
					}
				}
			}
		}

		// 3. --- [추가] YOU 속성 오브젝트 레이어 우선순위 조정 ---
		int youCount = 0;
		for (int i = 0; i < (int)eLayerType::Max; ++i)
		{
			if ((eLayerType)i == eLayerType::Camera || (eLayerType)i == eLayerType::UI) continue;

			Layer* layer = activeScene->GetLayer((eLayerType)i);
			if (layer == nullptr) continue;

			const std::vector<GameObject*>& objs = layer->GetGameObjects();
			// 컬렉션 수정 중 반복문 오류 방지를 위해 복사본 사용
			std::vector<GameObject*> copyObjs = objs;

			for (GameObject* obj : copyObjs)
			{
				if (obj->IsDead()) continue; // 파괴된 오브젝트는 제외
				if (obj->GetComponent<Word>()) continue; // 단어 블록은 제외

				eWordType type = GetTypeByName(obj->GetName());
				bool isYou = HasRule(type, eWordType::You);

				if (isYou) youCount++;

				// YOU이면 Player 레이어로, 아니면 Tile 레이어로 이동 (필요 시에만)
				if (isYou && obj->GetLayerType() != eLayerType::Player)
				{
					activeScene->MoveGameObjectLayer(obj, eLayerType::Player);
				}
				else if (!isYou && obj->GetLayerType() == eLayerType::Player)
				{
					activeScene->MoveGameObjectLayer(obj, eLayerType::Tile);
				}
			}
		}

		// --- YOU가 없으면 BGM 정지, 다시 생기면 재생 (PlayScene 전용) ---
		if (activeScene->GetName() == L"PlayScene")
		{
			if (youCount == 0)
			{
				AudioManager::StopBGM();
			}
			else if (youCount > 0 && !AudioManager::IsBGMPlaying())
			{
				AudioManager::PlayBGM(L"StageBGM", 0.2f);
			}
		}

		// 4. 새로운 규칙이 형성되었을 때만 효과음 재생
		bool ruleAdded = false;
		for (const auto& currentRule : mRules)
		{
			bool found = false;
			for (const auto& prevRule : prevRules)
			{
				if (currentRule.noun == prevRule.noun &&
					currentRule.verb == prevRule.verb &&
					currentRule.target == prevRule.target)
				{
					found = true;
					break;
				}
			}

			if (!found)
			{
				ruleAdded = true;
				break;
			}
		}

		if (ruleAdded)
		{
			AudioManager::PlaySFX(L"SentenceCompleteSFX");
		}
	}

	bool RuleManager::HasRule(eWordType noun, eWordType target)
	{
		for (const auto& rule : mRules)
		{
			if (rule.noun == noun && rule.target == target)
				return true;
		}
		return false;
	}

	bool RuleManager::IsNoun(eWordType type)
	{
		return (type == eWordType::Baba || type == eWordType::Rock ||
			type == eWordType::Wall || type == eWordType::Flag ||
			type == eWordType::Key || type == eWordType::Skull ||
			type == eWordType::Water || type == eWordType::Door);
	}

	bool RuleManager::IsProperty(eWordType type)
	{
		return (type == eWordType::You || type == eWordType::Push ||
			type == eWordType::Stop || type == eWordType::Win ||
			type == eWordType::Sink || type == eWordType::Defeat ||
			type == eWordType::Open || type == eWordType::Shut);
	}

	eWordType RuleManager::GetTypeByName(const std::wstring& name)
	{
		if (name == L"Baba") return eWordType::Baba;
		if (name == L"Rock") return eWordType::Rock;
		if (name == L"Wall") return eWordType::Wall;
		if (name == L"Flag") return eWordType::Flag;
		if (name == L"Key")  return eWordType::Key;
		if (name == L"Skull") return eWordType::Skull;
		if (name == L"Water") return eWordType::Water;
		if (name == L"Door")  return eWordType::Door;

		return eWordType::None;
	}
}
