#include "uginaTexture.h"
#include "uginaApplication.h"
#include "uginaResources.h"
extern ugina::Application api;
namespace ugina
{
	
	namespace graphics
	{
		//이프로젝트에서 사용할 텍스쳐 라는 리소스를 생성하는 리소스의 오버라이드 함수
		Texture* Texture::Create(const std::wstring& name, UINT width, UINT height)
		{
			Texture* image = Resources::Find<Texture>(name);

			if (image)
			{
				return image;
			}
			image = new Texture();
			image->SetName(name);
			image->SetWidth(width);
			image->SetHeight(height);

			#pragma region 이미지파일을 생성하기위한 필수작업
			HDC hdc = api.GetHdc();
			HWND hwnd = api.GetHwnd();
			//현재 dc에 호환되는 비트맵과 
			//그dc는 이 윈도우에서 사용하는 윈도우 dc와도 호환가능해야함
			image->mBitmap = CreateCompatibleBitmap(hdc, width, height);
			image->mHdc = CreateCompatibleDC(hdc);

			///박스콜라이더를 그리기위한 브러쉬 설정(콜라이더 사각형 내부를 채우는 브러쉬는 투명 브러쉬)
			HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);
			Rectangle(image->mHdc, -1, -1, image->GetWidth() + 1, image->GetHeight() + 1);
			SelectObject(hdc, oldBrush);
			///
			HBITMAP oldbitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
			DeleteObject(oldbitmap);
			#pragma endregion

			Resources::Insert(name + L"Image", image);

			return image;
		}
		Texture::Texture()
			:Resource(ugina::enums::eResourceType::Texture)
			,mbAlpha(false)
		{


		}

		Texture::~Texture()
		{
		}

		//텍스쳐를 일단 게임의 메모리에 올리는 함수(현재는 Resources 클래스의 Load함수가 실행시켜줌)
		HRESULT Texture::Load(const std::wstring& path)
		{
			//aaaa.png파일이면 .이후부터 끝까지의 문자열을 반환 (즉 png(확장자)를 반환)
			std::wstring ext = path.substr(path.find_last_of(L'.') + 1);
			
			if (ext == L"bmp")
			{
				mType = eTextureType::Bmp;
				//BMP파일 이미지를 로드해서 HBITMAP을 통해서 참조
				mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				
				//null을 반환하는 실패
				if (mBitmap == nullptr)
				{
					return S_FALSE;
				}
				//비트맵 구조체를 통해서 HBITMAP의 내용을 저장
				BITMAP info = {};
			
				GetObject(mBitmap, sizeof(BITMAP), &info);
				
				mWidth = info.bmWidth;
				mHeight = info.bmHeight;

				//현재 이미지가 32비트 비트맵(알파값이 있는 비트맵인가)
				if (info.bmBitsPixel == 32)
				{
					mbAlpha = true;
				}
				//현재 이미지가 24비트 비트맵(알파값이 없는 비트맵인가)
				else if (info.bmBitsPixel == 24)
				{
					mbAlpha = false;
				}

				//현재 게임에 사용되고 있는 메인dc를 가져온다
				HDC maicDc = api.GetHdc();
				//비트맵을 그릴 DC(mhdc)를 메인DC에 호환되는 DC로 맞춘다.
				mHdc = CreateCompatibleDC(maicDc);
				
				//이 비트맵을 그릴 dc의 비트맵을 이미지를 가져온 비트맵으로 바꾼다.
				HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
				DeleteObject(oldBitmap);
				
					
			}
			else if (ext == L"png")
			{
				mType = eTextureType::Png;
				mImage = Gdiplus::Image::FromFile(path.c_str());
				if (mImage == nullptr)
				{
					return S_FALSE;
				}
				mWidth=mImage->GetWidth();
				mHeight=mImage->GetHeight();
			}

			return S_OK;
		}
	}
}
