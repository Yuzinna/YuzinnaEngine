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
		GameObject* word = object::Instantiate<GameObject>(enums::eLayerType::Word);
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
		case enums::eWordType::Sink:
			name = L"SinkWord";
			offKey = L"SinkOffWord";
			onKey = L"SinkOnWord";
			break;
		case enums::eWordType::Defeat:
			name = L"DefeatWord";
			offKey = L"DefeatOffWord";
			onKey = L"DefeatOnWord";
			break;
		case enums::eWordType::Wall:
			name = L"WallWord";
			offKey = L"WallOffWord";
			onKey = L"WallOnWord";
			break;
			/*case enums::eWordType::Flag:
				name = L"FlagWord";
				offKey = L"FlagOffWord";
				onKey = L"FlagOnWord";
				break;*/
		case enums::eWordType::Rock:
			name = L"RockWord";
			offKey = L"RockOffWord"; // TODO: 리소스 추가 필요 시 로딩 추가
			onKey = L"RockOnWord";
			break;
		case enums::eWordType::Key:
			name = L"KeyWord";
			offKey = L"KeyOffWord";
			onKey = L"KeyOnWord";
			break;
		case enums::eWordType::Skull:
			name = L"SkullWord";
			offKey = L"SkullOffWord";
			onKey = L"SkullOnWord";
			break;
		case enums::eWordType::Water:
			name = L"WaterWord";
			offKey = L"WaterOffWord";
			onKey = L"WaterOnWord";
			break;
		case enums::eWordType::Door:
			name = L"DoorWord";
			offKey = L"DoorOffWord";
			onKey = L"DoorOnWord";
			break;
		case enums::eWordType::Open:
			name = L"OpenWord";
			offKey = L"OpenOffWord";
			onKey = L"OpenOnWord";
			break;
		case enums::eWordType::Shut:
			name = L"ShutWord";
			offKey = L"ShutOffWord";
			onKey = L"ShutOnWord";
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

		// 모든 사물 오브젝트에 BabaScript를 추가하여 YOU 속성 부여 시 조종 가능하게 함
		obj->AddComponent<BabaScript>();

		GridManager::MoveObject(obj, gridPos);
		return obj;
		}

		GameObject* ObjectFactory::CreateKey(math::Vector2 gridPos)
		{
		return CreateNounObject(L"Key", L"Key", gridPos);
		}

		GameObject* ObjectFactory::CreateRock(math::Vector2 gridPos)
		{
		return CreateNounObject(L"Rock", L"Rock", gridPos);
		}

		GameObject* ObjectFactory::CreateSkull(math::Vector2 gridPos)
		{
		GameObject* skull = object::Instantiate<GameObject>(enums::eLayerType::Tile);
		skull->SetName(L"Skull");
		skull->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));
		skull->AddComponent<SpriteRenderer>();

		Animator* ani = skull->AddComponent<Animator>();
		graphics::Texture* tex = Resources::Find<graphics::Texture>(L"Skull");

		if (tex)
		{
			// 4개 방향 (우, 상, 좌, 하) 각각 3프레임 세로 애니메이션
			ani->CreateAnimation(L"SkullRight", tex, Vector2(0.0f, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
			ani->CreateAnimation(L"SkullUp",    tex, Vector2(24.0f, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
			ani->CreateAnimation(L"SkullLeft",  tex, Vector2(48.0f, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
			ani->CreateAnimation(L"SkullDown",  tex, Vector2(72.0f, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);

			ani->PlayAnimation(L"SkullRight", true);
		}

		// 해골도 조종 가능하도록 추가
		skull->AddComponent<BabaScript>();

		GridManager::MoveObject(skull, gridPos);
		return skull;
		}

		GameObject* ObjectFactory::CreateDoor(math::Vector2 gridPos)
		{
		return CreateNounObject(L"Door", L"Door", gridPos);
		}

		GameObject* ObjectFactory::CreateWater(math::Vector2 gridPos, const std::wstring& texKey)
		{
		return CreateNounObject(L"Water", texKey, gridPos);
		}

		GameObject* ObjectFactory::CreateByWordType(enums::eWordType type, math::Vector2 gridPos)
		{
			switch (type)
			{
			case enums::eWordType::Baba:  return CreateBaba(gridPos);
			case enums::eWordType::Rock:  return CreateRock(gridPos);
			case enums::eWordType::Wall:  return CreateNounObject(L"Wall", L"Wall_0", gridPos); // 기본 벽
			case enums::eWordType::Flag:  return CreateNounObject(L"Flag", L"Flag", gridPos);
			case enums::eWordType::Key:   return CreateKey(gridPos);
			case enums::eWordType::Skull: return CreateSkull(gridPos);
			case enums::eWordType::Water: return CreateWater(gridPos, L"Water_0"); // 기본 물
			case enums::eWordType::Door:  return CreateDoor(gridPos);
			default: break;
			}
			return nullptr;
		}

		void ObjectFactory::TransformObject(GameObject* obj, enums::eWordType toType)
		{
			if (obj == nullptr) return;

			Animator* ani = obj->GetComponent<Animator>();
			if (ani == nullptr) return;

			// 기존 애니메이션 모두 제거
			ani->ClearAnimations();

			std::wstring name = L"";
			std::wstring texKey = L"";

			switch (toType)
			{
			case enums::eWordType::Baba:
			{
				name = L"Baba";
				graphics::Texture* upTex = Resources::Find<graphics::Texture>(L"BabaUp");
				graphics::Texture* downTex = Resources::Find<graphics::Texture>(L"BabaDown");
				graphics::Texture* leftTex = Resources::Find<graphics::Texture>(L"BabaLeft");
				graphics::Texture* rightTex = Resources::Find<graphics::Texture>(L"BabaRight");

				for (int i = 0; i < 4; ++i)
				{
					ani->CreateAnimation(L"BabaUp_" + std::to_wstring(i), upTex, Vector2(24.0f * i, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
					ani->CreateAnimation(L"BabaDown_" + std::to_wstring(i), downTex, Vector2(24.0f * i, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
					ani->CreateAnimation(L"BabaLeft_" + std::to_wstring(i), leftTex, Vector2(24.0f * i, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
					ani->CreateAnimation(L"BabaRight_" + std::to_wstring(i), rightTex, Vector2(24.0f * i, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
				}
				ani->PlayAnimation(L"BabaRight_0", true);
			}
			break;

			case enums::eWordType::Skull:
			{
				name = L"Skull";
				graphics::Texture* tex = Resources::Find<graphics::Texture>(L"Skull");
				if (tex)
				{
					ani->CreateAnimation(L"SkullRight", tex, Vector2(0.0f, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
					ani->CreateAnimation(L"SkullUp", tex, Vector2(24.0f, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
					ani->CreateAnimation(L"SkullLeft", tex, Vector2(48.0f, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
					ani->CreateAnimation(L"SkullDown", tex, Vector2(72.0f, 0.0f), Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
					ani->PlayAnimation(L"SkullRight", true);
				}
			}
			break;

			case enums::eWordType::Rock:  name = L"Rock"; texKey = L"Rock"; break;
			case enums::eWordType::Wall:  name = L"Wall"; texKey = L"Wall_0"; break;
			case enums::eWordType::Flag:  name = L"Flag"; texKey = L"Flag"; break;
			case enums::eWordType::Key:   name = L"Key";  texKey = L"Key"; break;
			case enums::eWordType::Water: name = L"Water"; texKey = L"Water_0"; break;
			case enums::eWordType::Door:  name = L"Door"; texKey = L"Door"; break;
			default: break;
			}

			if (!texKey.empty())
			{
				graphics::Texture* tex = Resources::Find<graphics::Texture>(texKey);
				if (tex)
				{
					ani->CreateAnimation(L"Idle", tex, Vector2::Zero, Vector2(24, 24), Vector2::Zero, 3, 0.2f, true);
					ani->PlayAnimation(L"Idle", true);
				}
			}

			obj->SetName(name);
		}
		}
