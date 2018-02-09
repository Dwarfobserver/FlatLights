
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
#include "shader.hpp"
#include "shader_program.hpp"
#include "window.hpp"
#include "utils.hpp"
#include "texture.hpp"

int main(int argc, char** argv)
{
	try {
		stbi_set_flip_vertically_on_load(true);

		fl::window window{ 640, 480, "Hello World" };
		std::cout << "OpenGL v" << glGetString(GL_VERSION) << '\n';

		const fl::texture texture{ "resources/textures/texture.png" };
		const fl::texture normalMap{ "resources/textures/normal.png" };

		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		const float w = texture.width();
		const float h = texture.height();

		float vertexBuffer[] = {
		//   Position  |  Texture
		//       Triangle 1
			0.f, 0.f,   0.f, 0.f,
			w  , 0.f,   1.f, 0.f,
			0.f, h  ,   0.f, 1.f,
		//       Triangle 2
			w  , 0.f,   1.f, 0.f,
			w  , h  ,   1.f, 1.f,
			0.f, h  ,   0.f, 1.f,
		};

		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

		const auto vertexSize = 4 * sizeof(float);
		const auto vertexBegin = static_cast<float*>(nullptr);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertexSize, vertexBegin);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexSize, vertexBegin + 2);

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		GL_CHECK_ERRORS();

		const fl::shader basicVertex  { fl::shader_type::vertex  , "shaders/basic.vert" };
		const fl::shader basicFragment{ fl::shader_type::fragment, "shaders/basic.frag" };
		fl::shader_program shader{ basicVertex, basicFragment };

		glBindVertexArray(vao);
		glUseProgram(shader.id());

		const GLint locViewport = glGetUniformLocation(shader.id(), "uViewport");
		glUniform2f(locViewport, 640, 480);

		const GLint locTexture = glGetUniformLocation(shader.id(), "uTexture");
		glUniform1i(locTexture, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.id());

		const GLint locNormalMap = glGetUniformLocation(shader.id(), "uNormalMap");
		glUniform1i(locNormalMap, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalMap.id());

		const GLint locLight = glGetUniformLocation(shader.id(), "uLightPosition");

		GL_CHECK_ERRORS();

		while (!glfwWindowShouldClose(window.handle()))
		{
			const double tElasped = glfwGetTime();
			glUniform2f(locLight, sinf(tElasped), cosf(tElasped));

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

			glfwSwapBuffers(window.handle());
			glfwPollEvents();
		}

		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		
		GL_CHECK_ERRORS();
	}
	catch (std::exception const& e) {
		std::cerr << e.what();
		std::cout << "Press a touch to exit\n";
		std::cin.get();
	}
	return 0;
}
