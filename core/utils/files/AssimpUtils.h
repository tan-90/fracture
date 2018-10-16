#pragma once

#include <string>
#include <vector>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "..\..\Types.h"
#include "..\Color.h"

namespace fc
{
	struct MeshData;

	namespace utils
	{
		class AssimpUtils
		{
		public:
			static std::vector<MeshData*> LoadObjFile(std::string Path, Color Color);
			static std::vector<MeshData*> LoadObjFile(std::string Path, Color Color, uint Flags);

		private:
			static void GetNodeMeshes(aiNode* Node, const aiScene* Scene, std::vector<MeshData*>& MeshSet, Color Color);
			static MeshData* MeshDataFromAiMesh(aiMesh* AiMesh, Color Color);
		};
	}
}
