#include "Light.h"

namespace fc
{
	namespace graphics
	{
		ILight::ILight(LightType Type)
			:m_Type(Type)
		{

		}

		ILight::~ILight()
		{

		}

		void ILight::Update()
		{
			// NOOP can be overriden if needed by the light
		}
	}
}