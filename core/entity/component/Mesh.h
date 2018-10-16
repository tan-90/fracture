#pragma once

#include "Component.h"

#include "..\..\Types.h"
#include "..\..\graphics\VertexBuffer.h"
#include "..\..\graphics\IndexBuffer.h"
#include "..\..\graphics\VertexArray.h"
#include "..\..\utils\Color.h"
#include "..\..\graphics\material\PbrMaterial.h"

#include <glm\glm.hpp>

#include <vector>
#include <string>

namespace fc
{
	enum MeshPrimitives
	{
		CUBE,
		ROUNDED_CUBE,
		PLANE,
		SPHERE,
		CILINDER,
		MATERIAL_BALL
	};
	
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
		glm::vec3 Color;
		glm::vec2 Uv;
	};

	struct MeshData
	{
		std::vector<glm::vec3> m_Positions;
		std::vector<glm::vec3> m_Normals;
		std::vector<glm::vec3> m_Tangents;
		std::vector<glm::vec3> m_Bitangents;
		std::vector<glm::vec3> m_Colors;
		std::vector<glm::vec2> m_Uvs;

		std::vector<uint> m_Indices;
	};

	class Mesh : public Component
	{
	public:
		Mesh(graphics::PbrMaterial* Material);
		Mesh(MeshPrimitives Primitive, utils::Color MeshColor, graphics::PbrMaterial* Material);
		Mesh(std::string FilePath, utils::Color MeshColor, graphics::PbrMaterial* Material);

		virtual ~Mesh();

		void Upload();

		inline void SetPositions(std::vector<glm::vec3> Positions) { m_Data->m_Positions = Positions; }
		inline void SetNormals(std::vector<glm::vec3> Normals) { m_Data->m_Normals = Normals; }
		inline void SetColors(std::vector<glm::vec3> Colors) { m_Data->m_Colors = Colors; }
		inline void SetUvs(std::vector<glm::vec2> Uvs) { m_Data->m_Uvs = Uvs; }

		inline graphics::VertexArray* GetVertexArray() { return m_VertexArray; }
		inline const uint& GetVertexCount() const { return m_Data->m_Indices.size(); }
		inline graphics::PbrMaterial* GetMaterial() { return m_Material; }

	protected:
		static MeshData* s_BakedCube;
		static MeshData* s_BakedRoundedCube;
		static MeshData* s_BakedPlane;
		static MeshData* s_BakedSphere;
		static MeshData* s_BakedCilinder;
		static MeshData* s_BakedMaterialBall;

	private:
		void GenerateBuffers();

		MeshData* m_Data;

		graphics::VertexArray* m_VertexArray;
		graphics::VertexBuffer* m_VertexBuffer;
		graphics::IndexBuffer* m_IndexBuffer;

		graphics::PbrMaterial* m_Material;
	};
}
