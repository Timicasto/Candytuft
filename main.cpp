#include <thread>
#include <fstream>
#include "FontRenderer.hpp"
#include "TransparentWindow.hpp"
#include "modules/Hitokoto.hpp"

size_t load = 0;
size_t prev = 0;

void updateLoad() {
	std::string line;
	while (1) {
		std::ifstream str("/proc/stat");
		getline(str, line);
		size_t num = std::stoull(Utils::split(line, " ")[5]);
		load = num - prev;
		prev = num;
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(333ms);
	}
}

int main() {
	TransparentWindow window = TransparentWindow(800, 600, "test");
	auto renderer = FontRenderer();
	auto font = renderer.loadFont("./AlibabaPuHuiTi-2-65-Medium.ttf", 0b01 | 0b10, 32);
	std::wstring str = Hitokoto::renew();

	std::thread cpuload(updateLoad);
	cpuload.detach();

	while (window.shouldUpdate()) {
		glClear(GL_COLOR_BUFFER_BIT);

		renderer.render(font, std::to_wstring((double)((double)load * 3.0 / 12.0)), 0.0F, 8.0F, 1.0F, glm::vec4(0.2F, 0.8F, 1.0F, 1.0F), window.getProjection());

		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
	}

	return 0;
}
