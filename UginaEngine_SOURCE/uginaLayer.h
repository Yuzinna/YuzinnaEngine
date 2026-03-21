#pragma once
#include "uginaEntity.h"
#include "CommonInclude.h"
#include "uginaGameObject.h"
namespace ugina
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Destroy();
		//게임 오브젝트를 없애는 함수 여기에 한번에 모아서 삭제 시킨다.
		

		void AddGameObject(GameObject* gameObject);
		void EraseGameObject(GameObject* eraseGameObj);
		const std::vector<GameObject*> GetGameObjects() { return mGameObjects; }
	private:
		void findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs);
		void deleteGameObjects(std::vector<GameObject*> deleteObjs);
		
		void eraseDeadGameObject();
	private:
		std::vector<GameObject*> mGameObjects;
	};
	//너무 이름이 길어서 줄임
	typedef std::vector<GameObject*>::iterator GameObjectIter;
}