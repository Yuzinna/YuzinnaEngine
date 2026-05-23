#pragma once
#include "yuzinnaScene.h"
namespace yuzinna
{
	//씬들을 관리해주는 클래스
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name)
		{
			//내부에서 씬을 만들어서 이름을 저장하고, 초기화를 실행해줌 
			T* scene = new T();
			scene->SetName(name);			Scene* prevActiveScene = mActiveScene;//이전씬을 보관

			mActiveScene = scene;
			scene->Initialize();
						mActiveScene = prevActiveScene;

			//씬매니저에서 관리하는 mScene 자료구조에 {이름(key),scene(value)}을 한쌍으로 하는 노드를 저장시킴
			mScene.insert(std::make_pair(name, scene));
			//만들어진 씬을 리턴함(참조가 아닌 포인터를 리턴하는 이유는 자료구조에 넣을려고)
			return scene;
		}
		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* GetDontDestroyOnLoad() { return mDontDestroyOnLoad; }
		static std::vector<GameObject*> GetGameObjects(eLayerType layer);
		static void Initialize();
		//현재 선택된 씬(mActiveScene)에서 해야할 로직을 실행시키는 함수
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

		static void Destroy();
		//씬들의 메모리를 해제시켜주는 함수
		static void Release();
	private:
		//모든 씬을 담는 자료구조 map(트리구조)
		static std::map<std::wstring, Scene*> mScene;
		//씬 매니저에서 현재 활성화 되어있는 씬
		static Scene* mActiveScene; 
		static Scene* mDontDestroyOnLoad;
	};
	
}
