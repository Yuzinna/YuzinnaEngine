#include "yuzinnaBabaScene.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaTransform.h"
#include "yuzinnaTilemapRenderer.h"
#include "yuzinnaResources.h"
#include "yuzinnaTexture.h"
#include "yuzinnaBabaGridComponent.h"
#include "yuzinnaBabaPlayerScript.h"
#include "yuzinnaBabaGridManager.h"
#include "yuzinnaObject.h"
#include "yuzinnaCamera.h"
#include "yuzinnaRenderer.h"
#include "yuzinnaAnimator.h"
namespace yuzinna
{
	BabaScene::BabaScene()
	{
	}

	BabaScene::~BabaScene()
	{
	}

	void BabaScene::Initialize()
	{
		// 1. 移대찓???ㅼ젙 (?붾㈃ 以묒븰??鍮꾩텛?꾨줉)
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(300.0f, 300.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;

		// 2. 寃⑹옄 ????ш린 ?ㅼ젙 (?? 48x48)
		TilemapRenderer::TileSize = Vector2(25.0f, 25.0f);

		// 3. 諛붾컮(Baba) 罹먮┃???앹꽦
		GameObject* baba = object::Instantiate<GameObject>(enums::eLayerType::Player);
		baba->SetName(L"BABA");

		// 鍮꾩＜???ㅼ젙 (Animator ?ъ슜)
		Animator* animator = baba->AddComponent<Animator>();
		graphics::Texture* babaDown = Resources::Find<graphics::Texture>(L"BabaDown");
		graphics::Texture* babaLeft = Resources::Find<graphics::Texture>(L"BabaLeft");
		graphics::Texture* babaRight = Resources::Find<graphics::Texture>(L"BabaRight");
		graphics::Texture* babaUp = Resources::Find<graphics::Texture>(L"BabaUp");

		// 96x72 ?쒗듃?먯꽌 24x24 ?ㅽ봽?쇱씠??
		// 媛?諛⑺뼢??4媛쒖쓽 ?좊땲硫붿씠???쒗듃(??瑜??앹꽦 (媛??댁? ?몃줈濡?3媛쒖쓽 轅덊?嫄곕━???꾨젅??
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

		// 寃⑹옄 ?쒖뒪???μ갑
		auto grid = baba->AddComponent<BabaGridComponent>();
		grid->SetName(L"BABA");
		grid->SetGridIndex(Vector2(5, 5)); // ?쒖옉 ?꾩튂 (5, 5)
		grid->SetAtlasIndex(Vector2(0, 0)); // 泥?踰덉㎏ ????대?吏
		
		// 議곗쥌 ?ㅽ겕由쏀듃 ?μ갑
		baba->AddComponent<BabaPlayerScript>();

		// 珥덇린 洹쒖튃 ?섎룞 ?ㅼ젙 ??? ?ㅼ젣 ?⑥뼱 釉붾줉??諛곗튂?섏뿬 洹쒖튃???뚯떛?섍쾶 ?⑸땲??
		// (BABA IS YOU)
		
		// BABA ?⑥뼱
		GameObject* wordBaba = object::Instantiate<GameObject>(enums::eLayerType::Player);
		wordBaba->SetName(L"WORD_BABA_OBJ");
		auto gridBaba = wordBaba->AddComponent<BabaGridComponent>();
		gridBaba->SetName(L"BABA"); // 洹쒖튃 ?뚯떛 ????대쫫
		gridBaba->SetGridIndex(Vector2(2, 2));
		gridBaba->AddProperty(eBabaProperty::WORD);
		gridBaba->AddProperty(eBabaProperty::PUSH);
		
		// ?쒓컖???쒖떆 (?꾩떆)
		auto trBaba = wordBaba->AddComponent<TilemapRenderer>();
		trBaba->SetTexture(Resources::Find<graphics::Texture>(L"BabaWord"));
		trBaba->SetSize(Vector2(1.0f, 1.0f));

		auto compBaba = wordBaba->AddComponent<BabaWordComponent>();
		compBaba->SetWordType(eWordType::BABA);

		// IS ?⑥뼱
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

		// YOU ?⑥뼱
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

		// 4. 紐⑤뱺 珥덇린???꾨즺 ????湲곕낯 珥덇린???몄텧
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
		// ?ъ뿉 吏꾩엯?섎㈃ 珥덇린 洹쒖튃 ?뚯떛 ?섑뻾
		BabaGridManager::ParseRules();
	}

	void BabaScene::OnExit()
	{
		Scene::OnExit();
	}
}
