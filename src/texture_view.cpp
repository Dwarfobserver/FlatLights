
#include "texture_view.hpp"
#include "glm/vec2.hpp"
#include "utils.hpp"
#include "textures_manager.hpp"

namespace fl {

	texture_view::texture_view() noexcept :
		width_(0), height_(0), cursorX_(0), cursorY_(0)
	{}

	glm::vec2 texture_view::coord(float percentX, float percentY) const {
		FL_ASSERT(0.f <= percentX && percentX <= 1.f,
			"texture_view::coord parameters must be between 0 and 1.");
		FL_ASSERT(0.f <= percentY && percentY <= 1.f,
			"texture_view::coord parameters must be between 0 and 1.");

		return { (cursorX_ + percentX * width_) / textures_manager::size,
			(cursorY_ + percentY * height_) / textures_manager::size };
	}

	glm::vec2 texture_view::coord(glm::vec2 percent) const {
		return coord(percent.x, percent.y);
	}

	texture_view texture_view::sub_view(int x, int y, int width, int height) const {
		FL_ASSERT(x >= 0 && y >= 0 && width >= 0 && height >= 0,
			"sub_view parameters must be >= 0.");
		FL_ASSERT(x + width <= width_ && y + height <= height_,
			"sub_view must be contained in the called view.");

		texture_view texture;
		texture.cursorX_ = cursorX_ + x;
		texture.cursorY_ = cursorY_ + y;
		texture.width_ = width;
		texture.height_ = height;
		return texture;
	}


}
