#include "Component.h"

namespace fc
{
	Component::Component()
		:Component("unnamed")
	{

	}

	Component::Component(std::string Name)
		:m_Name(Name)
	{

	}

	Component::~Component()
	{

	}

	void Component::SetName(std::string Name)
	{
		m_Name = Name;
	}
}