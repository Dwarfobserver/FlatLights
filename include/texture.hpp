
#pragma once

#include <string_view>
#include <GL/glew.h>

namespace fl {

	class texture {
	public:
		texture() noexcept;
		~texture() noexcept;
		explicit texture(std::string_view fileName);

		texture(texture&& moved) noexcept;
		texture(texture const&) = delete;

		texture& operator=(texture&& moved) noexcept;
		texture& operator=(texture const&) = delete;

		void load_from_file(std::string_view fileName);

		GLuint id() const           { return id_; }
		bool empty() const          { return data_ == nullptr; }
		int width() const           { return width_; }
		int height() const          { return height_; }
		int size() const            { return width_ * height_ * 4; }
		uint8_t const* data() const { return data_; }
	private:
		void destroy() noexcept;
		void reset() noexcept;

		GLuint id_;
		int width_;
		int height_;
		uint8_t* data_;
	};

}
