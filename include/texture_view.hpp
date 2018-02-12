
#pragma once

#include "glm/fwd.hpp"

namespace fl {
	
	/// Represents an area of the texture manager where a texture is stored.
	/// This class cannot be modified.
	class texture_view {
		friend class textures_manager;
	public:
		texture_view() noexcept;

		/// Convert the texture's coordinates to coordinates in the global storage.
		glm::vec2 coord(float percentX, float percentY) const;
		glm::vec2 coord(glm::vec2 percent) const;

		/// Creates a texture view which must be contained in the current view.
		texture_view sub_view(int x, int y, int width, int height) const;

		/// Indicates if the view has been default-constructed.
		bool empty() const { return width_ == 0; }

		/// Returns the texture's width in pixels.
		int width()  const { return width_; }

		/// Returns the texture's height in pixels.
		int height() const { return height_; }
	private:
		int width_;
		int height_;
		int cursorX_;
		int cursorY_;
	};

}
