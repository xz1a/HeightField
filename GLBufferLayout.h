#ifndef _GL_BUFFER_LAYOUT_H_
#define _GL_BUFFER_LAYOUT_H_
#include <GL/gl3w.h>
#include <vector>
#include <iostream>

typedef struct GLBufferLayoutElement {
	GLint size;
	GLenum type;
	GLboolean normalized;
	const void* pointer;
} GLBufferLayoutElement;

class GLBufferLayout {
public:
	GLBufferLayout(const std::vector<GLBufferLayoutElement>& p_elements);
	GLBufferLayout(const std::vector<GLBufferLayoutElement>& p_elements, size_t p_stride);
	inline const std::vector<GLBufferLayoutElement>& GetElements() const { return elements; };
	inline GLsizei GetStride() const { return stride; }
protected:
private:
	std::vector<GLBufferLayoutElement> elements;
	GLsizei stride;
};
#endif