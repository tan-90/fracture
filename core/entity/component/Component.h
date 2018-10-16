#pragma once

#include <string>

namespace fc
{
	class Component
	{
	public:
		Component();
		Component(std::string Name);

		virtual ~Component();

		void SetName(std::string Name);
		inline std::string GetName() { return m_Name; }

	private:
		std::string m_Name;
	};
}