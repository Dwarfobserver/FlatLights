
#include "window.hpp"
#include <iostream>

namespace fl {

	window::window(int width, int height, std::string_view title) {
		if (!glfwInit()) throw std::runtime_error{ "GLFW could not be initialized" };

		glfwSetErrorCallback([] (int error, char const* msg) {
			std::cerr << "GLFW error " << error << " : " << msg << '\n';
		});

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		handle_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
		if (!handle_) {
			glfwTerminate();
			throw std::runtime_error{ "GLFW window could not be created" };
		}

		glfwMakeContextCurrent(handle_);

		if (const auto err = glewInit(); err != GLEW_OK)
		{
			const auto msg = reinterpret_cast<char const*>(glewGetErrorString(err));
			glfwTerminate();
			throw std::runtime_error{ msg };
		}

		glfwSetFramebufferSizeCallback(handle_, [] (GLFWwindow*, int w, int h) {
			glViewport(0, 0, w, h);
		});

		glViewport(0, 0, width, height);
		glfwSwapInterval(1);
	}

	window::~window() noexcept {
		glfwDestroyWindow(handle_);
		glfwTerminate();
	}


}
