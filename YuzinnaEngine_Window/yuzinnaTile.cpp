#include "yuzinnaTile.h"
#include "yuzinnaTransform.h"
#include "yuzinnaTilemapRenderer.h"
#include "yuzinnaTime.h"
#include "yuzinnaInput.h"
namespace yuzinna
{
	void Tile::Initialize()
	{
		GameObject::Initialize();
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Tile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Tile::SetIndexPosition(int x, int y)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos;

		pos.x = x * TilemapRenderer::TileSize.x;
		pos.y = y * TilemapRenderer::TileSize.y;
		tr->SetPosition(pos);
	}
}
