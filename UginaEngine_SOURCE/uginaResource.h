#pragma once
#include "uginaEntity.h"
namespace ugina
{
	class Resource abstract : public Entity
	{
	public :
		Resource(enums::eResourceType type);
		virtual ~Resource();

		//HRESULT는 bool과 같음
		//순수가상함수 실제메모리 할당이 불가능해지는 문법이다.(상속해서 사용)
		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }
	private:
		//현재 리소스의 타입을 가짐 오디오,텍스쳐와 같은
		const enums::eResourceType mType;
		//리소스 파일의 경로를 담음
		std::wstring mPath;
	};
}
