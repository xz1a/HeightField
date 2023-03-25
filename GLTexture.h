#ifndef _GL_TEXTURE_H_
#define _GL_TEXTURE_H_
#include <GL/gl3w.h>
#include <vector>
#include "stbi.h"

class GLTexture {
public:
	GLTexture(GLenum p_texture_type, std::vector<const char*> p_file_paths);
	~GLTexture();
	inline GLenum GetType() const { return texture_type; };
	inline GLuint GetHandle() const { return handle; };
protected:
private:
	GLuint handle;
	GLenum texture_type;
};
#endif