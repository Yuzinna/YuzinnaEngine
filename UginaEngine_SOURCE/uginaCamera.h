#pragma once
#include "uginaComponent.h"

namespace ugina
{
	using namespace ugina::math;
	class Camera :public Component
	{
	public:

		//좌표의 기준은 카메라를 기준으로 한다
		//오브젝트의 좌푯값으로부터 카메라가 이동한 거리만큼 빼서
		//카메라의 좌푯값을 기준으로 오브젝트의 pos를 다시계산(즉 리턴값은 오브젝트의 새로운좌푯값)
		Vector2 CalculatePosition(Vector2 pos) { return pos - mDistance; }
		Vector2 CalculateTilePosition(Vector2 pos) { return pos + mDistance; }

		Camera();
		~Camera();
		void Initialize()		override;
		void Update()			override;
		void LateUpdate()		override;
		void Render(HDC hdc)	override;

		void SetTarget(GameObject* target) { mTarget = target; }
	private:
		 GameObject* mTarget;
		 //카메라가 이동한 거리
		 Vector2 mDistance;
		 //키메라의 해상도
		 Vector2 mResolution;
		 //카메라가 바라보는 좌표
		 Vector2 mLookPosition;
	};
}
