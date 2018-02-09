
#include "utils.hpp"
#include <GL/glew.h>

using namespace std::string_literals;

namespace fl::detail {

	void gl_check_errors() {
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::string messages;
			do {
				messages += "GL error code = " + std::to_string(error) + '\n';
				error = glGetError();
			} while (error != GL_NO_ERROR);
			throw std::runtime_error{ messages };
		}
	}

	void assert_failed(char const* expr, char const* file, int line, std::string const& msg) {
		auto str =  "Assert failed in :\n"s + 
					file + "\n"
					"line " + std::to_string(line) + ", at " + expr + ".\n"
					"Error message : " + msg;

		// Remove null-terminated characters
		for (auto& c : str) if (c == 0) c = '_';

		throw std::runtime_error{ str };
	}

}
