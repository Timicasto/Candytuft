#include "TransparentWindow.hpp"

TransparentWindow::TransparentWindow(int width, int height, const std::string& title) : _width(width), _height(height) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);

	glfwSwapInterval(0);

	window = glfwCreateWindow(_width, _height, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
	}

	projection = glm::ortho(0.0F, (float)width, 0.0F, (float)height);
}

bool TransparentWindow::shouldUpdate() {
	return !glfwWindowShouldClose(window);
}

GLFWwindow *TransparentWindow::getWindow() const {
	return window;
}

const glm::mat4 &TransparentWindow::getProjection() const {
	return projection;
}
