#include "yuzinnaTilemapRenderer.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaTransform.h"
#include "yuzinnaTexture.h"
#include "yuzinnaRenderer.h"

namespace yuzinna
{
	Vector2 TilemapRenderer::TileSize = Vector2(48.0f, 48.0f);
	Vector2 TilemapRenderer::OriginTileSize = Vector2(48.0f, 48.0f);
	Vector2 TilemapRenderer::SelectedIndex = Vector2::One;

	TilemapRenderer::TilemapRenderer()
		:Component(enums::eComponentType::SpriteRenderer)
		,mTexture(nullptr)
		,mSize(1.0f,1.0f)
		,mIndex(0,0)
		,mTileSize(Vector2(24.0f,24.0f))
	{
		if (mTileSize.x > 0 && mTileSize.y > 0)
		{
			mSize.x = TileSize.x / mTileSize.x;
			mSize.y = TileSize.y / mTileSize.y;
		}
		OriginTileSize = mTileSize;
	}


	TilemapRenderer::~TilemapRenderer()
	{
	}
	void TilemapRenderer::Initialize()
	{
	}
	void TilemapRenderer::Update()
	{
	}
	void TilemapRenderer::LateUpdate()
	{
	}
	void TilemapRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr)
		{
			assert(false);
		}
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		pos = renderer::mainCamera->CalculatePosition(pos);
		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
		{
			if (mTexture->IsAlpha())
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

				AlphaBlend(hdc
					, pos.x, pos.y
					, mTileSize.x * mSize.x * scale.x
					, mTileSize.y * mSize.y * scale.y
					, mTexture->GetHdc()
					, mIndex.x * mTileSize.x, mIndex.y * mTileSize.y
					, mTileSize.x
					, mTileSize.y
					, func);
			}
			else
			{
				//https://blog.naver.com/power2845/50147965306
				TransparentBlt(hdc
					, pos.x, pos.y
					, mTileSize.x * mSize.x * scale.x
					, mTileSize.y * mSize.y * scale.y
					, mTexture->GetHdc()
					, mIndex.x * mTileSize.x, mIndex.y * mTileSize.y
					, mTileSize.x
					, mTileSize.y
					, RGB(255, 0, 255));
			}
		}
	}
}