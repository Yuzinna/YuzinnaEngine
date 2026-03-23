#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaComponent.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaEnums.h"

namespace yuzinna
{
	using namespace enums;

	class Word : public Component
	{
	public:
		Word();
		~Word();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

		void SetWordType(eWordType type) { mType = type; }
		eWordType GetWordType() { return mType; }

		void SetActive(bool active) { mbActive = active; }
		bool IsActive() { return mbActive; }

	private:
		eWordType mType;
		bool mbActive;
		bool mbPrevActive;
	};
}
