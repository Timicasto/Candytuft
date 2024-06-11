#ifndef CANDYTUFT_HITOKOTO_HPP
#define CANDYTUFT_HITOKOTO_HPP

#include "../utils.hpp"

class Hitokoto {
std::wstring str;
public:
    Hitokoto(): str(renew()){}
	static std::wstring renew();
    void updateString(const std::wstring& s = std::wstring());
    std::wstring getString();
};


#endif //CANDYTUFT_HITOKOTO_HPP
