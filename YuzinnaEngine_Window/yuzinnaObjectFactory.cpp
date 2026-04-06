#include "yuzinnaObjectFactory.h"
#include "yuzinnaObject.h"
#include "yuzinnaTransform.h"
#include "yuzinnaSpriteRenderer.h"
#include "yuzinnaAnimator.h"
#include "yuzinnaWord.h"
#include "yuzinnaBabaScript.h"
#include "yuzinnaResources.h"
#include "yuzinnaTexture.h"
#include "yuzinnaGridManager.h"
#include "yuzinnaTilemapRenderer.h"

namespace yuzinna
{
	GameObject* ObjectFactory::CreateBaba(math::Vector2 gridPos)
	{
		GameObject* baba = object::Instantiate<GameObject>(enums::eLayerType::Player);
		baba->SetName(L"Baba");
		baba->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

		baba->AddComponent<SpriteRenderer>();
		Animator* ani = baba->AddComponent<Animator>();

		graphics::Texture* upTex = Resources::Find<graphics::Texture>(L"BabaUp");
		graphics::Texture* downTex = Resources::Find<graphics::Texture>(L"BabaDown");
		graphics::Texture* leftTex = Resources::Find<graphics::Texture>(L"BabaLeft");
		graphics::Texture* rightTex = Resources::Find<graphics::Texture>(L"BabaRight");

		// 4방향 * 4버전 애니메이션 생성
		for (int i = 0; i < 4; ++i)
		{
			ani->CreateAnimation(L"BabaUp_" + std::to_wstring(i), upTex, Vector2(24.0f * i, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
			ani->CreateAnimation(L"BabaDown_" + std::to_wstring(i), downTex, Vector2(24.0f * i, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
			ani->CreateAnimation(L"BabaLeft_" + std::to_wstring(i), leftTex, Vector2(24.0f * i, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
			ani->CreateAnimation(L"BabaRight_" + std::to_wstring(i), rightTex, Vector2(24.0f * i, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
		}

		ani->PlayAnimation(L"BabaRight_0", true);
		baba->AddComponent<BabaScript>();

		GridManager::MoveObject(baba, gridPos);
		return baba;
	}

	GameObject* ObjectFactory::CreateWord(enums::eWordType type, math::Vector2 gridPos)
	{
		GameObject* word = object::Instantiate<GameObject>(enums::eLayerType::Tile);
		word->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));
		word->AddComponent<SpriteRenderer>();

		Word* wordComp = word->AddComponent<Word>();
		wordComp->SetWordType(type);

		Animator* wordAni = word->AddComponent<Animator>();
		std::wstring offKey = L"";
		std::wstring onKey = L"";
		std::wstring name = L"";

		// 타입에 따른 텍스처 키 매핑
		switch (type)
		{
		case enums::eWordType::Baba:
			name = L"BabaWord";
			offKey = L"BabaOffWord";
			onKey = L"BabaOnWord";
			break;
		case enums::eWordType::Is:
			name = L"IsWord";
			offKey = L"IsOffWord";
			onKey = L"IsOnWord";
			break;
		case enums::eWordType::You:
			name = L"YouWord";
			offKey = L"YouOffWord";
			onKey = L"YouOnWord";
			break;
		case enums::eWordType::Flag:
			name = L"FlagWord";
			offKey = L"FlagOffWord";
			onKey = L"FlagOnWord";
			break;
		case enums::eWordType::Win:
			name = L"WinWord";
			offKey = L"WinOffWord";
			onKey = L"WinOnWord";
			break;
		case enums::eWordType::Stop:
			name = L"StopWord";
			offKey = L"StopOffWord";
			onKey = L"StopOnWord";
			break;
		case enums::eWordType::Push:
			name = L"PushWord";
			offKey = L"PushOffWord";
			onKey = L"PushOnWord";
			break;
		case enums::eWordType::Wall:
			name = L"WallWord";
			offKey = L"WallOffWord";
			onKey = L"WallOnWord";
			break;
		default:
			name = L"UnknownWord";
			break;
		}

		word->SetName(name);
		graphics::Texture* offTex = Resources::Find<graphics::Texture>(offKey);
		graphics::Texture* onTex = Resources::Find<graphics::Texture>(onKey);

		if (offTex) wordAni->CreateAnimation(L"Off", offTex, Vector2::Zero, Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
		if (onTex) wordAni->CreateAnimation(L"On", onTex, Vector2::Zero, Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);

		wordAni->PlayAnimation(L"On", true);
		GridManager::MoveObject(word, gridPos);

		return word;
	}

	GameObject* ObjectFactory::CreateNounObject(const std::wstring& name, const std::wstring& texKey, math::Vector2 gridPos)
	{
		GameObject* obj = object::Instantiate<GameObject>(enums::eLayerType::Tile);
		obj->SetName(name);
		obj->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));
		obj->AddComponent<SpriteRenderer>();

		Animator* ani = obj->AddComponent<Animator>();
		graphics::Texture* tex = Resources::Find<graphics::Texture>(texKey);
		if (tex)
		{
			ani->CreateAnimation(L"Idle", tex, Vector2::Zero, Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
			ani->PlayAnimation(L"Idle", true);
		}

		GridManager::MoveObject(obj, gridPos);
		return obj;
	}
}
