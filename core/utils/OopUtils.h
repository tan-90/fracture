#pragma once

namespace fc
{
	namespace utils
	{
		template<typename O, typename T>
		bool InstanceOf(const O* Object)
		{
			return dynamic_cast<const T*>(Object) != nullptr;
		}
	}
}
