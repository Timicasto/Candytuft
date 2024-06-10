#ifndef CANDYTUFT_TRANSPARENTWINDOW_HPP
#define CANDYTUFT_TRANSPARENTWINDOW_HPP

#include "logger.hpp"
#include <sstream>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GLFW/glfw3.h>

class TransparentWindow {
public:

	TransparentWindow(int width, int height, const std::string& title);

	bool shouldUpdate();

	[[nodiscard]] GLFWwindow *getWindow() const;

	const glm::mat4 &getProjection() const;

private:

	glm::mat4 projection;
	GLFWwindow* window;
	int _width;
	int _height;

};


#endif //CANDYTUFT_TRANSPARENTWINDOW_HPP
