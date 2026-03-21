#include "uginaTitleScene.h"
#include "uginaInput.h"
#include "uginaPlayer.h"
#include "uginaSceneManager.h"
#include "uginaAnimator.h"
namespace ugina
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{

		Scene::Initialize();
	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
		/*if (Input::GetKeyDown(keyCode::N))
		{
			SceneManager::LoadScene(L"PlayScene");
		}*/
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t str[50] = L"Title Scene";
		TextOut(hdc, 0, 0, str, 11);
	}
	void TitleScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void TitleScene::OnExit()
	{
		Scene::OnExit();
	}
}