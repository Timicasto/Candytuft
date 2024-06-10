#ifndef CANDYTUFT_TRANSPARENTWINDOW_HPP
#define CANDYTUFT_TRANSPARENTWINDOW_HPP

#include "logger.hpp"
#include <sstream>
#include "glad/glad.h"

#include <GLFW/glfw3.h>

class TransparentWindow {
public:

	TransparentWindow(int width, int height, const std::string& title);

	bool shouldUpdate();

	[[nodiscard]] GLFWwindow *getWindow() const;

private:

	GLFWwindow* window;
	int _width;
	int _height;

};


#endif //CANDYTUFT_TRANSPARENTWINDOW_HPP
