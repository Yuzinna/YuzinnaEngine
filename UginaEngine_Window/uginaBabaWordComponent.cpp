#include "uginaBabaWordComponent.h"

namespace ugina
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
		// 단어 타입에 따라 카테고리를 분류합니다.
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
