#ifndef CANDYTUFT_TRANSPARENTWINDOW_HPP
#define CANDYTUFT_TRANSPARENTWINDOW_HPP

#include <GL/glx.h>
#include "logger.hpp"
#include <sstream>
#include <X11/extensions/Xrender.h>
#include <X11/Xatom.h>

class TransparentWindow {
public:
	TransparentWindow(Display* display, int posX, int posY, int width, int height, const std::string& title, bool borderless);

private:
	void printFBConfig(GLXFBConfig config);
	void bindContext();

	Display* _display;
	GLXWindow _window;
	GLXFBConfig _config;
	Atom delAtom;

	constexpr static int CONFIG[] = {
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_DOUBLEBUFFER, True,
			GLX_RED_SIZE, 8,
			GLX_GREEN_SIZE, 8,
			GLX_BLUE_SIZE, 8,
			GLX_ALPHA_SIZE, 8,
			GLX_DEPTH_SIZE, 16,
			None
	};

};


#endif //CANDYTUFT_TRANSPARENTWINDOW_HPP
