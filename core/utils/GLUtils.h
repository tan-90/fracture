#pragma once

#include "..\Types.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <map>

namespace fc
{
	namespace utils
	{
		class GLUtils
		{
		public:
			GLUtils();
			~GLUtils();

			static std::map<GLenum, uint> InitFormatChannelCount();
			static std::map<GLenum, uint> InitTypeSize();
			
			static std::map<GLenum, uint> s_FormatChannelCount;
			static std::map<GLenum, uint> s_TypeSize;

		private:
			static GLUtils* s_Instance;

		};
	}
}
