#ifndef CANDYTUFT_SHADER_HPP
#define CANDYTUFT_SHADER_HPP

#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"

class Shader {
private:
	unsigned int id;
public:
	Shader(const std::string& vsh, const std::string& fsh);
	void use() const;
	void setBool(const std::string& loc, bool val) const;
	void setInt(const std::string& loc, int val) const;
	void setFloat(const std::string& loc, float val) const;
	void setVec3f(const std::string& loc, glm::vec3 val) const;
	void setVec4f(const std::string& loc, glm::vec4 val) const;
	void setMat4f(const std::string& loc, glm::mat4 val) const;
};


#endif //CANDYTUFT_SHADER_HPP
