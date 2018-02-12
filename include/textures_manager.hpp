
#pragma once

#include "fwd_opengl.hpp"
#include <vector>
#include <string_view>
#include <glm/fwd.hpp>

namespace fl {

	class texture_view;

	class textures_manager {
	public:
		static constexpr int size = 2048;

		textures_manager();
		~textures_manager() noexcept;

		void set_automatic_update(bool b) { hasAutomaticUpdate_ = b; }
		bool has_automatic_update() const { return hasAutomaticUpdate_; }
		void update_textures();

		texture_view store_from_file(std::string_view textureFile);
		texture_view store_from_file(std::string_view textureFile, std::string_view normalMapFile);
		texture_view store_from_data(uint8_t* texture, int width, int height);
		texture_view store_from_data(uint8_t* texture, uint8_t* normalMap, int width, int height);

		texture_view get_storage_view() const;

		bool empty() const { return texturesId_ == 0; }
		bool can_store(int width, int height) const;

		GLuint textures_id() const { return texturesId_; }
		GLuint normal_maps_id() const { return normalMapsId_; }
	private:
		std::vector<uint8_t> textures_;
		std::vector<uint8_t> normalMaps_;
		int cursorX_;
		int cursorY_;
		int rowHeight_;
		GLuint texturesId_;
		GLuint normalMapsId_;
		bool hasAutomaticUpdate_;

		void destroyTextures() noexcept;
		void createTextures();
	};

}
