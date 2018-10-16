#include "MathUtils.h"

namespace fc
{
	namespace utils
	{
		float MathUtils::ToRadians(float Degrees)
		{
			return Degrees * (3.141592653f / 180.0f);
		}

		float MathUtils::ToDegree(float Radians)
		{
			return Radians * (180.0f / 3.141592653f);
		}
	}
}