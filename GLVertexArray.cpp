#include "GLVertexArray.h"

GLVertexArray::GLVertexArray() {
	glGenVertexArrays(1, &handle);
}

GLVertexArray::GLVertexArray(const std::vector<LayoutBufferParam> p_buffers) {
	glGenVertexArrays(1, &handle);
	glBindVertexArray(handle);
	for (int i = 0; i < p_buffers.size(); ++i) {
		const LayoutBufferParam& param = p_buffers[i];
		glBindBuffer(param.buffer.get()->GetType(), param.buffer.get()->GetHandle());
		const std::vector<GLBufferLayoutElement>& elements = param.layout.GetElements();
		size_t offset = 0;
		int last_offset = 0;
		for (int i = 0; i < elements.size(); ++i) {
			glEnableVertexAttribArray(i);
			offset += (i == 0) ? 0 : last_offset;
			glVertexAttribPointer(i, elements[i].size, elements[i].type, elements[i].normalized, param.layout.GetStride(), (void*)offset);
			last_offset = elements[i].size * sizeof(elements[i].type);
		}
	}
	glBindVertexArray(0);
}

GLVertexArray::~GLVertexArray() {
	glDeleteVertexArrays(1, &handle);
}