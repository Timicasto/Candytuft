#ifndef AUDIOFFT_VID_LOGGER_HPP
#define AUDIOFFT_VID_LOGGER_HPP

#include <cstdio>
#include <string>
#include <ctime>
#include <memory>
#include <stdarg.h>
#include <cstring>

namespace Logger {
	typedef enum LogLevel {
		FATAL,
		ERROR,
		WARN,
		INFO,
		DEBUG
	} LogLevel;

	static LogLevel level = DEBUG;

	static void setLogLevel(LogLevel newLevel) {
		level = newLevel;
	}

	static void log(LogLevel l, const std::string &module, const std::string &msg) {
		time_t t;
		time(&t);
		auto local = localtime(&t);
		std::string lvl;
		switch (l) {
			case FATAL:
				lvl = "FATAL]";
				break;
			case ERROR:
				lvl = "ERROR]";
				break;
			case WARN:
				lvl = "WARN] ";
				break;
			case INFO:
				lvl = "INFO] ";
				break;
			case DEBUG:
				lvl = "DEBUG]";
				break;
		}
		if (l <= DEBUG) {
			printf("[%02d:%02d:%02d] [%s [%s] %s\n", local->tm_hour, local->tm_min, local->tm_sec, lvl.c_str(),
			       module.c_str(), msg.c_str());
		}
	}
}
#endif //AUDIOFFT_VID_LOGGER_HPP
