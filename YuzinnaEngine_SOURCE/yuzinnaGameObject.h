#pragma once
#include "CommonInclude.h"
#include "yuzinnaComponent.h"
#include "yuzinnaCollider.h"
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
			//Ȱ��
			Active,
			//������
			Paused,
			//����
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
			comp->Initialize();
			comp->SetOwner(this);

			//������ ���� Ǫ�� ���Լ��� ���� ��ſ� enums Ÿ���� �ε����� ���
			//mComponets.push_back(comp);
			mComponents[(UINT)comp->GetType()] = comp;

			return comp;
		}
		template <typename T>
		T* GetComponent()
		{

			T* component = nullptr;
			for (Component* comp : mComponents)
			{
				//mComponents�ȿ� �ִ� ������Ʈ���� �ϳ��ϳ� ĳ�����غ�
				component = dynamic_cast<T*>(comp);
				//ĳ�����Ѱ��� �ߵǼ� component�ȿ� ���� �ݺ��� Ż��
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


