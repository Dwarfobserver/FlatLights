
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <iostream>
#include "shader.hpp"
#include "shader_program.hpp"
#include "window.hpp"
#include "utils.hpp"
#include "textures_manager.hpp"

std::ostream& operator<<(std::ostream& os, glm::vec2 const& vec) {
	return os << "{ " << vec.x << ", " << vec.y << " }";
}

int main(int argc, char** argv)
{
	try {
		fl::window window{ 640, 480, "Hello World" };
		std::cout << "OpenGL v" << glGetString(GL_VERSION) << '\n';

		fl::textures_manager texturesManager;

		const auto hScarecrow = texturesManager.store_from_file(
			"resources/textures/texture.png",
			"resources/textures/normal.png");
		/*
		const auto hFrog = texturesManager.store_from_file(
			"resources/textures/FB frog.png",
			"resources/textures/FB frog normal.png");*/

		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		const auto deleteVao = fl::defer([&] { glDeleteVertexArrays(1, &vao); });

		const fl::shader basicVertex  { fl::shader_type::vertex  , "shaders/basic.vert" };
		const fl::shader basicFragment{ fl::shader_type::fragment, "shaders/basic.frag" };
		fl::shader_program shader{ basicVertex, basicFragment };

		glUseProgram(shader.id());

		const GLint locViewport = glGetUniformLocation(shader.id(), "uViewport");
		glUniform2f(locViewport, 640, 480);

		const GLint locTexture = glGetUniformLocation(shader.id(), "uTexture");
		glUniform1i(locTexture, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturesManager.textures_id());

		const GLint locNormalMap = glGetUniformLocation(shader.id(), "uNormalMap");
		glUniform1i(locNormalMap, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texturesManager.normal_maps_id());

		const GLint locLight = glGetUniformLocation(shader.id(), "uLightPosition");

		fl::sprite scarecrow;
		scarecrow.texture = hScarecrow;
		scarecrow.position = { 200, 100 };/*
		fl::sprite frog;
		frog.texture = hFrog;
		frog.position = { 350, 100 };
		fl::sprite texturesView;
		texturesView.texture = texturesManager.get_storage_view();
		texturesView.position = { 0, 0 };*/

		while (!glfwWindowShouldClose(window.handle()))
		{
			const double tElasped = glfwGetTime();
			glUniform2f(locLight, sinf(tElasped), cosf(tElasped));

			window.draw_sprite(scarecrow);
			//window.draw_sprite(texturesView);
			window.display();
			window.poll_events();
		}
	}
	catch (std::exception const& e) {
		std::cerr << e.what();
		std::cout << "Press a touch to exit\n";
		std::cin.get();
	}
	return 0;
}
