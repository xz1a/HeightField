#ifndef _GL_VERTEX_ARRAY_H_
#define _GL_VERTEX_ARRAY_H_
#include <GL/gl3w.h>
#include "GLBuffer.h"
#include "GLBufferLayout.h"

typedef struct LayoutBufferParam {
	GLBufferLayout layout;
	std::shared_ptr<GLBuffer> buffer;
};

class GLVertexArray {	
public:
	GLVertexArray();
	GLVertexArray(const std::vector<LayoutBufferParam> p_buffers);
	~GLVertexArray();
	inline GLuint GetHandle() const{ return handle; }
protected:
private:
	GLuint handle;
	std::shared_ptr<GLBuffer> buffer_array;
};
#endif