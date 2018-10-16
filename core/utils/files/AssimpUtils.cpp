#include "AssimpUtils.h"

#include "..\..\entity\component\Mesh.h"

namespace fc
{
	namespace utils
	{
		std::vector<MeshData*> AssimpUtils::LoadObjFile(std::string Path, Color Color)
		{
			return LoadObjFile(Path, Color, NULL);
		}
		std::vector<MeshData*> AssimpUtils::LoadObjFile(std::string Path, Color Color, uint Flags)
		{
			std::vector<MeshData*> Meshes;

			Assimp::Importer Importer;
			Importer.SetPropertyBool(AI_CONFIG_IMPORT_ASE_RECONSTRUCT_NORMALS, false);
			const aiScene* Scene = Importer.ReadFile(Path, Flags);

			GetNodeMeshes(Scene->mRootNode, Scene, Meshes, Color);

			return Meshes;
		}
		void AssimpUtils::GetNodeMeshes(aiNode* Node, const aiScene* Scene, std::vector<MeshData*>& MeshSet, Color Color)
		{
			for (uint i = 0; i < Node->mNumMeshes; i++)
			{
				MeshData* Mesh;
				Mesh = MeshDataFromAiMesh(Scene->mMeshes[Node->mMeshes[i]], Color);
				MeshSet.push_back(Mesh);
			}

			for (uint i = 0; i < Node->mNumChildren; i++)
			{
				GetNodeMeshes(Node->mChildren[i], Scene, MeshSet, Color);
			}
		}
		MeshData* AssimpUtils::MeshDataFromAiMesh(aiMesh* AiMesh, Color Color)
		{
			MeshData* Mesh = new MeshData();

			for (uint i = 0; i < AiMesh->mNumVertices; i++)
			{
				glm::vec3 Position;
				glm::vec3 Normal;
				glm::vec3 Tangent;
				glm::vec3 Bitangent;
				glm::vec2 Uv;

				Position.x = AiMesh->mVertices[i].x;
				Position.y = AiMesh->mVertices[i].y;
				Position.z = AiMesh->mVertices[i].z;
				Mesh->m_Positions.push_back(Position);

				Normal.x = AiMesh->mNormals[i].x;
				Normal.y = AiMesh->mNormals[i].y;
				Normal.z = AiMesh->mNormals[i].z;
				Mesh->m_Normals.push_back(Normal);

				Tangent.x = AiMesh->mTangents[i].x;
				Tangent.y = AiMesh->mTangents[i].y;
				Tangent.z = AiMesh->mTangents[i].z;
				Mesh->m_Tangents.push_back(Tangent);

				Bitangent.x = AiMesh->mBitangents[i].x;
				Bitangent.y = AiMesh->mBitangents[i].y;
				Bitangent.z = AiMesh->mBitangents[i].z;
				Mesh->m_Bitangents.push_back(Bitangent);

				Mesh->m_Colors.push_back(glm::vec3(Color.Red, Color.Green, Color.Blue));

				// TODO support multiple textures
				Uv.x = AiMesh->mTextureCoords[0][i].x;
				Uv.y = AiMesh->mTextureCoords[0][i].y;
				Mesh->m_Uvs.push_back(Uv);
			}

			for (uint i = 0; i < AiMesh->mNumFaces; i++)
			{
				aiFace Face = AiMesh->mFaces[i];
				for (uint j = 0; j < Face.mNumIndices; j++)
				{
					Mesh->m_Indices.push_back(Face.mIndices[j]);
				}
			}

			return Mesh;
		}
	}
}