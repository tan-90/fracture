#pragma once

#include "component\Component.h"

#include "..\utils\OopUtils.h"

#include <vector>

namespace fc
{
	class Entity
	{
	public:
		void AttachComponent(Component* Component);
		template<typename T>
		T* GetComponentOfType()
		{
			for (Component* CurrentComponent : m_Components)
			{
				if (utils::InstanceOf<Component, T>(CurrentComponent))
				{
					return (T*)CurrentComponent;
				}
			}

			return nullptr;
		}

	private:
		std::vector<Component*> m_Components;
	};
}
