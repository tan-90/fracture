#pragma once

#include "..\..\Types.h"
#include "..\Color.h"

#include <FreeImage.h>
#include <glm/glm.hpp>

#include <stb_image.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <cstdio>

namespace fc
{
	struct MeshData;
	
	namespace utils
	{
		struct VertexIndices
		{
			uint Position;
			uint Normal;
			uint Uv;

			bool operator<(const VertexIndices& rhs) const
			{
				return Position < rhs.Position;
			}
			bool operator==(const VertexIndices& rhs) const
			{
				return Position == rhs.Position && Normal == rhs.Normal && Uv == rhs.Uv;
			}
		};

		struct Image
		{
			byte* Data;
			uint Width;
			uint Height;
			uint BitsPerPixel;
		};		

		class FileUtils
		{
		public:
			static std::string ReadTextFile(std::string Path);
			static Image* ReadImageFile(std::string Path);
			static Image* ReadHdrImageFile(std::string Path);
			static MeshData* ReadObjFile(std::string Path, Color MeshColor);
			static bool Exists(std::string Path);

			static bool Screenshot(std::string FileName, int Width, int Height);
		};
	}
}