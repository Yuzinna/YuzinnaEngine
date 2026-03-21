#pragma once
#include "uginaResource.h"
namespace ugina
{
	class Resources
	{
	public:
		template<typename T>
		static T* Find(const std::wstring& key)
		{
			//auto = std::map<std::wstring, Resource*>::iterator
			auto iter = mResources.find(key);
			if (iter == mResources.end())
			{
				return nullptr;
			}

			return dynamic_cast<T*>(iter->second);

		}

		template<typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			//리소스를 로드하기전에 일단 같은 이름의 리소스가 있는지 찾아봄
			T* resource = Resources::Find<T>(key);
			//존재한다면 로드할필요가 없으니 바로 그 리소스를 리턴
			if (resource != nullptr)
			{
				return resource;
			}
			//없다면 새로운 리소스를 생성
			resource = new T();
			// 각 리소스 객체가 가지고 있는 로드함수를 실행시켜서 리소스를 로드시킴
			if (FAILED(resource->Load(path)))
			{
				assert(false);
			}
			//로드된 리소소는 mResources 맵에 저장
			resource->SetName(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));
			

			return resource;
		}

		static void Insert(const std::wstring& key, Resource* resource)
		{
			if (key == L"")
			{
				return;
			}
			if (resource == nullptr)
			{
				return;
			}
			mResources.insert(std::make_pair(key, resource));
		}
		static void Release()
		{
			//auto = std::pair<const std::wstring,Resource*> map의 첫번째 값은 내부적으로 const로 들어감
			for (auto& iter : mResources)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}
	private:

		//엔진 내부에서 사용할 이름이 키(ex BG,Player), value는 안에 들어간 리소스객체의 포인터
		static std::map<std::wstring, Resource*> mResources;
	};
}

