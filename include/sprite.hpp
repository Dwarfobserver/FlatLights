
#pragma once

#include "glm/vec2.hpp"
#include "texture_view.hpp"

namespace fl {
	
	struct sprite {
		sprite() : texture(), position(), rotation(), scale(1.f) {}

		texture_view texture;
		glm::vec2 position;
		float rotation;
		float scale;
	};

}
