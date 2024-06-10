#include "FontRenderer.hpp"
#include "TransparentWindow.hpp"

int main() {
	TransparentWindow window = TransparentWindow(800, 600, "test");
	auto renderer = FontRenderer();
	auto font = renderer.loadFont("./AlibabaPuHuiTi-2-65-Medium.ttf", 0b01 | 0b10, 32);

	while (window.shouldUpdate()) {
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		renderer.render(font, L"测试文本", 0.0F, 8.0F, 1.0F, glm::vec4(1.0F, 0.8F, 1.0F, 0.65F));

		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
	}

	return 0;
}
