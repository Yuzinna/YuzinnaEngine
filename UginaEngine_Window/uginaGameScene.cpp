#include "uginaGameScene.h"
#include "uginaPlayScene.h"
#include "uginaGameObject.h"
#include "uginaPlayer.h"
#include "uginaTransform.h"
#include "uginaSpriteRenderer.h"
#include "uginaInput.h"
#include "uginaTitleScene.h"
#include "uginaSceneManager.h"
#include "uginaObject.h"
#include "uginaTexture.h"
#include "uginaResources.h"
#include "uginaPlayerScript.h"
#include "uginaCamera.h"
#include "uginaRenderer.h"
#include "uginaAnimator.h"
#include "uginaCat.h"
#include "uginaCatScript.h"
#include "uginaBoxCollider2D.h"
#include "uginaCircleCollider2D.h"
#include "uginaCollisionManager.h"
#include "uginaTile.h"
#include "uginaTilemapRenderer.h"
#include "uginaRigidbody.h"
#include "uginaFloor.h"
#include "uginaFloorScript.h"

namespace ugina
{
    GameScene::GameScene()
    {
    }
    GameScene::~GameScene()
    {
    }
    void GameScene::Initialize()
    {
        // 1. 카메라 생성
        //GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(0.0f, 0.0f));
        GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(336.0f, 423.0f));
        Camera* cameraComp = camera->AddComponent<Camera>();
        renderer::mainCamera = cameraComp;


        // 2. 플레이어 생성 및 스크립트 추가
        mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
        mPlayer->AddComponent<PlayerScript>();

        // 3. 외형 설정을 위한 SpriteRenderer 추가 (리소스 로드 확인 필요)
        SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
        
        graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Player");
            if (playerTex)
            {
                sr->SetTexture(playerTex);
            }


        // 4. 초기 위치 설정
        mPlayer->GetComponent<Transform>()->SetPosition(Vector2(336.0f, 423.0f));


        Scene::Initialize();
    }
    void GameScene::Update()
    {
        Scene::Update();
    }
    void GameScene::LateUpdate()
    {
        Scene::LateUpdate();
    }
    void GameScene::Render(HDC hdc)
    {
        Scene::Render(hdc);
    }
    void GameScene::OnEnter()
    {
        Scene::OnEnter();
    }
    void GameScene::OnExit()
    {
        Scene::OnExit();
    }
}