#include <thread>
#include <fstream>
#include "FontRenderer.hpp"
#include "TransparentWindow.hpp"
#include "modules/Hitokoto.hpp"

int main() {
    int w = 800, h = 600;
    TransparentWindow window = TransparentWindow(w, h, "test");
	auto renderer = FontRenderer();
	auto font = renderer.loadFont("./AlibabaPuHuiTi-2-65-Medium.ttf", 0b01 | 0b10, 32);
	std::wstring str = Hitokoto::renew();

	while (window.shouldUpdate()) {
        glClear(GL_COLOR_BUFFER_BIT);
        std::tie(w, h) = renderer.render(font, str, 0.0F, 8.0F, 1.0F, glm::vec4(0.2F, 0.8F, 1.0F, 1.0F), window.getProjection());
        glfwSetWindowSize(window.getWindow(), w, h);
		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
	}

	return 0;
}
