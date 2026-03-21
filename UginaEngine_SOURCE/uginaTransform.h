#pragma once
#include "uginaEntity.h"
#include "uginaComponent.h"
namespace ugina
{
	using namespace math;
	class Transform :public Component
	{
	public:
		Transform();
		~Transform();

		 void Initialize() override;
		 void Update() override;
		 void LateUpdate() override;
		 void Render(HDC hdc) override;

		void SetPosition(Vector2 pos) { mPosition.x = pos.x; mPosition.y = pos.y; }
		Vector2 GetPosition() { return mPosition; }
		float GetRotation() { return mRotation; }
		void SetRotation(float rotate) { mRotation = rotate; }
		Vector2 GetScale() { return mScale; }
		void SetScale(Vector2 scale) { mScale = scale; }

	private:
		//오브젝트의 정중앙이다
		Vector2 mPosition;
		Vector2 mScale;
		float mRotation;

	};
}

