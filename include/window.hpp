
#pragma once

#include "fwd_opengl.hpp"
#include "sprite.hpp"
#include <glm/vec2.hpp>
#include <string_view>
#include <vector>

struct GLFWwindow;

namespace fl {

	class shader_program;

	class window {
	public:
		static window& instance() { return *pInstance; }

		window(int width, int height, std::string_view title);
		~window() noexcept;

		GLFWwindow* handle() { return handle_; }

		void draw_sprite(sprite const& s);
		void display();
		void poll_events();
	private:
		static window* pInstance;

		struct vertex_t {
			glm::vec2 position;
			glm::vec2 texCoord;
		};

		std::vector<vertex_t> vertexes_;
		GLFWwindow* handle_;
		GLuint vao_;
		GLuint vbo_;
	};

}
