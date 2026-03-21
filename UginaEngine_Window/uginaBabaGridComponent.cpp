#include "uginaBabaGridComponent.h"
#include "uginaTransform.h"
#include "uginaTilemapRenderer.h"
#include "uginaGameObject.h"

namespace ugina
{
	BabaGridComponent::BabaGridComponent()
		: mGridIndex(math::Vector2::Zero)
		, mAtlasIndex(math::Vector2::Zero)
	{
	}

	BabaGridComponent::~BabaGridComponent()
	{
	}

	void BabaGridComponent::Initialize()
	{
	}

	void BabaGridComponent::Update()
	{
		// 1. 화면 위치를 그리드 인덱스에 맞춰 실시간 동기화
		Transform* tr = GetOwner()->GetComponent<Transform>();
		if (tr)
		{
			math::Vector2 screenPos;
			screenPos.x = mGridIndex.x * TilemapRenderer::TileSize.x;
			screenPos.y = mGridIndex.y * TilemapRenderer::TileSize.y;
			tr->SetPosition(screenPos);
		}

		// 2. 타일맵 렌더러의 인덱스를 아틀라스 인덱스와 동기화
		TilemapRenderer* tmr = GetOwner()->GetComponent<TilemapRenderer>();
		if (tmr)
		{
			tmr->SetIndex(mAtlasIndex);
		}
	}

	void BabaGridComponent::AddProperty(eBabaProperty prop)
	{
		if (!HasProperty(prop)) mProperties.push_back(prop);
	}

	void BabaGridComponent::RemoveProperty(eBabaProperty prop)
	{
		for (auto it = mProperties.begin(); it != mProperties.end(); ++it)
		{
			if (*it == prop) { mProperties.erase(it); break; }
		}
	}

	bool BabaGridComponent::HasProperty(eBabaProperty prop)
	{
		for (auto p : mProperties) { if (p == prop) return true; }
		return false;
	}
}
