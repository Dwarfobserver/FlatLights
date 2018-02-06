
#pragma once
#include <string_view>

namespace fl {

	class texture {
	public:
		texture() noexcept;
		explicit texture(std::string_view fileName);
		~texture() noexcept;

		texture(texture&& moved) noexcept;
		texture(texture const&) = delete;

		texture& operator=(texture&& moved) noexcept;
		texture& operator=(texture const&) = delete;

		bool empty() const          { return data_ == nullptr; }
		int width() const           { return width_; }
		int height() const          { return height_; }
		int size() const            { return width_ * height_ * 4; }
		uint8_t const* data() const { return data_; }
	private:
		int width_;
		int height_;
		uint8_t* data_;
	};

}
