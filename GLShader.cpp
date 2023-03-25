#include "GLShader.h"

GLShader::GLShader(const char* p_path, GLenum p_shader_type) {
	path = p_path;
	shader_type = p_shader_type;
	handle = glCreateShader(shader_type);
}

GLShader::~GLShader() {
	glDeleteShader(handle);
}

void GLShader::CreateAndCompile() const {
	std::ifstream file;
	file.open(path);
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::stringstream source_string_stream;
	source_string_stream << file.rdbuf();
	std::string source_string = source_string_stream.str();
	const GLchar* source[] = { source_string.c_str() };

	glShaderSource(handle, 1, source, NULL);
	glCompileShader(handle);

	int success;
	char infoLog[512];
	glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(handle, 512, NULL, infoLog);
		std::cout << "<ERROR> SHADER COMPILATION FAILED" << " " << infoLog << std::endl;
	} 
	else {
		std::cout << "<STATUS> SHADER COMPILATION SUCCESS" << std::endl;
	}
	
	file.close();
}