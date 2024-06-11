#include <locale>
#include <codecvt>
#include "Hitokoto.hpp"

std::wstring Hitokoto::renew() {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring result = conv.from_bytes(Utils::requestNetwork("https://v1.hitokoto.cn/?encode=text").c_str());
    return result.empty() ? conv.from_bytes("[Error fetching hitokoto]") : result;
}

void Hitokoto::updateString(const std::wstring& s){
    str = renew();
}

std::wstring Hitokoto::getString() {
    return str;
}
