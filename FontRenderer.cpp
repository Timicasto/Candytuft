#include "FontRenderer.hpp"

FontRenderer::FontRenderer() : FontRenderer(Shader(Shader::EXTERNAL_FILE, defVsh, defFsh)) {

}

FontRenderer::FontRenderer(Shader shader) : s(shader) {
	if (FT_Init_FreeType(&lib)) {
		Logger::log(Logger::FATAL, "FontRenderer", "Failed to initialize Freetype Library");
	} else {
		Logger::log(Logger::INFO, "FontRenderer", "Freetype Library initialized.");
	}
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

size_t FontRenderer::loadFont(const std::string &path, uint32_t mode, int size) {
	FT_Face face;
	if (FT_New_Face(lib, path.c_str(), 0, &face)) {
		Logger::log(Logger::ERROR, "FontRenderer", "Error while reading font file " + path);
	} else {
		Logger::log(Logger::INFO, "FontRenderer",  "Loaded vector font file " + path + " got font face " + face->family_name + "(" + face->style_name + ")" + " and " + std::to_string(face->num_glyphs) + " glyphs");
	}
	if (FT_HAS_FIXED_SIZES(face)) {
		Logger::log(Logger::WARN, "FontRenderer", "Loaded font file contains bitmaps that are fixed size, parsing and rendering may misbehave or exit with an error");
	}
	if (FT_HAS_COLOR(face)) {
		Logger::log(Logger::WARN, "FontRenderer", "Loaded font file contains color, parsing and rendering may misbehave");
	}
	FT_Set_Pixel_Sizes(face, 0, size);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	std::vector<std::pair<wchar_t, wchar_t>> toLoad;
	bool loadAll = false;

	if (mode % 2) {
		toLoad.emplace_back(0, 128);
	}

	if ((mode >> 1) % 2) {
		toLoad.emplace_back(0x4E00, 0x9FEA);
		toLoad.emplace_back(0x3430, 0x4DB5);
		toLoad.emplace_back(0xF900, 0xFAD9);
		toLoad.emplace_back(12246, 12352);
		toLoad.emplace_back(0xFF00, 0xFFEF);
		toLoad.emplace_back(0x2000, 0x206F);
		toLoad.emplace_back(0x3040, 0x30FF);
		toLoad.emplace_back(0x3300, 0x33FF);
		toLoad.emplace_back(0x20000, 0x323AF);
		toLoad.emplace_back(0x1AFF0, 0x1B16F);
		toLoad.emplace_back(0x3000, 0x303F);
	}

	if ((mode >> 7) % 2)  {
		loadAll = true;
	}

	std::unordered_map<wchar_t, RenderableCharacter> fontMap;

	if (loadAll) {
		uint64_t charcode;
		uint32_t index;
		charcode = FT_Get_First_Char(face, &index);
		while (index) {
			if (FT_Load_Char(face, index, FT_LOAD_RENDER)) {
				Logger::log(Logger::ERROR, "FontRenderer", "Error while loading glyph " + std::to_string(charcode));
			} else {
				Logger::log(Logger::DEBUG, "FontRenderer", "Loaded glyph " + std::to_string(charcode) +" from face " + face->family_name);
			}

			GLuint tex;
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			auto ch = RenderableCharacter(tex, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x);
			fontMap.insert(std::make_pair(index, ch));

			charcode = FT_Get_Next_Char(face, charcode, &index);
		}
	}

	for (const auto& range : toLoad) {
		for (auto c = range.first; c <= range.second; ++c) {
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				Logger::log(Logger::ERROR, "FontRenderer", "Error while loading glyph " + std::to_string(c));
			} else {
				Logger::log(Logger::DEBUG, "FontRenderer", "Loaded glyph " + std::to_string(c) +" from face " + face->family_name);
			}
			GLuint tex;
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			auto ch = RenderableCharacter(tex, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x);
			fontMap.insert(std::make_pair(c, ch));
		}
	}

	fonts.emplace_back(fontMap);
	FT_Done_Face(face);
	return fonts.size() - 1;
}

std::tuple<int, int> FontRenderer::render(size_t font, const std::wstring &text, float x, float y, float scale, glm::vec4 color, glm::mat4 projection) {
	s.use();
	s.setVec4f("textColor", color);
	s.setMat4f("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    float w = x, h = y;
	for (const auto& item : text) {
		if ((fonts[font]).find(item) == fonts[font].end()) {
			Logger::log(Logger::ERROR, "FontRenderer", "Char " + std::to_string(item) + "is not found in font " + std::to_string(font));
			continue;
		}
		RenderableCharacter c = (*((fonts[font]).find(item))).second;
		GLfloat xPos = x + c.getBearing().x * scale;
        GLfloat yPos = y - (c.getSize().y - c.getBearing().y) * scale;
        GLfloat wChar = c.getSize().x * scale;
        GLfloat hChar = c.getSize().y * scale;

		GLfloat vertices[6][4] = {
                {xPos, yPos + hChar, 0.0, 0.0},
				{xPos, yPos, 0.0, 1.0},
                {xPos + wChar, yPos, 1.0, 1.0},
                {xPos, yPos + hChar, 0.0, 0.0},
                {xPos + wChar, yPos, 1.0, 1.0},
                {xPos + wChar, yPos + hChar, 1.0, 0.0}
		};
		glBindTexture(GL_TEXTURE_2D, c.getTexId());
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (c.getAdvance() >> 6) * scale;
        w = x + xPos + wChar;
        h = std::max(h, y + yPos + hChar); // kinda dirty hack
    }
	glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return {static_cast<int>(w), static_cast<int>(h)};
}
