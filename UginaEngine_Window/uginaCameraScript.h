#pragma once
#include "..\\UginaEngine_SOURCE\\uginaScript.h"
#include "..\\UginaEngine_SOURCE\\\uginaTransform.h"
namespace ugina
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

