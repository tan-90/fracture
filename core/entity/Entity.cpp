#include "Entity.h"

namespace fc
{
	void Entity::AttachComponent(Component* Component)
	{
		m_Components.push_back(Component);
	}
}