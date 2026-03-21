#include "yuzinnaBabaWordComponent.h"

namespace yuzinna
{
	BabaWordComponent::BabaWordComponent()
		: mWordType(eWordType::BABA)
	{
	}

	BabaWordComponent::~BabaWordComponent()
	{
	}

	void BabaWordComponent::Initialize()
	{
	}

	eWordCategory BabaWordComponent::GetCategory()
	{
		// ?⑥뼱 ??낆뿉 ?곕씪 移댄뀒怨좊━瑜?遺꾨쪟?⑸땲??
		switch (mWordType)
		{
		case eWordType::BABA:
		case eWordType::ROCK:
		case eWordType::WALL:
		case eWordType::FLAG:
			return eWordCategory::NOUN;

		case eWordType::IS:
			return eWordCategory::VERB;

		case eWordType::YOU:
		case eWordType::PUSH:
		case eWordType::STOP:
		case eWordType::WIN:
		case eWordType::SINK:
			return eWordCategory::PROPERTY;

		default:
			return eWordCategory::END;
		}
	}
}
