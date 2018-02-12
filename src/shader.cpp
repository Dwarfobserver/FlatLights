
#include <fstream>
#include <sstream>
#include "shader.hpp"
#include "utils.hpp"
#include <vector>

namespace fl {

	GLenum get_gl_enum(shader_type type) {
		switch (type) {
			case shader_type::vertex:   return GL_VERTEX_SHADER;
			case shader_type::fragment: return GL_FRAGMENT_SHADER;
			default: throw std::runtime_error{ "Wrong shader_type value" };
		}
	}

	std::string to_string(shader_type type) {
		switch (type) {
			case shader_type::vertex:   return "vertex";
			case shader_type::fragment: return "fragment";
			default: throw std::runtime_error{ "Wrong shader_type value" };
		}
	}

	shader::shader(shader_type type, std::string_view file) :
		type_(type)
	{
		// Create shader
		const GLenum glType = get_gl_enum(type);
		id_ = glCreateShader(glType);

		// read shader file
		std::ifstream fileStream{ file.data(), std::ios::in };
		FL_ASSERT(fileStream.is_open(), "Impossible to open " + to_string(type_) + " file at " + file.data());
		std::stringstream sstr;
		sstr << fileStream.rdbuf();
		auto code = sstr.str();

		// Compile shader
		GLchar const * const pCode = code.c_str();
		glShaderSource(id_, 1, &pCode, nullptr);
		glCompileShader(id_);

		// Check compilation errors
		int logLength;
		glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0) {
			std::string errorMessage(logLength, '\0');
			glGetShaderInfoLog(id_, logLength, nullptr, errorMessage.data());
			throw std::runtime_error{ errorMessage };
		}
	}

	shader::~shader() noexcept {
		glDeleteShader(id_);
	}

}
