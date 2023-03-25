#ifndef _GL_PROGRAM_H_
#define _GL_PROGRAM_H_
#include <GL/gl3w.h>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "GLShader.h"
#include <memory>

class GLProgram {
public:
	GLProgram(const std::vector<GLShaderParameters>& p_shaders);
	~GLProgram();

	//Uniform Usage Functions.
	void SetUniformInteger(const GLchar* p_uniform, int p_data);
	void SetUniformFloat(const GLchar* p_uniform, float p_data);
	void SetUniformVec2(const GLchar* p_uniform, const glm::vec2& p_data);
	void SetUniformVec3(const GLchar* p_uniform, const glm::vec3& p_data);
	void SetUniformVec4(const GLchar* p_uniform, const glm::vec4& p_data);
	void SetUniformMat3(const GLchar* p_uniform, const glm::mat3& p_data, GLboolean p_transpose);
	void SetUniformMat4(const GLchar* p_uniform, const glm::mat4& p_data, GLboolean p_transpose);

	inline GLuint GetHandle() const { return handle; }
protected:
	GLuint GetUniformLocation(const GLchar* uniform);
private:
	GLuint handle;
	std::vector<std::shared_ptr<GLShader>> shaders;
	std::unordered_map<const GLchar*, GLint> uniform_location_map;
};
#endif