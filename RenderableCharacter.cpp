#include "RenderableCharacter.hpp"

RenderableCharacter::RenderableCharacter(GLuint texId, const glm::ivec2 &size, const glm::ivec2 &bearing,
                                         GLuint advance): texId(texId),
                                                          size(size),
                                                          bearing(bearing),
                                                          advance(advance) {

}

GLuint RenderableCharacter::getTexId() const {
	return texId;
}

const glm::ivec2 &RenderableCharacter::getSize() const {
	return size;
}

const glm::ivec2 &RenderableCharacter::getBearing() const {
	return bearing;
}

GLuint RenderableCharacter::getAdvance() const {
	return advance;
}
