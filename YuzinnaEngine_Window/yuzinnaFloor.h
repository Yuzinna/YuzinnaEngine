#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaGameObject.h"
namespace yuzinna
{
	class Floor: public GameObject
	{
	public:
		Floor();
		~Floor();

		void Initialize()override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;
	private:

	};
}

