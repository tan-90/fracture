#include "GLUtils.h"

namespace fc
{
	namespace utils
	{
		GLUtils* GLUtils::s_Instance = new GLUtils();
		std::map<GLenum, uint> GLUtils::s_FormatChannelCount = GLUtils::InitFormatChannelCount();
		std::map<GLenum, uint> GLUtils::s_TypeSize = GLUtils::InitTypeSize();

		GLUtils::GLUtils()
		{

		}

		GLUtils::~GLUtils()
		{

		}

		std::map<GLenum, uint> GLUtils::InitFormatChannelCount()
		{
			std::map<GLenum, uint> FormatChannelCount;

			FormatChannelCount.insert(std::make_pair(GL_RED          , 1));
			FormatChannelCount.insert(std::make_pair(GL_GREEN        , 1));
			FormatChannelCount.insert(std::make_pair(GL_BLUE         , 1));
			FormatChannelCount.insert(std::make_pair(GL_RG           , 2));
			FormatChannelCount.insert(std::make_pair(GL_RGB          , 3));
			FormatChannelCount.insert(std::make_pair(GL_RGBA         , 4));
			FormatChannelCount.insert(std::make_pair(GL_BGR          , 3));
			FormatChannelCount.insert(std::make_pair(GL_BGRA         , 4));
			FormatChannelCount.insert(std::make_pair(GL_RED_INTEGER  , 1));
			FormatChannelCount.insert(std::make_pair(GL_GREEN_INTEGER, 1));
			FormatChannelCount.insert(std::make_pair(GL_BLUE_INTEGER , 1));
			FormatChannelCount.insert(std::make_pair(GL_RG_INTEGER   , 2));
			FormatChannelCount.insert(std::make_pair(GL_RGB_INTEGER  , 3));
			FormatChannelCount.insert(std::make_pair(GL_RGBA_INTEGER , 4));
			FormatChannelCount.insert(std::make_pair(GL_BGR_INTEGER  , 3));
			FormatChannelCount.insert(std::make_pair(GL_BGRA_INTEGER , 4));

			return FormatChannelCount;
		}

		std::map<GLenum, uint> GLUtils::InitTypeSize()
		{
			std::map<GLenum, uint> TypeSize;

			TypeSize.insert(std::make_pair(GL_UNSIGNED_BYTE, 1));
			TypeSize.insert(std::make_pair(GL_BYTE, 1));
			TypeSize.insert(std::make_pair(GL_UNSIGNED_SHORT, 2));
			TypeSize.insert(std::make_pair(GL_SHORT, 2));
			TypeSize.insert(std::make_pair(GL_UNSIGNED_INT, 4));
			TypeSize.insert(std::make_pair(GL_INT, 4));
			TypeSize.insert(std::make_pair(GL_HALF_FLOAT, 2));
			TypeSize.insert(std::make_pair(GL_FLOAT, 4));

			return TypeSize;
		}
	}
}