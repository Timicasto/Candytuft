#include "FontRenderer.hpp"
#include "TransparentWindow.hpp"
#include "Hitokoto.hpp"

int main() {
	TransparentWindow window = TransparentWindow(800, 600, "test");
	auto renderer = FontRenderer();
	auto font = renderer.loadFont("./AlibabaPuHuiTi-2-65-Medium.ttf", 0b01 | 0b10, 32);
	std::wstring str = Hitokoto::renew();

	while (window.shouldUpdate()) {
		glClear(GL_COLOR_BUFFER_BIT);

		renderer.render(font, str, 0.0F, 8.0F, 1.0F, glm::vec4(0.2F, 0.8F, 1.0F, 1.0F), window.getProjection());

		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
	}

	return 0;
}
