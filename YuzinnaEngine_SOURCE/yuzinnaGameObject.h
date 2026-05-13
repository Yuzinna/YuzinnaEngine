#pragma once
#include "CommonInclude.h"
#include "yuzinnaComponent.h"
#include "yuzinnaCollider.h"
#include <vector>

namespace yuzinna
{
	namespace object
	{
		void Destroy(GameObject* gameObject);
	}
}
namespace yuzinna
{

	class GameObject : public Entity
	{
	public:
		friend void object::Destroy(GameObject* obj);
		enum class eState
		{
			//활성
			Active,
			//일시정지
			Paused,
			//사망
			Dead,
			End
		};

		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			comp->SetOwner(this);
			comp->Initialize();
			enums::eComponentType type = comp->GetType();
			switch (type)
			{
			case yuzinna::enums::eComponentType::Transform:
				comp->SetName(L"Transform");
				break;
			case yuzinna::enums::eComponentType::Collider:
				comp->SetName(L"Collider");
				break;
			case yuzinna::enums::eComponentType::Rigidbody:
				comp->SetName(L"Rigidbody");
				break;
			case yuzinna::enums::eComponentType::Script:
				comp->SetName(L"Script");
				break;
			case yuzinna::enums::eComponentType::SpriteRenderer:
				comp->SetName(L"SpriteRenderer");
				break;
			case yuzinna::enums::eComponentType::Animator:
				comp->SetName(L"Animator");
				break;
			case yuzinna::enums::eComponentType::Camera:
				comp->SetName(L"Camera");
				break;
			case yuzinna::enums::eComponentType::AudioListener:
				comp->SetName(L"AudioListener");
				break;
			case yuzinna::enums::eComponentType::AudioSource:
				comp->SetName(L"AudioSource");
				break;
			case yuzinna::enums::eComponentType::End:
				break;
			default:
				break;
			}
			// 타입별 인덱스 대신 벡터에 순차적으로 추가하여 여러 컴포넌트(스크립트) 허용
			mComponents.push_back(comp);

			return comp;
		}
		template <typename T>
		T* GetComponent()
		{

			T* component = nullptr;
			for (Component* comp : mComponents)
			{
				//mComponents 안에 있는 컴포넌트들을 하나하나 캐스팅해봄
				component = dynamic_cast<T*>(comp);
				//캐스팅한 결과가 성공하여 component 안에 들어가면 반복문 탈출
				if (component)
				{
					break;
				}
			}
			return component;
		}
		eState GetState() { return mState; }
		void SetActive(bool power)
		{
			if (power == true)
			{
				mState = eState::Active;
			}
			if (power == false)
			{
				mState = eState::Paused;
			}
		}
		          
		bool IsActive() { return  mState == eState::Active; }
		bool IsDead() { return mState == eState::Dead; }

		void SetLayerType(eLayerType layerType) { mLayerType = layerType; }
		eLayerType GetLayerType() { return mLayerType; }
	private:
		void initializeTransform();
		void death() { mState = eState::Dead; }
	private:
		eState mState;
		std::vector<Component*> mComponents;
		eLayerType mLayerType;

	};
}
