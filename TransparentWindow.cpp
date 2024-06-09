#include "TransparentWindow.hpp"
#include "utils.hpp"

TransparentWindow::TransparentWindow(Display* display, int posX, int posY, int width, int height, const std::string& title, bool borderless): _display(display) {
	if (!_display) {
		Logger::log(Logger::FATAL, "LIFECYCLE-X11", "Couldn't communicate with X server");
	}

	int xscreen = DefaultScreen(_display);
	int numConfigs;
	Window root = RootWindow(_display, xscreen);
	GLXFBConfig* fbConfigs = glXChooseFBConfig(_display, xscreen, CONFIG, &numConfigs);
	GLXFBConfig config = nullptr;
	XVisualInfo* visual;
	XRenderPictFormat* format;

	for (int i = 0; i < numConfigs; ++i) {
		visual = glXGetVisualFromFBConfig(_display, fbConfigs[i]);
		if (!visual) {
			continue;
		}

		format = XRenderFindVisualFormat(_display, visual -> visual);
		if (!format) {
			continue;
		}

		config = fbConfigs[i];
		if (format -> direct.alphaMask > 0) {
			break;
		}

		XFree(visual);
	}

	if (!config) {
		Logger::log(Logger::FATAL, "LIFECYCLE-X11", "No matching FB config found.");
	}

	printFBConfig(config);
	_config = config;

	XSetWindowAttributes attr = {0, };
	Colormap  map = XCreateColormap(_display, root, visual -> visual, AllocNone);

	attr.colormap = map;
	attr.background_pixel = None;
	attr.border_pixmap = None;
	attr.border_pixel = 0;
	attr.event_mask =
			StructureNotifyMask | EnterWindowMask | LeaveWindowMask | ExposureMask | ButtonPressMask |
			ButtonReleaseMask | OwnerGrabButtonMask | KeyPressMask | KeyReleaseMask;
	int attrMask = CWColormap | CWBorderPixel | CWEventMask;

	Window window = XCreateWindow(_display, root, posX, posY, width, height, 0, visual -> depth, InputOutput, visual -> visual, attrMask, &attr);

	if (!window) {
		Logger::log(Logger::FATAL, "LIFECYCLE-X11", "Failed to create X window");
	}

	_window = window;

	XTextProperty textProp = {
		.value = (unsigned char*) title.c_str(),
		.encoding = XA_STRING,
		.format = 8,
		.nitems = title.length()
	};

	XSizeHints hints = {
			.flags = USPosition | USSize,
			.x = posX,
			.y = posY,
			.width = width,
			.height = height
	};

	XWMHints* startupState = XAllocWMHints();
	startupState -> initial_state = NormalState;
	startupState -> flags = StateHint;

	XSetWMProperties(_display, window, &textProp, &textProp, nullptr, 0, &hints, startupState, nullptr);

	if (borderless) {
		struct MwmHints {
			unsigned long flags;
			unsigned long functions;
			unsigned long decorations;
			long inputMode;
			unsigned long status;
		};
		Atom prop = XInternAtom(_display, "_MOTIF_WM_HINTS", 0);
		struct MwmHints mwmHints {
			.flags = 1L << 1,
			.decorations = 0
		};
		XChangeProperty(_display, window, prop, prop, 32, PropModeReplace, (unsigned char*)&mwmHints, 5);
	}

	XFree(startupState);

	XMapWindow(_display, window);

	if ((delAtom = XInternAtom(_display, "WM_DELETE_WINDOW", 0)) != None) {
		XSetWMProtocols(_display, window, &delAtom, 1);
	}

	bindContext();
}

void TransparentWindow::printFBConfig(GLXFBConfig config) {
	int doubleBuffer;
	int rBit, gBit, bBit, aBit, depth;

	glXGetFBConfigAttrib(_display, config, GLX_DOUBLEBUFFER, &doubleBuffer);
	glXGetFBConfigAttrib(_display, config, GLX_RED_SIZE, &rBit);
	glXGetFBConfigAttrib(_display, config, GLX_GREEN_SIZE, &gBit);
	glXGetFBConfigAttrib(_display, config, GLX_BLUE_SIZE, &bBit);
	glXGetFBConfigAttrib(_display, config, GLX_ALPHA_SIZE, &aBit);
	glXGetFBConfigAttrib(_display, config, GLX_DEPTH_SIZE, &depth);

	std::stringstream log;
	log << "Initialized with FBConfig: Doublebuffer: ";
	log << doubleBuffer << " Red Bits: " << rBit << " Green Bits: " << gBit << " Blue Bits: " << bBit;
	log << " Alpha Bits: " << aBit << " Depth Bits: " << depth;

	Logger::log(Logger::INFO, "LIFECYCLE-X11", log.str());
}

static int error(Display* dpy, XErrorEvent* evt) {
	Logger::log(Logger::FATAL, "LIFECYCLE-X11", "ERROR OCCURRED IN CONTEXT CREATION.");
	return 0;
}

void TransparentWindow::bindContext() {
	int dummy;
	if (!glXQueryExtension(_display, &dummy, &dummy)) {
		Logger::log(Logger::FATAL, "LIFECYCLE-X11", "OpenGL IS NOT SUPPORTED ON CURRENT X SERVER");
	}

	GLXContext context;

	if (Utils::checkExtension(glXQueryExtensionsString(_display, DefaultScreen(_display)), "GLX_ARB_create_context")) {
		typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
		auto arbProc = (glXCreateContextAttribsARBProc)glXGetProcAddressARB(
				reinterpret_cast<const GLubyte *>("glXCreateContextAttribsARB"));
		if (arbProc) {
			int attribs[] = {
					0x2091, 2, 0x2092, 1, None
			};

			int (*oldHandler)(Display*, XErrorEvent*) = XSetErrorHandler(&error);

			context = arbProc(_display, _config, 0, True, attribs);
			XSync(_display, False);
			XSetErrorHandler(oldHandler);
		} else {
			Logger::log(Logger::FATAL, "LIFECYCLE-X11", "glXCreateContextAttribsARB could not be retrieved");
		}
	} else {
		Logger::log(Logger::FATAL, "LIFECYCLE-X11", "glXCreateContextAttribsARB is not supported");
	}

	if (!context) {
		Logger::log(Logger::WARN, "LIFECYCLE-X11", "GL ARB is not supported, falling back to GL");

		context = glXCreateNewContext(_display, _config, GLX_RGBA_TYPE, 0, True);
		if (!context) {
			Logger::log(Logger::FATAL, "LIFECYCLE-X11", "GL is not supported too, context creation failed");
		}
	}

	if (!glXMakeContextCurrent(_display, _window, _window, context)) {
		Logger::log(Logger::FATAL, "LIFECYCLE-X11", "Failed to validate GL context");
	}
}
