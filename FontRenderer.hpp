#ifndef CANDYTUFT_FONTRENDERER_HPP
#define CANDYTUFT_FONTRENDERER_HPP

#include <ft2build.h>
#include "logger.hpp"
#include <vector>
#include <unordered_map>
#include FT_FREETYPE_H
#include "RenderableCharacter.hpp"
#include "Shader.hpp"

static const std::string defVsh = "./text.vsh";
static const std::string defFsh = "./text.fsh";

class FontRenderer {

private:
	GLuint vao{}, vbo{};
	FT_Library lib;
	std::vector<std::unordered_map<wchar_t, RenderableCharacter>> fonts;
	Shader s;

public:
	FontRenderer();
	explicit FontRenderer(Shader shader);
	size_t loadFont(const std::string& path, uint32_t mode, int size);
    std::tuple<int, int> render(size_t font, const std::wstring &text, float x, float y, float scale, glm::vec4 color, glm::mat4 projection);
};


#endif //CANDYTUFT_FONTRENDERER_HPP
