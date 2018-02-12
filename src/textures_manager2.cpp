/*
#include "textures_manager.hpp"
#include "texture_view.hpp"
#include "utils.hpp"
#include <GL/glew.h>
#include <stb_image.h>
#include <glm/vec2.hpp>
#include <algorithm>

namespace fl {

	textures_manager::textures_manager() :
		textures_(size * size),
		normalMaps_(size * size),
		cursorX_(0),
		cursorY_(0),
		rowHeight_(0),
		texturesId_(0),
		normalMapsId_(0),
		hasAutomaticUpdate_(true)
	{
		// Set normal default value to (127, 127, 255) which match to the normal vector (0, 0, 1)
		uint32_t pixel = 0;
		pixel += 127;
		pixel += 127 << 8;
		pixel += 255 << 16;
		pixel += 255 << 24;
		fill(normalMaps_.begin(), normalMaps_.end(), pixel);

		// OpenGL need to load images in inverted order
		stbi_set_flip_vertically_on_load(true);
	}

	textures_manager::~textures_manager() noexcept {
		destroyTextures();
	}

	void textures_manager::update_textures() {
		destroyTextures();
		createTextures();
	}

	texture_view textures_manager::store_from_file(std::string_view textureFile) {
		int width, height, channels;
		uint8_t* data = stbi_load(textureFile.data(), &width, &height, &channels, 4);

		FL_ASSERT(data != nullptr, stbi_failure_reason());
		auto freeData{ defer([&] { stbi_image_free(data); }) };

		return store_from_data(data, width, height);
	}

	texture_view textures_manager::store_from_file(std::string_view textureFile, std::string_view normalMapFile) {
		int width1, height1, channels1;
		uint8_t* textureData = stbi_load(textureFile.data(), &width1, &height1, &channels1, 4);

		FL_ASSERT(textureData != nullptr, stbi_failure_reason());
		auto freeTexture{ defer([&] { stbi_image_free(textureData); }) };

		int width2, height2, channels2;
		uint8_t* normalData = stbi_load(normalMapFile.data(), &width2, &height2, &channels2, 4);

		FL_ASSERT(normalData != nullptr, stbi_failure_reason());
		auto freeNormal{ defer([&] { stbi_image_free(normalData); }) };

		FL_ASSERT(width1 == width2 && height1 == height2,
			"The texture and the normal map files passed do not havec the same dimensions :\n"
			"texture width = " + std::to_string(width1) + ", normal map width = " + std::to_string(width2) +
			", texture height = " + std::to_string(height1) + ", normal map height = " + std::to_string(height2));

		return store_from_data(textureData, normalData, width1, height1);
	}

	texture_view textures_manager::store_from_data(uint8_t* texture, int width, int height) {
		return store_from_data(texture, nullptr, width, height);
	}

	texture_view textures_manager::store_from_data(uint8_t* texture, uint8_t* normalMap, int width, int height) {
		uint32_t* pTexture = reinterpret_cast<uint32_t*>(texture);
		uint32_t* pNormal = reinterpret_cast<uint32_t*>(normalMap);

		if (!can_store(width, height)) throw std::runtime_error
		{ "textures_manager could not store a texture." };

		// Copy on same row
		if (width <= size - cursorX_) {
			rowHeight_ = std::max(height, rowHeight_);
		}
		// Copy on next row
		else {
			cursorX_ = 0;
			cursorY_ += rowHeight_;
			rowHeight_ = height;
		}

		// Make view

		texture_view view;
		view.cursorX_ = cursorX_;
		view.cursorY_ = cursorY_;
		view.width_ = width;
		view.height_ = height;

		// Copy data

		cursorX_ += width;
		const auto shift = cursorX_ + cursorY_ * size;

		if (normalMap != nullptr) {
			const auto texureDst = textures_.data() + shift;
			const auto normalDst = normalMaps_.data() + shift;
			for (int i = 0; i < height; ++i) {
				std::copy(pTexture + i * width, pTexture + i * (width + 1), texureDst);
				std::copy(pNormal + i * width , pNormal + i * (width + 1) , normalDst);
			}
		}
		else {
			const auto texureDst = textures_.data() + shift;
			for (int i = 0; i < height; ++i) {
				std::copy(pTexture + i * width, pTexture + i * (width + 1), texureDst);
			}
		}

		// Create textures

		if (hasAutomaticUpdate_) { // Do it conditionally for normap map
			destroyTextures();
			createTextures();
		}

		return view;
	}

	texture_view textures_manager::get_storage_view() const {
		texture_view view;
		view.cursorX_ = 0;
		view.cursorY_ = 0;
		view.width_ = size;
		view.height_ = size;
		return view;
	}

	bool textures_manager::can_store(int width, int height) const {

		const int newH = std::max(height, rowHeight_);

		// Try current texture row
		if (newH > size - cursorY_) return false;

		// Try next texture row
		if (width > size - cursorX_)
			if (height > size - cursorY_ - rowHeight_) return false;

		return true;
	}

	void textures_manager::destroyTextures() noexcept {
		if (!empty()) {
			glDeleteTextures(2, &texturesId_);
		}
	}

	void textures_manager::createTextures() {
		glGenTextures(2, &texturesId_);

		glBindTexture(GL_TEXTURE_2D, texturesId_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, textures_.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, normalMapsId_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, normalMaps_.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

}
*/