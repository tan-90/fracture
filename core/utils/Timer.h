#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace fc
{
	namespace utils
	{
		class Timer
		{
		public:
			Timer();
			~Timer();

			void Start();
			void Reset();

			void Stop();
			GLfloat Elapsed();

			GLfloat Complete();

		private:
			GLfloat m_StartTime;
			GLfloat m_StopTime;

			bool m_Running;
		};
	}
}