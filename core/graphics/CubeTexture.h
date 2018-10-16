#pragma once

#include "Texture.h"
#include "ImageTexture.h"

#include <string>

#include "..\utils\files\FileUtils.h"

namespace fc
{
	namespace graphics
	{
		class CubeTexture : public Texture
		{
		public:
			CubeTexture(GLuint Slot, GLenum ColorSpace, GLenum InternalColorSpace, GLenum DataType);
			CubeTexture(std::string* Paths, GLuint Slot, GLenum ColorSpace, GLenum InternalColorSpace, GLenum DataType);
			CubeTexture(std::string BasePath, std::string Extension, GLuint Slot, GLenum ColorSpace = GL_RGBA, GLenum InternalColorSpace = GL_RGBA, GLenum DataType = GL_UNSIGNED_BYTE);
			~CubeTexture();

			void Upload() override;			

			static std::string s_CubeMapImageSufix[];

			inline void SetWidth(uint Width) { m_Width = Width; }
			inline void SetHeight(uint Height) { m_Height = Height; }


		private:
			std::string* GetImagePaths(std::string BasePath, std::string Extension);
			byte** LoadImages(std::string* Paths);

			uint m_Width;
			uint m_Height;

			std::string* m_Paths;
			byte** m_Data;
		};
	}
}