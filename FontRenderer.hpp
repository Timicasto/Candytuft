#ifndef CANDYTUFT_FONTRENDERER_HPP
#define CANDYTUFT_FONTRENDERER_HPP

#include <ft2build.h>
#include "logger.hpp"
#include <vector>
#include <unordered_map>
#include FT_FREETYPE_H
#include "RenderableCharacter.hpp"
#include "Shader.hpp"

static const std::string defVsh = "#version 330 core\nlayout (location = 0) in vec4 vertex;\nout vec2 texCoords;\n\nuniform mat4 projection;\n\nvoid main() {\n    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n    texCoords = vertex.zw;\n}";
static const std::string defFsh = "#version 330 core\nin vec2 texCoords;\nout vec4 color;\n\nuniform sampler2D text;\nuniform vec4 textColor;\n\nvoid main() {\n    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);\n    color = vec4(textColor) * sampled;\n}";

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
	void render(size_t font, const std::wstring& text, float x, float y, float scale, glm::vec4 color);
};


#endif //CANDYTUFT_FONTRENDERER_HPP
