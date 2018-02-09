
#pragma once
#include <string_view>
#include <GL/glew.h>

namespace fl {

	enum class shader_type { vertex, fragment };

	GLenum get_gl_enum(shader_type type);
	std::string to_string(shader_type type);

	class shader {
	public:
		shader(shader_type type, std::string_view file);
		~shader() noexcept;

		shader_type type() const { return type_; }
		GLuint id() const        { return id_; }
	private:
		shader_type type_;
		GLuint id_;
	};

}
