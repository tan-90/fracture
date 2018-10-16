#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <string>
#include <map>

#include "..\utils\files\FileUtils.h"

namespace fc
{
	namespace graphics
	{
		class Shader
		{
		public:
			Shader(std::string VertexPath, std::string FragmentPath);
			~Shader();

			void Enable();
			void Disable();

			// TODO Replace uniform binding with constant buffers
			void BindUniform(std::string Location);
			void UploadUniformFloat(std::string Location, GLfloat Value);
			void UploadUniformFloatVec3(std::string Location, glm::vec3 Value);
			void UploadUniformFloatMat4(std::string Location, glm::mat4 Value);
			void UploadUniformInt(std::string Location, GLint Value);

			static void SetBoundShader(Shader* BoundShader);

		private:
			GLuint ProgramFromShaders(GLuint Vertex, GLuint Fragment);
			GLuint ShaderFromFile(GLenum Type, std::string Path);

			GLuint m_Handle;

			std::map<std::string, GLuint> m_Uniforms;

			static Shader* m_BoundShader;
		};
	}
}