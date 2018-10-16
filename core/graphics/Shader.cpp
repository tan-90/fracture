#include "Shader.h"

namespace fc
{
	namespace graphics
	{
		Shader* Shader::m_BoundShader;
		Shader::Shader(std::string VertexPath, std::string FragmentPath)
		{
			GLuint VertexShader = ShaderFromFile(GL_VERTEX_SHADER, VertexPath);
			GLuint FragmentShader = ShaderFromFile(GL_FRAGMENT_SHADER, FragmentPath);

			m_Handle = ProgramFromShaders(VertexShader, FragmentShader);
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_Handle);
		}

		void Shader::Enable()
		{
			if (!m_BoundShader || m_BoundShader != this)
			{
				Shader::SetBoundShader(this);
				glUseProgram(m_Handle);
			}
		}

		void Shader::Disable()
		{
			if (m_BoundShader)
			{
				Shader::SetBoundShader(nullptr);
				glUseProgram(NULL);
			}
		}

		void Shader::BindUniform(std::string Location)
		{
			GLuint LocationPointer;
			LocationPointer = glGetUniformLocation(m_Handle, (GLchar*)Location.c_str());
			m_Uniforms.insert(std::make_pair(Location, LocationPointer));
		}

		void Shader::UploadUniformFloat(std::string Location, GLfloat Value)
		{
			Enable();
			GLuint LocationPointer = m_Uniforms[Location];
			glUniform1f(LocationPointer, Value);
		}

		void Shader::UploadUniformFloatVec3(std::string Location, glm::vec3 Value)
		{
			Enable();
			GLuint LocationPointer = m_Uniforms[Location];
			glUniform3f(LocationPointer, Value.x, Value.y, Value.z);
		}

		void Shader::UploadUniformFloatMat4(std::string Location, glm::mat4 Value)
		{
			Enable();
			GLuint LocationPointer = m_Uniforms[Location];
			glUniformMatrix4fv(LocationPointer, 1, GL_FALSE, glm::value_ptr(Value));
		}

		void Shader::UploadUniformInt(std::string Location, GLint Value)
		{
			Enable();
			GLuint LocationPointer = m_Uniforms[Location];
			glUniform1i(LocationPointer, Value);
		}

		void Shader::SetBoundShader(Shader* BoundShader)
		{
			m_BoundShader = BoundShader;
		}

		GLuint Shader::ProgramFromShaders(GLuint Vertex, GLuint Fragment)
		{
			GLint  ShaderStatus;
			GLchar ErrorInfo[4096];

			GLuint ShaderProgram = glCreateProgram();
			glAttachShader(ShaderProgram, Vertex);
			glAttachShader(ShaderProgram, Fragment);
			glLinkProgram(ShaderProgram);
			glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &ShaderStatus);
			if (!ShaderStatus)
			{
				glGetProgramInfoLog(ShaderProgram, 4096, NULL, ErrorInfo);
				std::cout << "Error linking program: " << std::endl;
				std::cout << ErrorInfo << std::endl;
			}
			return ShaderProgram;
		}

		GLuint Shader::ShaderFromFile(GLenum Type, std::string Path)
		{
			GLint  ShaderStatus;
			GLchar ErrorInfo[4096];
			std::string StringSource = utils::FileUtils::ReadTextFile(Path);
			GLchar* Source = (GLchar*)StringSource.c_str();

			GLuint ShaderHandle = glCreateShader(Type);
			glShaderSource(ShaderHandle, 1, &Source, NULL);
			glCompileShader(ShaderHandle);
			glGetShaderiv(ShaderHandle, GL_COMPILE_STATUS, &ShaderStatus);
			if (!ShaderStatus)
			{
				glGetShaderInfoLog(ShaderHandle, 4096, NULL, ErrorInfo);
				std::cout << "Failed to compile shader: " << std::endl;
				std::cout << ErrorInfo << std::endl;
			}
			return ShaderHandle;
		}
	}
}