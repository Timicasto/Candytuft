#include <locale>
#include <codecvt>
#include "Hitokoto.hpp"

std::wstring Hitokoto::renew() {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.from_bytes(Utils::requestNetwork("https://v1.hitokoto.cn/?encode=text").c_str());
}
