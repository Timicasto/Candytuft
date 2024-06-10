#ifndef CANDYTUFT_UTILS_HPP
#define CANDYTUFT_UTILS_HPP

#include <string>
#include <cstring>

extern "C" {
#include <curl/curl.h>
};

namespace Utils {
	static std::string tmp;

	static size_t recv(void* ptr, size_t size, size_t byteSize, void* userPtr) {
		char* buffer = new char[byteSize];
		memcpy(buffer, ptr, byteSize);
		tmp = std::string(buffer);
		return size * byteSize;
	}

	static std::string requestNetwork(const std::string& url) {
		CURL* curl = curl_easy_init();
		if (curl) {
			CURLcode ret;
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			tmp = "";
			tmp = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, recv);
			ret = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
		}
		return tmp;
	}
};

#endif //CANDYTUFT_UTILS_HPP
