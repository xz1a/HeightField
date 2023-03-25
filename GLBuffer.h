#ifndef _GL_BUFFER_H_
#define _GL_BUFFER_H_
#include <GL/gl3w.h>
#include <iostream>

class GLBuffer {
public:
	GLBuffer(GLenum p_buffer_type);
	GLBuffer(GLenum p_buffer_type, const void* p_data, size_t p_size);
	~GLBuffer();
	void UpdateData(const void* p_data);
	inline GLenum GetType() const { return buffer_type; };
	inline GLuint GetHandle() const { return handle; };
protected:
private:
	GLuint handle;
	GLenum buffer_type;
	size_t data_size;
};
#endif