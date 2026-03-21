#pragma once
#include "uginaScene.h"
namespace ugina
{
	class GameScene : public Scene
	{
	private :
		class Player* mPlayer;
	public :

		GameScene();
		~GameScene();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC	hdc) override;

		void OnEnter() override;
		void OnExit() override;
	};
}

