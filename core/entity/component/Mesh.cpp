#include "Mesh.h"

#include "..\..\utils\files\FileUtils.h"
#include "..\..\utils\files\AssimpUtils.h"

namespace fc
{
	MeshData* Mesh::s_BakedCube;
	MeshData* Mesh::s_BakedRoundedCube;
	MeshData* Mesh::s_BakedPlane;
	MeshData* Mesh::s_BakedSphere;
	MeshData* Mesh::s_BakedCilinder;
	MeshData* Mesh::s_BakedMaterialBall;

	Mesh::Mesh(graphics::PbrMaterial* Material)
		:m_Material(Material)
	{
		m_Data = new MeshData();
		m_VertexArray = new graphics::VertexArray();
		m_VertexArray->Bind();
		m_VertexBuffer = m_VertexArray->CreateManagedBuffer();
		m_IndexBuffer = m_VertexArray->CreateIndexBuffer();
		m_VertexArray->Unbind();
	}
	
	Mesh::Mesh(MeshPrimitives Primitive, utils::Color MeshColor, graphics::PbrMaterial* Material)
		:Mesh(Material)
	{
		switch (Primitive)
		{
		case CUBE:
			if (s_BakedCube == nullptr)
			{
				m_Data = utils::AssimpUtils::LoadObjFile("res/model/Cube.obj", MeshColor, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace).at(0);
				s_BakedCube = m_Data;
			}
			else
			{
				m_Data = s_BakedCube;
			}
			break;
		case ROUNDED_CUBE:
			if (s_BakedRoundedCube == nullptr)
			{
				m_Data = utils::AssimpUtils::LoadObjFile("res/model/RoundedCube.obj", MeshColor, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace).at(0);
				s_BakedRoundedCube = m_Data;
			}
			else
			{
				m_Data = s_BakedRoundedCube;
			}
			break;
		case PLANE:
			if (s_BakedPlane == nullptr)
			{
				m_Data = utils::AssimpUtils::LoadObjFile("res/model/Plane.obj", MeshColor, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace).at(0);
				s_BakedPlane = m_Data;
			}
			else
			{
				m_Data = s_BakedPlane;
			}
			break;
		case SPHERE:
			if (s_BakedSphere == nullptr)
			{
				m_Data = utils::AssimpUtils::LoadObjFile("res/model/Sphere.obj", MeshColor, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace).at(0);
				s_BakedSphere = m_Data;
			}
			else
			{
				m_Data = s_BakedSphere;
			}
			break;
		case CILINDER:
			if (s_BakedCilinder == nullptr)
			{
				m_Data = utils::AssimpUtils::LoadObjFile("res/model/Cilinder.obj", MeshColor, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace).at(0);
				s_BakedCilinder = m_Data;
			}
			else
			{
				m_Data = s_BakedCilinder;
			}

			break;
		case MATERIAL_BALL:
			if (s_BakedMaterialBall == nullptr)
			{
				m_Data = utils::AssimpUtils::LoadObjFile("res/model/MaterialBall.obj", MeshColor, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace).at(0);
				s_BakedMaterialBall = m_Data;
			}
			else
			{
				m_Data = s_BakedMaterialBall;
			}
			break;
		}
	}

	Mesh::Mesh(std::string FilePath, utils::Color MeshColor, graphics::PbrMaterial* Material)
		:Mesh(Material)
	{
		m_Data = utils::AssimpUtils::LoadObjFile(FilePath, MeshColor, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace).at(0);
	}

	Mesh::~Mesh()
	{
		if(m_Data != nullptr)
		{
			delete m_Data;
		}
	}

	void Mesh::Upload()
	{
		GenerateBuffers();
	}

	void Mesh::GenerateBuffers()
	{
		m_VertexArray->Bind();
		m_VertexBuffer->Bind();

		std::vector<Vertex> Vertices;
		for (uint i = 0; i < m_Data->m_Positions.size(); i++)
		{
			Vertex CurrentVertex;
			CurrentVertex.Position = m_Data->m_Positions[i];
			CurrentVertex.Normal = m_Data->m_Normals[i];
			CurrentVertex.Tangent = m_Data->m_Tangents[i];
			CurrentVertex.Bitangent = m_Data->m_Bitangents[i];
			CurrentVertex.Color = m_Data->m_Colors[i];
			CurrentVertex.Uv = m_Data->m_Uvs[i];

			Vertices.push_back(CurrentVertex);
		}

		m_VertexBuffer->SetBufferData((byte*)&Vertices[0], Vertices.size() * sizeof(Vertex));

		uint Pointer = 0;
		fc::graphics::Attribute Position;
		Position.Stride = sizeof(Vertex);
		Position.Pointer = (void*)Pointer;
		Position.Type = GL_FLOAT;
		Position.Size = 3;
		Pointer += Position.Size * sizeof(GLfloat);

		fc::graphics::Attribute Normal;
		Normal.Stride = sizeof(Vertex);
		Normal.Pointer = (void*)Pointer;
		Normal.Type = GL_FLOAT;
		Normal.Size = 3;
		Pointer += Normal.Size * sizeof(GLfloat);

		fc::graphics::Attribute Tangent;
		Tangent.Stride = sizeof(Vertex);
		Tangent.Pointer = (void*)Pointer;
		Tangent.Type = GL_FLOAT;
		Tangent.Size = 3;
		Pointer += Tangent.Size * sizeof(GLfloat);

		fc::graphics::Attribute Bitangent;
		Bitangent.Stride = sizeof(Vertex);
		Bitangent.Pointer = (void*)Pointer;
		Bitangent.Type = GL_FLOAT;
		Bitangent.Size = 3;
		Pointer += Bitangent.Size * sizeof(GLfloat);

		fc::graphics::Attribute Color;
		Color.Stride = sizeof(Vertex);
		Color.Pointer = (void*)Pointer;
		Color.Type = GL_FLOAT;
		Color.Size = 3;
		Pointer += Color.Size * sizeof(GLfloat);

		fc::graphics::Attribute Uv;
		Uv.Stride = sizeof(Vertex);
		Uv.Pointer = (void*)Pointer;
		Uv.Type = GL_FLOAT;
		Uv.Size = 2;

		m_VertexBuffer->PushAttribute(Position);
		m_VertexBuffer->PushAttribute(Normal);
		m_VertexBuffer->PushAttribute(Tangent);
		m_VertexBuffer->PushAttribute(Bitangent);
		m_VertexBuffer->PushAttribute(Color);
		m_VertexBuffer->PushAttribute(Uv);

		m_IndexBuffer->SetBufferData((byte*)&m_Data->m_Indices[0], m_Data->m_Indices.size() * sizeof(uint));

		m_VertexBuffer->Upload();
		m_IndexBuffer->Upload();

		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();
	}
}