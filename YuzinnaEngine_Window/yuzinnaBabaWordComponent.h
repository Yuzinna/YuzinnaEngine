#pragma once
#include "yuzinnaScript.h"

namespace yuzinna
{
	// ?⑥뼱??醫낅쪟瑜?遺꾨쪟?⑸땲??
	enum class eWordType
	{
		// 紐낆궗 (Nouns)
		BABA,
		ROCK,
		WALL,
		FLAG,

		// ?숈궗 (Verbs)
		IS,

		// ?띿꽦 (Properties)
		YOU,
		PUSH,
		STOP,
		WIN,
		SINK,

		END
	};

	// ???⑥뼱媛 ?대뼡 移댄뀒怨좊━???랁븯?붿? 遺꾨쪟?⑸땲??
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
