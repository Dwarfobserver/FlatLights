
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

int main(int argc, char** argv)
{
	stbi_set_flip_vertically_on_load(true);

	if (!glfwInit())
		return -1;

	const auto pWindow = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!pWindow)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(pWindow);

	if (const auto err = glewInit(); err != GLEW_OK)
	{
		std::cerr << "Error : " << glewGetErrorString(err) << '\n';
	}

	std::cout << "OpenGL v" << glGetString(GL_VERSION) << '\n';

	while (!glfwWindowShouldClose(pWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(pWindow);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
