
#include "shader_program.hpp"
#include "utils.hpp"

namespace fl {

	shader_program::shader_program(shader const& vertexShader, shader const& fragmentShader) {
		FL_ASSERT(vertexShader.type()   == shader_type::vertex,
				  "Wrong shader type passed to the shader program");
		FL_ASSERT(fragmentShader.type() == shader_type::fragment,
				  "Wrong shader type passed to the shader program");

		// Link program
		id_ = glCreateProgram();
		glAttachShader(id_, vertexShader.id());
		glAttachShader(id_, fragmentShader.id());
		glLinkProgram(id_);

		// Check program
		int logLength;
		glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0) {
			std::string errorMessage(logLength, '\0');
			glGetProgramInfoLog(id_, logLength, nullptr, errorMessage.data());
			throw std::runtime_error{ errorMessage };
		}

		// Detach shaders
		glDetachShader(id_, vertexShader.id());
		glDetachShader(id_, fragmentShader.id());
	}

	shader_program::~shader_program() noexcept {
		glDeleteProgram(id_);
	}

}
