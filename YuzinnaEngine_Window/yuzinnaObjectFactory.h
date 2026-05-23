#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaGameObject.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaEnums.h"

namespace yuzinna
{
	class ObjectFactory
	{
	public:
		// 바바 캐릭터 생성 (16개 애니메이션)
		static GameObject* CreateBaba(math::Vector2 gridPos);

		// 단어 블록 생성 (On/Off 애니메이션 및 Word 컴포넌트 추가)
		static GameObject* CreateWord(enums::eWordType type, math::Vector2 gridPos);

		// 일반 사물 생성 - 벽, 바위, 깃발 등 (3프레임 애니메이션)
		static GameObject* CreateNounObject(const std::wstring& name, const std::wstring& texKey, math::Vector2 gridPos);
		static GameObject* CreateKey(math::Vector2 gridPos);
		static GameObject* CreateRock(math::Vector2 gridPos);
		static GameObject* CreateSkull(math::Vector2 gridPos);
		static GameObject* CreateDoor(math::Vector2 gridPos);
		static GameObject* CreateWater(math::Vector2 gridPos, const std::wstring& texKey);
	};
}
