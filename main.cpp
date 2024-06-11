#include "FontRenderer.hpp"
#include "TransparentWindow.hpp"
#include "modules/Hitokoto.hpp"
int main() {
    int w = 800, h = 600;
    TransparentWindow window = TransparentWindow(w, h, "test");
	auto renderer = FontRenderer();
	auto font = renderer.loadFont("./AlibabaPuHuiTi-2-65-Medium.ttf", 0b01 | 0b10, 32);
    auto hitokoto = Hitokoto();
    glfwSetWindowUserPointer(window.getWindow(), &hitokoto);

    glfwSetKeyCallback(window.getWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mode) mutable{
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (key == GLFW_KEY_ENTER && action == GLFW_PRESS){
            auto ptr = static_cast<Hitokoto*>(glfwGetWindowUserPointer(window));
            ptr->updateString();
        }
    });
    while (window.shouldUpdate()) {
        glClear(GL_COLOR_BUFFER_BIT);
        std::tie(w, h) = renderer.render(font, hitokoto.getString(), 0.0F, 8.0F, 1.0F, glm::vec4(0.2F, 0.8F, 1.0F, 1.0F), window.getProjection());
        glfwSetWindowSize(window.getWindow(), w, h);
        glfwSwapBuffers(window.getWindow());
        glfwWaitEvents();
	}

	return 0;
}
