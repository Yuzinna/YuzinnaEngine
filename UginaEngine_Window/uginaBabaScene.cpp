#include "uginaBabaScene.h"
#include "uginaGameObject.h"
#include "uginaTransform.h"
#include "uginaTilemapRenderer.h"
#include "uginaResources.h"
#include "uginaTexture.h"
#include "uginaBabaGridComponent.h"
#include "uginaBabaPlayerScript.h"
#include "uginaBabaGridManager.h"
#include "uginaObject.h"
#include "uginaCamera.h"
#include "uginaRenderer.h"
#include "uginaAnimator.h"
namespace ugina
{
	BabaScene::BabaScene()
	{
	}

	BabaScene::~BabaScene()
	{
	}

	void BabaScene::Initialize()
	{
		// 1. 카메라 설정 (화면 중앙을 비추도록)
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(300.0f, 300.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;

		// 2. 격자 타일 크기 설정 (예: 48x48)
		TilemapRenderer::TileSize = Vector2(25.0f, 25.0f);

		// 3. 바바(Baba) 캐릭터 생성
		GameObject* baba = object::Instantiate<GameObject>(enums::eLayerType::Player);
		baba->SetName(L"BABA");

		// 비주얼 설정 (Animator 사용)
		Animator* animator = baba->AddComponent<Animator>();
		graphics::Texture* babaDown = Resources::Find<graphics::Texture>(L"BabaDown");
		graphics::Texture* babaLeft = Resources::Find<graphics::Texture>(L"BabaLeft");
		graphics::Texture* babaRight = Resources::Find<graphics::Texture>(L"BabaRight");
		graphics::Texture* babaUp = Resources::Find<graphics::Texture>(L"BabaUp");

		// 96x72 시트에서 24x24 스프라이트
		// 각 방향당 4개의 애니메이션 시트(열)를 생성 (각 열은 세로로 3개의 꿈틀거리는 프레임)
		for (int i = 0; i < 4; ++i)
		{
			std::wstring suffix = std::to_wstring(i);
			animator->CreateAnimation(L"BabaDown_" + suffix, babaDown, Vector2(25.0f * i, 0.0f), Vector2(25.0f, 25.0f), Vector2::Zero, 3, 0.3f, true);
			animator->CreateAnimation(L"BabaLeft_" + suffix, babaLeft, Vector2(25.0f * i, 0.0f), Vector2(25.0f, 25.0f), Vector2::Zero, 3, 0.3f, true);
			animator->CreateAnimation(L"BabaRight_" + suffix, babaRight, Vector2(25.0f * i, 0.0f), Vector2(25.0f, 25.0f), Vector2::Zero, 3, 0.3f, true);
			animator->CreateAnimation(L"BabaUp_" + suffix, babaUp, Vector2(25.0f * i, 0.0f), Vector2(25.0f, 25.0f), Vector2::Zero, 3, 0.3f, true);
		}

		animator->PlayAnimation(L"BabaRight_0");
		baba->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f)); // 24x24 -> 48x48

		// 격자 시스템 장착
		auto grid = baba->AddComponent<BabaGridComponent>();
		grid->SetName(L"BABA");
		grid->SetGridIndex(Vector2(5, 5)); // 시작 위치 (5, 5)
		grid->SetAtlasIndex(Vector2(0, 0)); // 첫 번째 타일 이미지
		
		// 조종 스크립트 장착
		baba->AddComponent<BabaPlayerScript>();

		// 초기 규칙 수동 설정 대신, 실제 단어 블록을 배치하여 규칙이 파싱되게 합니다.
		// (BABA IS YOU)
		
		// BABA 단어
		GameObject* wordBaba = object::Instantiate<GameObject>(enums::eLayerType::Player);
		wordBaba->SetName(L"WORD_BABA_OBJ");
		auto gridBaba = wordBaba->AddComponent<BabaGridComponent>();
		gridBaba->SetName(L"BABA"); // 규칙 파싱 대상 이름
		gridBaba->SetGridIndex(Vector2(2, 2));
		gridBaba->AddProperty(eBabaProperty::WORD);
		gridBaba->AddProperty(eBabaProperty::PUSH);
		
		// 시각적 표시 (임시)
		auto trBaba = wordBaba->AddComponent<TilemapRenderer>();
		trBaba->SetTexture(Resources::Find<graphics::Texture>(L"BabaWord"));
		trBaba->SetSize(Vector2(1.0f, 1.0f));

		auto compBaba = wordBaba->AddComponent<BabaWordComponent>();
		compBaba->SetWordType(eWordType::BABA);

		// IS 단어
		GameObject* wordIs = object::Instantiate<GameObject>(enums::eLayerType::Player);
		wordIs->SetName(L"WORD_IS_OBJ");
		auto gridIs = wordIs->AddComponent<BabaGridComponent>();
		gridIs->SetName(L"IS");
		gridIs->SetGridIndex(Vector2(3, 2));
		gridIs->AddProperty(eBabaProperty::WORD);
		gridIs->AddProperty(eBabaProperty::PUSH);

		auto trIs = wordIs->AddComponent<TilemapRenderer>();
		trIs->SetTexture(Resources::Find<graphics::Texture>(L"Player"));
		trIs->SetSize(Vector2(0.1f, 0.1f));

		auto compIs = wordIs->AddComponent<BabaWordComponent>();
		compIs->SetWordType(eWordType::IS);

		// YOU 단어
		GameObject* wordYou = object::Instantiate<GameObject>(enums::eLayerType::Player);
		wordYou->SetName(L"WORD_YOU_OBJ");
		auto gridYou = wordYou->AddComponent<BabaGridComponent>();
		gridYou->SetName(L"YOU");
		gridYou->SetGridIndex(Vector2(4, 2));
		gridYou->AddProperty(eBabaProperty::WORD);
		gridYou->AddProperty(eBabaProperty::PUSH);

		auto trYou = wordYou->AddComponent<TilemapRenderer>();
		trYou->SetTexture(Resources::Find<graphics::Texture>(L"Player"));
		trYou->SetSize(Vector2(0.1f, 0.1f));

		auto compYou = wordYou->AddComponent<BabaWordComponent>();
		compYou->SetWordType(eWordType::YOU);

		// 4. 모든 초기화 완료 후 씬 기본 초기화 호출
		Scene::Initialize();
	}

	void BabaScene::Update()
	{
		Scene::Update();
	}

	void BabaScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void BabaScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void BabaScene::OnEnter()
	{
		Scene::OnEnter();
		// 씬에 진입하면 초기 규칙 파싱 수행
		BabaGridManager::ParseRules();
	}

	void BabaScene::OnExit()
	{
		Scene::OnExit();
	}
}
