#include "FileUtils.h"

#include "..\..\entity\component\Mesh.h"

namespace fc
{
	namespace utils
	{
		std::string FileUtils::ReadTextFile(std::string Path)
		{
			std::ifstream File;
			std::stringstream FileStream;

			File.open(Path);
			FileStream << File.rdbuf();
			File.close();

			return FileStream.str();
		}

		Image* FileUtils::ReadImageFile(std::string Path)
		{
			const char* ImagePath = Path.c_str();
			FREE_IMAGE_FORMAT Format = FIF_UNKNOWN;
			Format = FreeImage_GetFileType(ImagePath, 0);

			if (Format == FIF_UNKNOWN)
			{
				Format = FreeImage_GetFIFFromFilename(ImagePath);
			}

			if (Format == FIF_UNKNOWN)
			{
				return nullptr;
			}

			FIBITMAP* BitMap = nullptr;
			if (FreeImage_FIFSupportsReading(Format))
			{
				BitMap = FreeImage_Load(Format, ImagePath);
			}

			FIBITMAP* BitMap32 = nullptr;
			BitMap32 = FreeImage_ConvertTo32Bits(BitMap);
			FreeImage_FlipVertical(BitMap32);
			FreeImage_Unload(BitMap);

			if (!BitMap32)
			{
				std::cout << Path << ": Error converting to 32 bits." << std::endl;
			}

			Image* ImageData = new Image();
			ImageData->Data = FreeImage_GetBits(BitMap32);
			ImageData->Width = FreeImage_GetWidth(BitMap32);
			ImageData->Height = FreeImage_GetHeight(BitMap32);
			ImageData->BitsPerPixel = FreeImage_GetBPP(BitMap32);

			return ImageData;
		}

		Image* FileUtils::ReadHdrImageFile(std::string Path)
		{
			Image* ImageData = new Image();

			int Width;
			int Height;
			int Channels;

			ImageData->Data = (byte*)stbi_loadf(Path.c_str(), &Width, &Height, &Channels, NULL);
			ImageData->Width = (int)Width;
			ImageData->Height = (int)Height;
			ImageData->BitsPerPixel = Channels * sizeof(float) * 8;

			return ImageData;
		}

		MeshData* FileUtils::ReadObjFile(std::string Path, Color MeshColor)
		{
			MeshData* Data = new MeshData();

			FILE* File;
			char* Line = new char[128];
			File = fopen(Path.c_str(), "r");

			std::vector<glm::vec3> Positions;
			std::vector<glm::vec3> Normals;
			std::vector<glm::vec2> Uvs;

			std::map<VertexIndices, uint> Indices;
			uint CurrentIndex;
			CurrentIndex = 0;

			while (fscanf(File, "%s", Line) != EOF)
			{
				if (strcmp(Line, "v") == 0)
				{
					// Position
					glm::vec3 CurrentPosition;
					fscanf(File, "%f %f %f", &CurrentPosition.x, &CurrentPosition.y, &CurrentPosition.z);
					Positions.push_back(CurrentPosition);
				}
				else if (strcmp(Line, "vt") == 0)
				{
					// Texture
					glm::vec2 CurrentUv;
					fscanf(File, "%f %f", &CurrentUv.x, &CurrentUv.y);
					Uvs.push_back(CurrentUv);
				}
				else if (strcmp(Line, "vn") == 0)
				{
					// Normal
					glm::vec3 CurrentNormal;
					fscanf(File, "%f %f %f", &CurrentNormal.x, &CurrentNormal.y, &CurrentNormal.z);
					Normals.push_back(CurrentNormal);
				}
				else if (strcmp(Line, "f") == 0)
				{
					// Face
					VertexIndices TriangleVertices[3];

					fscanf(
						File,
						"%u/%u/%u %u/%u/%u %u/%u/%u",
						&TriangleVertices[0].Position, &TriangleVertices[0].Uv, &TriangleVertices[0].Normal,
						&TriangleVertices[1].Position, &TriangleVertices[1].Uv, &TriangleVertices[1].Normal,
						&TriangleVertices[2].Position, &TriangleVertices[2].Uv, &TriangleVertices[2].Normal
						);

					for (int i = 0; i < 3; i++)
					{
						if (Indices.find(TriangleVertices[i]) == Indices.end())
						{
							Indices.insert(std::make_pair(TriangleVertices[i], CurrentIndex++));
							Data->m_Positions.push_back(Positions[TriangleVertices[i].Position - 1]);
							Data->m_Normals.push_back(Normals[TriangleVertices[i].Normal - 1]);
							Data->m_Colors.push_back({ MeshColor.Red, MeshColor.Green, MeshColor.Blue });
							Data->m_Uvs.push_back(Uvs[TriangleVertices[i].Uv - 1]);
						}
						Data->m_Indices.push_back(Indices[TriangleVertices[i]]);
					}
				}
			}
			
			fclose(File);
			delete Line;
			return Data;
		}
		bool FileUtils::Exists(std::string Path)
		{
			if (FILE* File = fopen(Path.c_str(), "r"))
			{
				fclose(File);
				return true;
			}
			return false;
		}
		bool FileUtils::Screenshot(std::string FileName, int Width, int Height)
		{
			long BufferSize = Width * Height * 3;
			byte* Buffer = new byte[BufferSize];

			glReadPixels(0, 0, Width, Height, GL_BGR, GL_UNSIGNED_BYTE, Buffer);

			FIBITMAP *FreeImageDib = FreeImage_ConvertFromRawBits(Buffer, Width, Height, 3 * Width, 24, 0x0000FF, 0x00FF00, 0xFF0000);
			FreeImage_Save(FIF_TIFF, FreeImageDib, FileName.c_str());

			delete[] Buffer;

			return true;
		}
	}
}