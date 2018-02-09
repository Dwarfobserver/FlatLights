
#pragma once

#include "fwd_opengl.hpp"
#include <vector>
#include <optional>
#include <glm/vec2.hpp>

namespace fl {

	class texture_storage;
	class texture_handle {
		friend class texture_storage;
	public:
		glm::vec2 coord(float x, float y) const;
		glm::vec2 coord(glm::vec2 coord)  const;
	private:
		int width_;
		int height_;
		int x_;
		int y_;
		int maxW_;
		int maxH_;
	};
	
	class texture_storage {
	public:
		texture_storage(int width, int height);
		~texture_storage() noexcept;

		texture_storage(texture_storage&& moved) noexcept;
		texture_storage(texture_storage const&) = delete;

		texture_storage& operator=(texture_storage&& moved) noexcept;
		texture_storage& operator=(texture_storage const&) = delete;

		bool empty() const { return id_ == 0; }
		int width()  const { return width_; }
		int height() const { return height_; }
		GLuint id()  const { return id_; }

		std::optional<texture_handle> try_store(std::string_view fileName);
	private:
		const int width_;
		const int height_;
		GLuint id_;
		std::vector<char> content_;

	};

}
