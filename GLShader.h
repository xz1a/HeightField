#ifndef _GL_SHADER_H_
#define _GL_SHADER_H_
#include <GL/gl3w.h>
#include <fstream>
#include <sstream>
#include <iostream>

//Struct for Initialization Parameters.
typedef struct GLShaderParameters{
	const char* path;
	GLenum shader_type;
} ShaderParameters;

class GLShader {
public:
	friend class GLProgram;
	GLShader(const char* p_path, GLenum p_shader_type);
	~GLShader();
	inline  GLuint GetHandle() const { return handle; }
	void CreateAndCompile() const;
protected:
private:
	GLuint handle;
	const char* path;
	GLenum shader_type;
};
#endif