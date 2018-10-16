#include "Timer.h"

namespace fc
{
	namespace utils
	{
		Timer::Timer()
			:m_StartTime(0), m_StopTime(0), m_Running(false)
		{

		}

		Timer::~Timer()
		{

		}

		void Timer::Start()
		{
			m_Running = true;
			m_StartTime = glfwGetTime();
		}

		void Timer::Reset()
		{
			Stop();
			Start();
		}

		void Timer::Stop()
		{
			m_Running = false;
			m_StopTime = glfwGetTime();
		}

		GLfloat Timer::Elapsed()
		{
			return glfwGetTime() - m_StartTime;
		}

		GLfloat Timer::Complete()
		{
			return m_StopTime - m_StartTime;
		}
	}
}