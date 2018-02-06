
#include "texture.h"
#include "stb_image.h"
#include <string>

namespace fl {

	texture::texture() noexcept :
		width_(),
		height_(),
		data_()
	{}

	texture::texture(std::string_view fileName) {
		int channels;
		data_ = stbi_load(fileName.data(), &width_, &height_, &channels, 4);

		if (channels != 4) throw std::runtime_error{
			"Channels = " + std::to_string(channels) + " instead of 4" };
	}

	texture::~texture() noexcept {
		if (data_) stbi_image_free(data_);
	}

	texture::texture(texture&& moved) noexcept :
		width_ (moved.width_),
		height_(moved.height_),
		data_  (moved.data_)
	{
		moved.width_  = 0;
		moved.height_ = 0;
		moved.data_   = nullptr;
	}

	texture& texture::operator=(texture&& moved) noexcept {
		if (data_) stbi_image_free(data_);

		width_  = moved.width_;
		height_ = moved.height_;
		data_   = moved.data_;

		moved.width_  = 0;
		moved.height_ = 0;
		moved.data_   = nullptr;
		
		return *this;
	}

}
