#include "GLBufferLayout.h"

GLBufferLayout::GLBufferLayout(const std::vector<GLBufferLayoutElement>& p_elements) {
	elements = p_elements;
	stride = 0;
	for (int i = 0; i < elements.size(); ++i) {
		stride += elements[i].size * sizeof(elements[i].type);
	}
}

GLBufferLayout::GLBufferLayout(const std::vector<GLBufferLayoutElement>& p_elements, size_t p_stride) {
	elements = p_elements;
	stride = p_stride;
}