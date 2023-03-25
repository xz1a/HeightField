#include "GLProgram.h"

GLProgram::GLProgram(const std::vector<GLShaderParameters>& p_shaders) {
	shaders = std::vector<std::shared_ptr<GLShader>>(p_shaders.size());
	uniform_location_map = std::unordered_map<const GLchar*, GLint>();

	//Create Shader Objects from Parameters.
	for (int i = 0; i < shaders.size(); ++i) {
		shaders[i] = std::make_shared<GLShader>(p_shaders[i].path, p_shaders[i].shader_type);
	}

	//Create Program.
	handle = glCreateProgram();

	//Bind all Shaders to Program.
	for (int i = 0; i < shaders.size(); ++i) {
		shaders[i].get()->CreateAndCompile();
		glAttachShader(handle, shaders[i].get()->GetHandle());
	}

	glLinkProgram(handle);
	int success;
	glGetProgramiv(handle, GL_LINK_STATUS, &success);
	if (!success) {
		std::cout << "<ERROR> PROGRAM LINKING FAILED." << std::endl;
	}
	else {
		std::cout << "<STATUS> PROGRAM LINKING SUCCESS." << std::endl;
	}
}

GLProgram::~GLProgram() {
	glDeleteProgram(handle);
}

//Function Returns Uniform Location from the uniform cache or calls glGetUniform and stores it in the cache.
GLuint GLProgram::GetUniformLocation(const GLchar* p_uniform) {
	if (uniform_location_map.find(p_uniform) == uniform_location_map.end()) {
		GLint location = glGetUniformLocation(handle, p_uniform);
		if (location != -1) {
			uniform_location_map.insert(std::pair<const GLchar*, GLint>(p_uniform, location));
			
		}
		return location;
	} else {
		return uniform_location_map.at(p_uniform);
	}
}


//Uniform Usage Functions.
void GLProgram::SetUniformInteger(const GLchar* p_uniform, int p_data) {
	GLint uniform_location = GetUniformLocation(p_uniform);
	glProgramUniform1i(handle, uniform_location, p_data);
}

void GLProgram::SetUniformFloat(const GLchar* p_uniform, float p_data) {
	GLint uniform_location = GetUniformLocation(p_uniform);
	glProgramUniform1f(handle, uniform_location, p_data);
}

void GLProgram::SetUniformVec2(const GLchar* p_uniform, const glm::vec2& p_data) {
	GLint uniform_location = GetUniformLocation(p_uniform);
	glProgramUniform2fv(handle, uniform_location, 1, glm::value_ptr(p_data));
}

void GLProgram::SetUniformVec3(const GLchar* p_uniform, const glm::vec3& p_data) {
	GLint uniform_location = GetUniformLocation(p_uniform);
	glProgramUniform3fv(handle, uniform_location, 1, glm::value_ptr(p_data));
}

void GLProgram::SetUniformVec4(const GLchar* p_uniform, const glm::vec4& p_data) {
	GLint uniform_location = GetUniformLocation(p_uniform);
	glProgramUniform4fv(handle, uniform_location, 1, glm::value_ptr(p_data));
}

void GLProgram::SetUniformMat3(const GLchar* p_uniform, const glm::mat3& p_data, GLboolean p_transpose) {
	GLint uniform_location = GetUniformLocation(p_uniform);
	glProgramUniformMatrix3fv(handle, uniform_location, 1, p_transpose, glm::value_ptr(p_data));
}

void GLProgram::SetUniformMat4(const GLchar* p_uniform, const glm::mat4& p_data, GLboolean p_transpose) {
	GLint uniform_location = GetUniformLocation(p_uniform);
	glProgramUniformMatrix4fv(handle, uniform_location, 1, p_transpose, glm::value_ptr(p_data));
}