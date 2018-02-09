
#pragma once

#include "shader.hpp"

namespace fl {
	
	class shader_program {
	public:
		shader_program(shader const& vertexShader, shader const& fragmentShader);
		~shader_program() noexcept;

		GLuint id() const { return id_; }
	private:
		GLuint id_;
	};

}
