#include "GLBuffer.h"

GLBuffer::GLBuffer(GLenum p_buffer_type) {
	buffer_type = p_buffer_type;
	glGenBuffers(1, &handle);
	data_size = 0;
}

GLBuffer::GLBuffer(GLenum p_buffer_type, const void* p_data, size_t p_size) {
	buffer_type = p_buffer_type;
	glCreateBuffers(1, &handle);
	glNamedBufferData(handle, p_size, p_data, GL_STATIC_DRAW);
	data_size = p_size;
}

GLBuffer::~GLBuffer() {
	glDeleteBuffers(1, &handle);
}

void GLBuffer::UpdateData(const void* p_data) {
	glNamedBufferSubData(handle, 0, data_size, p_data);
}