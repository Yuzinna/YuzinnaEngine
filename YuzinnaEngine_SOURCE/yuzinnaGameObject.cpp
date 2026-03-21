#include "yuzinnaGameObject.h"
#include "yuzinnaInput.h"
#include "yuzinnaTime.h"
#include "yuzinnaTransform.h"

namespace yuzinna::object
{
	void Destroy(GameObject* gameObject)
	{
		if (gameObject != nullptr)
		{
			gameObject->death();
		}
	}
}
namespace yuzinna
{
	GameObject::GameObject()
		:mState(eState::Active)
		,mLayerType(eLayerType::None)
	{
		// 이전에 고정 크기로 컴포넌트를 할당하던 방식을 가변 벡터(push_back) 방식으로 수정
		initializeTransform();
	}

	GameObject::~GameObject()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
			{
				continue;
			}
			//메모리 해제
			delete com;
			//메모리를 nullptr로 초기화
			com = nullptr;
		}
	}
	void GameObject::Initialize()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
			{
				continue;
			}
			com->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
			{
				continue;
			}
			com->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
			{
				continue;
			}
			com->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* com : mComponents)
		{
			if (com == nullptr)
			{
				continue;
			}
			com->Render(hdc);
		}
	}

	void GameObject::initializeTransform()
	{
		AddComponent<Transform>();
	}
}
