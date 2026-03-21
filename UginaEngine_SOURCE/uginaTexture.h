#pragma once
#include "uginaResource.h"

namespace ugina
{
	namespace graphics
	{	
		class Texture : public Resource
		{
		public:
			enum class eTextureType
			{
				Bmp,
				Png,
				None
			};
			static Texture* Create(const std::wstring& name, UINT width, UINT height);
			Texture();
			~Texture();

			virtual HRESULT Load(const std::wstring& path) override;


			void SetWidth(UINT width) { mWidth = width; }
			void SetHeight(UINT height) { mHeight = height; }
			UINT GetWidth() { return mWidth; }
			UINT GetHeight() { return mHeight; }
			HDC GetHdc() { return mHdc; }
			eTextureType GetTextureType() { return mType; }
			Gdiplus::Image* GetImage() { return mImage; }
			bool IsAlpha() { return mbAlpha; }
		private:
			bool mbAlpha;
			eTextureType mType;
			Gdiplus::Image* mImage;
			HBITMAP mBitmap;
			HDC mHdc;

			UINT mWidth;
			UINT mHeight;
		};
	}
}

