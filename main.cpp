#include "TransparentWindow.hpp"

int main() {
	TransparentWindow window = TransparentWindow(XOpenDisplay(nullptr), 100, 100, 200, 200, "Test", true);
}
