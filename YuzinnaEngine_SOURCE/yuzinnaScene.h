#pragma once
#include "yuzinnaEntity.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaLayer.h"
namespace yuzinna
{

	//게임의 장면
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObj, const enums::eLayerType type);
		void EraseGameObject(GameObject* gameObj);
		void MoveGameObjectLayer(GameObject* gameObj, const enums::eLayerType type);
		Layer* GetLayer(const enums::eLayerType type) { return mLayers[(UINT)type]; }
	private: 
		void createLayers();

	private:
		//씬에서 모든 게임오브젝트는 레이어라는 더큰 분류에 저장되어 나뉘어 진다.
		std::vector<Layer*> mLayers;
	};

}

