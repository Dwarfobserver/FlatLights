
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string_view>

namespace fl {

	class window {
	public:
		window(int width, int height, std::string_view title);
		~window() noexcept;

		GLFWwindow* handle() { return handle_; }
	private:
		GLFWwindow* handle_;
	};

}
