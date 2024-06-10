#ifndef CANDYTUFT_RENDERABLECHARACTER_HPP
#define CANDYTUFT_RENDERABLECHARACTER_HPP

#include <glm/glm.hpp>
#include "glad/glad.h"

class ivec2;

class RenderableCharacter {
private:
	GLuint texId;
	glm::ivec2 size;
	glm::ivec2 bearing;
	GLuint advance;

public:
	RenderableCharacter(GLuint texId, const glm::ivec2& size, const glm::ivec2& bearing, GLuint advance);

	[[nodiscard]] GLuint getTexId() const;

	[[nodiscard]] const glm::ivec2 &getSize() const;

	[[nodiscard]] const glm::ivec2 &getBearing() const;

	[[nodiscard]] GLuint getAdvance() const;

};


#endif //CANDYTUFT_RENDERABLECHARACTER_HPP
