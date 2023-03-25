#include "GLTexture.h"

GLTexture::GLTexture(GLenum p_texture_type, std::vector<const char*> p_file_paths) {
	texture_type = p_texture_type;
	glGenTextures(1, &handle);
	glBindTexture(p_texture_type, handle);

	int width, height, channels;
	switch (texture_type) {
	case GL_TEXTURE_2D:
		for (int i = 0; i < p_file_paths.size(); ++i) {
			unsigned char* data = stbi_load(p_file_paths[i], &width, &height, &channels, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}
		break;
	case GL_TEXTURE_CUBE_MAP:
		for (int i = 0; i < p_file_paths.size(); ++i) {
			unsigned char* data = stbi_load(p_file_paths[i], &width, &height, &channels, 0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		break;
	}

	glBindTexture(p_texture_type, 0);
}

GLTexture::~GLTexture() {
	glDeleteTextures(1, &handle);
}