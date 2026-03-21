#include "yuzinnaComponent.h"

namespace yuzinna
{
	Component::Component(enums::eComponentType type) : mType(type)
	{
	}
	yuzinna::Component::~Component()
	{
	}
	void Component::Initialize()
	{
	}
	void Component::Update()
	{
	}
	void Component::LateUpdate()
	{
	}
	void Component::Render(HDC hdc)
	{
	}
}
