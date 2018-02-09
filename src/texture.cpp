
#include <string>
#include "texture.hpp"
#include "stb_image.h"
#include "utils.hpp"

namespace fl {

	texture::texture() noexcept {
		reset();
	}

	texture::texture(std::string_view fileName) {
		load_from_file(fileName);
	}

	texture::~texture() noexcept {
		destroy();
	}

	texture::texture(texture&& moved) noexcept :
		id_    (moved.id_),
		width_ (moved.width_),
		height_(moved.height_),
		data_  (moved.data_)
	{
		moved.reset();
	}

	texture& texture::operator=(texture&& moved) noexcept {
		destroy();

		id_     = moved.id_;
		width_  = moved.width_;
		height_ = moved.height_;
		data_   = moved.data_;

		moved.reset();
		
		return *this;
	}

	void texture::load_from_file(std::string_view fileName) {
		destroy();

		int channels;
		data_ = stbi_load(fileName.data(), &width_, &height_, &channels, 4);

		FL_ASSERT(data_ != nullptr, stbi_failure_reason());
		FL_ASSERT(channels == 4   , "Channels = " + std::to_string(channels) + " instead of 4");
		
		glGenTextures(1, &id_);
		glBindTexture(GL_TEXTURE_2D, id_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		GL_CHECK_ERRORS();
	}

	void texture::destroy() noexcept {
		if (data_) {
			stbi_image_free(data_);
			glDeleteTextures(1, &id_);
			reset();
		}
	}

	void texture::reset() noexcept {
		id_ = 0;
		width_ = 0;
		height_ = 0;
		data_ = nullptr;
	}

}
