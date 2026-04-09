#include "yuzinnaLayer.h"
#include "yuzinnaGameObject.h"
namespace yuzinna
{
	Layer::Layer() : mGameObjects{}
	{

	}
	Layer::~Layer()
	{
		for (GameObject* gameobj : mGameObjects)
		{
			if (gameobj == nullptr)
			{
				continue;
			}
			delete gameobj;
			gameobj = nullptr;
		}
	}
	void Layer::Initialize()
	{
		for (GameObject* gameObj: mGameObjects)
		{
			if (gameObj == nullptr)
			{
				continue;
			}
			gameObj->Initialize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* gameObj: mGameObjects)
		{
			if (gameObj == nullptr)
			{
				continue;
			}
			//현재 게임오브젝트의 상태가 멈춤 혹은 죽은 상태면 스킵
			if (gameObj->IsActive()==false)
			{
				continue;
			}
			gameObj->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (GameObject* gameObj: mGameObjects)
		{
			if (gameObj == nullptr)
			{
				continue;
			}
			//현재 게임오브젝트의 상태가 멈춤 혹은 죽은 상태면 스킵
			if (gameObj->IsActive() == false)
			{
				continue;
			}
			gameObj->LateUpdate();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
			{
				continue;
			}
			
			//현재 게임오브젝트의 상태가 멈춤 혹은 죽은 상태면 스킵
			if (gameObj->IsActive() == false)
			{
				continue;
			}
			gameObj->Render(hdc);
		}
	}
	void Layer::Destroy()
	{
		// Baba Is You의 Undo 기능을 위해 스테이지 도중 Dead 상태가 된 오브젝트를 실제로 삭제하지 않습니다.
		// 실제 삭제는 씬을 나갈 때나 스테이지가 초기화될 때 수행됩니다.

		/*std::vector<GameObject*> deleteObjects = {};
		findDeadGameObjects(deleteObjects);
		eraseDeadGameObject();
		deleteGameObjects(deleteObjects);*/
	}
	void Layer::AddGameObject(GameObject* gameObject)
	{

		if (gameObject == nullptr)
		{
			return;
		}
		mGameObjects.push_back(gameObject);
	}
	void Layer::EraseGameObject(GameObject* eraseGameObj)
	{
		std::erase_if(mGameObjects, [=](GameObject* gameobj)
			{
				return gameobj == eraseGameObj; 
			});
	}
	void Layer::findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs)
	{
		//gameObjs는 삭제할 게임오브젝트들의 포인터를 담는 임시공간
		for (GameObject* gameObj : mGameObjects)
		{
			GameObject::eState active = gameObj->GetState();
			if (active == GameObject::eState::Dead)
			{
				gameObjs.push_back(gameObj);
			}
		}
	}
	void Layer::deleteGameObjects(std::vector<GameObject*> deleteObjs)
	{
		for (GameObject* obj : deleteObjs)
		{
			delete obj;
			obj = nullptr;
		}
		
	}
	
	void Layer::eraseDeadGameObject()
	{
		std::erase_if(mGameObjects, [](GameObject* gameObj) 
			{
				return gameObj->IsDead(); 
			});
	}
}