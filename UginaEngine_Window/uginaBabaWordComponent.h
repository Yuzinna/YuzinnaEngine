#pragma once
#include "uginaScript.h"

namespace ugina
{
	// 단어의 종류를 분류합니다.
	enum class eWordType
	{
		// 명사 (Nouns)
		BABA,
		ROCK,
		WALL,
		FLAG,

		// 동사 (Verbs)
		IS,

		// 속성 (Properties)
		YOU,
		PUSH,
		STOP,
		WIN,
		SINK,

		END
	};

	// 이 단어가 어떤 카테고리에 속하는지 분류합니다.
	enum class eWordCategory
	{
		NOUN,
		VERB,
		PROPERTY,
		END
	};

	class BabaWordComponent : public Script
	{
	public:
		BabaWordComponent();
		~BabaWordComponent();

		void Initialize() override;

		void SetWordType(eWordType type) { mWordType = type; }
		eWordType GetWordType() { return mWordType; }

		eWordCategory GetCategory();

	private:
		eWordType mWordType;
	};
}
