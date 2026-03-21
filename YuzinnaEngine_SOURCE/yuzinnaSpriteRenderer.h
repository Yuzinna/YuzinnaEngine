#pragma once
#include "yuzinnaEntity.h"
#include "yuzinnaComponent.h"
#include "yuzinnaTexture.h"
namespace yuzinna
{

	class SpriteRenderer :public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();
		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;
	
		void SetTexture(graphics::Texture* texture) { mTexture = texture; }
		void SetSize(math::Vector2 size) { mSize = size; }

	private:
		//graphics네임스페이스 안에있는 텍스쳐 클래스 
		graphics::Texture* mTexture;

		math::Vector2 mSize;
		

		
	};
}

