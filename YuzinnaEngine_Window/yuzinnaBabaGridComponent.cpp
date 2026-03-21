#include "yuzinnaBabaGridComponent.h"
#include "yuzinnaTransform.h"
#include "yuzinnaTilemapRenderer.h"
#include "yuzinnaGameObject.h"

namespace yuzinna
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
		// 1. ?붾㈃ ?꾩튂瑜?洹몃━???몃뜳?ㅼ뿉 留욎떠 ?ㅼ떆媛??숆린??
		Transform* tr = GetOwner()->GetComponent<Transform>();
		if (tr)
		{
			math::Vector2 screenPos;
			screenPos.x = mGridIndex.x * TilemapRenderer::TileSize.x;
			screenPos.y = mGridIndex.y * TilemapRenderer::TileSize.y;
			tr->SetPosition(screenPos);
		}

		// 2. ??쇰㏊ ?뚮뜑?ъ쓽 ?몃뜳?ㅻ? ?꾪??쇱뒪 ?몃뜳?ㅼ? ?숆린??
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
