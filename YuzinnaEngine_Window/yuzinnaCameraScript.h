#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaScript.h"
#include "..\\YuzinnaEngine_SOURCE\\\yuzinnaTransform.h"
namespace yuzinna
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
	};
}

