#ifndef CANDYTUFT_UTILS_HPP
#define CANDYTUFT_UTILS_HPP

namespace Utils {
		static bool checkExtension(const char *extList, const char *ext) {
			const char *start, *where, *terminator;

			where = strchr(ext, ' ');
			if (where || *ext == '\0') {
				return false;
			}

			for (start = extList;;) {
				where = strstr(start, ext);
				if (!where) {
					break;
				}

				terminator = where + strlen(ext);

				if (where == start || *(where - 1) == ' ') {
					if (*terminator == ' ' || *terminator == '\0') {
						return true;
					}
				}

				start = terminator;
			}
			return false;
		}
};

#endif //CANDYTUFT_UTILS_HPP
