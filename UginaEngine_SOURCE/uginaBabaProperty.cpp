#include "uginaBabaProperty.h"

namespace ugina
{
	BabaProperty::BabaProperty()
		: Component(enums::eComponentType::BabaProperty)
	{
	}

	BabaProperty::~BabaProperty()
	{
	}

	void BabaProperty::Initialize()
	{
	}

	void BabaProperty::Update()
	{
	}

	void BabaProperty::LateUpdate()
	{
	}

	void BabaProperty::Render(HDC hdc)
	{
	}

	void BabaProperty::AddProperty(eBabaProperty prop)
	{
		if (!HasProperty(prop))
		{
			mProperties.push_back(prop);
		}
	}

	void BabaProperty::RemoveProperty(eBabaProperty prop)
	{
		for (auto it = mProperties.begin(); it != mProperties.end(); ++it)
		{
			if (*it == prop)
			{
				mProperties.erase(it);
				break;
			}
		}
	}

	void BabaProperty::ClearProperties()
	{
		mProperties.clear();
	}

	bool BabaProperty::HasProperty(eBabaProperty prop)
	{
		for (auto p : mProperties)
		{
			if (p == prop) return true;
		}
		return false;
	}
}
