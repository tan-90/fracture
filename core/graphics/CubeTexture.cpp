#include "CubeTexture.h"

namespace fc
{
	namespace graphics
	{
		std::string CubeTexture::s_CubeMapImageSufix[] = 
		{
			"_ft", 
			"_bk", 
			"_up", 
			"_dn", 
			"_rt", 
			"_lf",
		};

		CubeTexture::CubeTexture(GLuint Slot, GLenum ColorSpace, GLenum InternalColorSpace, GLenum DataType)
			:Texture(Slot, GL_TEXTURE_CUBE_MAP, ColorSpace, InternalColorSpace, DataType)
		{
			m_ColorSpace = ColorSpace;
			m_InternalColorSpace = InternalColorSpace;
			m_DataType = DataType;
		}

		CubeTexture::CubeTexture(std::string* Paths, GLuint Slot, GLenum ColorSpace, GLenum InternalColorSpace, GLenum DataType)
			:Texture(Slot, GL_TEXTURE_CUBE_MAP, ColorSpace, InternalColorSpace, DataType)
		{
			m_ColorSpace = ColorSpace;
			m_InternalColorSpace = InternalColorSpace;
			m_DataType = DataType;

			m_Paths = Paths;
			m_Data = LoadImages(Paths);
		}

		CubeTexture::CubeTexture(std::string BasePath, std::string Extension, GLuint Slot, GLenum ColorSpace, GLenum InternalColorSpace, GLenum DataType)
			:CubeTexture(GetImagePaths(BasePath, Extension), Slot, ColorSpace, InternalColorSpace, DataType)
		{

		}

		CubeTexture::~CubeTexture()
		{
			delete m_Paths;
			delete[] m_Data;
		}

		void CubeTexture::Upload()
		{
			Bind();

			for (int i = 0; i < 6; i++)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_ColorSpace, m_Width, m_Height, 0, m_InternalColorSpace, m_DataType, (const void*)m_Data != NULL? m_Data[i] : NULL);
			}

			glTexParameteri(GetTextureType(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GetTextureType(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GetTextureType(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GetTextureType(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GetTextureType(), GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 

			Unbind();
		}

		std::string* CubeTexture::GetImagePaths(std::string BasePath, std::string Extension)
		{
			std::string* ImagePaths = new std::string[6];

			for (int i = 0; i < 6; i++)
			{
				ImagePaths[i] = BasePath + CubeTexture::s_CubeMapImageSufix[i] + Extension;
			}

			return ImagePaths;
		}
		byte** CubeTexture::LoadImages(std::string* Paths)
		{
			byte** Images = new byte*[6];

			for (int i = 0; i < 6; i++)
			{
				utils::Image* CurrentFace = utils::FileUtils::ReadImageFile(Paths[i]);

				if (i == 0)
				{
					m_Width = CurrentFace->Width;
					m_Height = CurrentFace->Height;
				}

				Images[i] = CurrentFace->Data;
			}

			return Images;
		}
	}
}