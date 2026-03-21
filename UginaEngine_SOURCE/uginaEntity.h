#pragma once
#include "CommonInclude.h"
using namespace ugina::math;

namespace ugina
{
	//이 엔진에서 디버깅 하는 요소들에 이름을 부여하여 디버깅 하기에 용이 하게 함
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName;}

	private:
		std::wstring mName;
	};
}


