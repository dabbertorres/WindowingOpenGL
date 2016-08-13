#include "Window.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <map>

#include "opengl/gl_glCore33.hpp"

#include "Engine.hpp"

namespace
{
	dbr::gl::exts::LoadTest glLoaded;
}

// used for mapping GLFW callbacks to our windows...
static std::map<GLFWwindow*, dbr::gl::Window*> allWindows;

static void cursorPosCallback(GLFWwindow* window, double x, double y)
{
	allWindows[window]->mouseMove(x, y);
}

namespace dbr
{
	namespace gl
	{
		Window::Window()
			: window(nullptr)
		{}

		Window::~Window()
		{
			if(window != nullptr)
				glfwDestroyWindow(window);
		}

		void Window::open(std::size_t width, std::size_t height, const std::string& title, bool fullscreen, std::size_t monitorIdx)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, gl::TRUE_);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? Engine::instance.get(monitorIdx) : nullptr, nullptr);
			activate();
			
			if(!glLoaded)
			{
				if(!(glLoaded = gl::sys::LoadFunctions()))
					throw std::runtime_error("Failed to acquire OpenGL functions");
			}
			
			allWindows.emplace(window, this);

			glfwSetCursorPosCallback(window, cursorPosCallback);
		}

		void Window::close()
		{
			if(window != nullptr)
				glfwDestroyWindow(window);
		}

		void Window::activate()
		{
			glfwMakeContextCurrent(window);
		}

		void Window::deactivate()
		{
			glfwMakeContextCurrent(nullptr);
		}

		void Window::update()
		{
			glfwPollEvents();
		}

		void Window::clear(const Color& col)
		{
			gl::ClearColor(col.rf(), col.gf(), col.bf(), col.af());
			gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
		}

		void Window::draw()
		{

		}

		void Window::display()
		{
			glfwSwapBuffers(window);
		}

		bool Window::isOpen()
		{
			return !glfwWindowShouldClose(window);
		}

		math::Vector2u Window::windowSize() const
		{
			int w = 0;
			int h = 0;
			glfwGetWindowSize(window, &w, &h);

			return{static_cast<std::size_t>(w), static_cast<std::size_t>(h)};
		}

		math::Vector2u Window::bufferSize() const
		{
			int w = 0;
			int h = 0;
			glfwGetFramebufferSize(window, &w, &h);

			return{static_cast<std::size_t>(w), static_cast<std::size_t>(h)};
		}
	}
}