#pragma once

#include <GL\glew.h>

namespace fc
{
	namespace utils
	{
		struct Color
		{
			GLfloat Red;
			GLfloat Green;
			GLfloat Blue;

			GLfloat Alpha;

			Color(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha)
			{
				this->Red = Red;
				this->Green = Green;
				this->Blue = Blue;
				this->Alpha = Alpha;
			}
		};
	}
}