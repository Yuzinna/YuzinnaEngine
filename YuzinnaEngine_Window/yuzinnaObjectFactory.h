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

		// [추가] WordType을 기반으로 해당하는 사물 오브젝트를 생성합니다. (변이 로직용)
		static GameObject* CreateByWordType(enums::eWordType type, math::Vector2 gridPos);

		// [추가] 기존 오브젝트를 새로운 타입으로 변이시킵니다. (Undo 호환성을 위해 포인터 유지)
		static void TransformObject(GameObject* obj, enums::eWordType toType);
	};
}
