
#include "window.hpp"

#include "utils.hpp"
#include "sprite.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace fl {

	window* window::pInstance = nullptr;

	window::window(int width, int height, std::string_view title) {
		FL_ASSERT(pInstance == nullptr, "A window has already been created.");

		glfwSetErrorCallback([](int error, char const* msg) {
			std::cerr << "GLFW error " << error << " : " << msg << '\n';
		});

		FL_ASSERT(glfwInit(), "GLFW could not be initialized.");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		handle_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
		if (!handle_) {
			glfwTerminate();
			throw std::runtime_error{ "GLFW window could not be created" };
		}

		glfwMakeContextCurrent(handle_);

		glfwSetFramebufferSizeCallback(handle_, [](GLFWwindow*, int w, int h) {
			glViewport(0, 0, w, h);
		});

		if (const auto err = glewInit(); err != GLEW_OK)
		{
			const auto msg = reinterpret_cast<char const*>(glewGetErrorString(err));
			glfwTerminate();
			throw std::runtime_error{ msg };
		}
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(static_cast<GLDEBUGPROC>([]
				(GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam) {
			std::cerr << "GL callback : " << message << '\n';
		}), nullptr);

		glViewport(0, 0, width, height);
		glfwSwapInterval(1);

		//glGenVertexArrays(1, &vao_);
		glCreateBuffers(1, &vbo_);

		pInstance = this;
	}

	window::~window() noexcept {
		glDeleteBuffers(1, &vbo_);
		glfwDestroyWindow(handle_);
		glfwTerminate();
	}

	void window::draw_sprite(sprite const& s) {
		vertex_t vertexes[4];

		vertexes[0].position = s.position;
		vertexes[1].position = s.position + glm::vec2{ s.texture.width(), 0 };
		vertexes[2].position = s.position + glm::vec2{ 0,                 s.texture.height() };
		vertexes[3].position = s.position + glm::vec2{ s.texture.width(), s.texture.height() };

		vertexes[0].texCoord = s.texture.coord(0.f, 0.f);
		vertexes[1].texCoord = s.texture.coord(1.f, 0.f);
		vertexes[2].texCoord = s.texture.coord(0.f, 1.f);
		vertexes[3].texCoord = s.texture.coord(1.f, 1.f);

		vertexes_.push_back(vertexes[0]);
		vertexes_.push_back(vertexes[1]);
		vertexes_.push_back(vertexes[2]);
		vertexes_.push_back(vertexes[1]);
		vertexes_.push_back(vertexes[2]);
		vertexes_.push_back(vertexes[3]);
	}

	void window::display() {
		glDeleteBuffers(1, &vbo_);
		glCreateBuffers(1, &vbo_);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * vertexes_.size(), vertexes_.data(), GL_STATIC_DRAW);

		const auto vertexSize = 4 * sizeof(float);
		const auto vertexBegin = static_cast<float*>(nullptr);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertexSize, vertexBegin);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexSize, vertexBegin + 2);

		glDrawArrays(GL_TRIANGLES, 0, vertexes_.size());

		vertexes_.clear();

		glfwSwapBuffers(handle_);

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void window::poll_events() {
		glfwPollEvents();
	}

}
