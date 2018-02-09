
#include "texture_storage.hpp"
#include "utils.hpp"
#include <GL/glew.h>

namespace fl {
	
	texture_storage::texture_storage(int width, int height) :
		width_(width),
		height_(height),
		id_(0),
		content_(width * height)
	{
		FL_ASSERT(width <= 2048 && height <= 2048,
				"Texture storage dimensions can't be superior to 2048.");

		glGenTextures(1, &id_);
		glBindTexture(GL_TEXTURE_2D, id_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, content_.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		GL_CHECK_ERRORS();

	}

	texture_storage::~texture_storage() noexcept {
		glDeleteTextures(1, &id_);
	}

	std::optional<texture_handle> texture_storage::try_store(std::string_view fileName) {
		texture_handle handle;
	}

}
