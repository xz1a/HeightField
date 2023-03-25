#include "GLRenderSystem.h"

GLRenderSystem::GLRenderSystem() {
	current_program = nullptr;
	program_map = std::unordered_map<const char*, std::shared_ptr<GLProgram>>();
	current_textures = std::unordered_map<GLenum, std::shared_ptr<GLTexture>>();
	current_buffers = std::unordered_map<GLenum, std::shared_ptr<GLBuffer>>();
}

/*
* Functions for Creating and Using OpenGL Shaders
*/

void GLRenderSystem::BindProgram(const char* p_program) {
	if (p_program != current_program) {
		if (program_map.find(p_program) == program_map.end()) {
			glUseProgram(0);
			std::cout << "Couldn't Find Selected Program." << std::endl;
		}
		else {
			std::shared_ptr<GLProgram> gl_program = program_map.at(p_program);
			glUseProgram(gl_program->GetHandle());
			current_program = p_program;
		}
	}
}

std::shared_ptr<GLProgram> GLRenderSystem::CreateProgram(const char* p_program_name, std::vector<GLShaderParameters>&& p_shaders) {
	program_map.insert(std::pair<const char*, std::shared_ptr<GLProgram>>(p_program_name, std::make_shared<GLProgram>(p_shaders)));
	return program_map.at(p_program_name);
}


//Functions for Setting Uniforms.
void GLRenderSystem::SetProgramUniformInteger(const char* p_program_name, const GLchar* p_uniform, int p_data) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformInteger(p_uniform, p_data);
	}
}

void GLRenderSystem::SetProgramUniformFloat(const char* p_program_name, const GLchar* p_uniform, float p_data) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformFloat(p_uniform, p_data);
	}
}

void GLRenderSystem::SetProgramUniformVec2(const char* p_program_name, const GLchar* p_uniform, const glm::vec2& p_data) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformVec2(p_uniform, p_data);
	}
}

void GLRenderSystem::SetProgramUniformVec3(const char* p_program_name, const GLchar* p_uniform, const glm::vec3& p_data) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformVec3(p_uniform, p_data);
	}
}

void GLRenderSystem::SetProgramUniformVec4(const char* p_program_name, const GLchar* p_uniform, const glm::vec4& p_data) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformVec4(p_uniform, p_data);
	}
}

void GLRenderSystem::SetProgramUniformMat3(const char* p_program_name, const GLchar* p_uniform, const glm::mat3& p_data, GLboolean p_transpose) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformMat3(p_uniform, p_data, p_transpose);
	}

}

void GLRenderSystem::SetProgramUniformMat4(const char* p_program_name, const GLchar* p_uniform, const glm::mat4& p_data, GLboolean p_transpose) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformMat4(p_uniform, p_data, p_transpose);
	}
}

//Functions for OpenGL Buffers.
[[nodiscard]] std::shared_ptr<GLBuffer> GLRenderSystem::CreateBuffer(GLenum p_buffer_type) {
	std::shared_ptr <GLBuffer> buffer = std::make_shared<GLBuffer>(p_buffer_type);
	return buffer;
}

[[nodiscard]] std::shared_ptr<GLBuffer> GLRenderSystem::CreateBuffer(GLenum p_buffer_type, const void* p_data, size_t p_size) {
	std::shared_ptr <GLBuffer> buffer = std::make_shared<GLBuffer>(p_buffer_type, p_data, p_size);
	return buffer;
}

void GLRenderSystem::BindBuffer(std::shared_ptr<GLBuffer> p_buffer) {
	GLenum type = p_buffer.get()->GetType();
	if (current_buffers[type] != p_buffer) {
		glBindBuffer(type, p_buffer.get()->GetHandle());
		current_buffers[type] = p_buffer;
	}
}

//Functions for OpenGL Vertex Arrays.
[[nodiscard]] std::shared_ptr<GLVertexArray> GLRenderSystem::CreateVertexArray() {
	std::shared_ptr<GLVertexArray> vertex_array = std::make_shared<GLVertexArray>();
	return vertex_array;
}

[[nodiscard]] std::shared_ptr<GLVertexArray> GLRenderSystem::CreateVertexArray(const std::vector<LayoutBufferParam> p_buffers) {
	std::shared_ptr<GLVertexArray> vertex_array = std::make_shared<GLVertexArray>(p_buffers);

	return vertex_array;
}

void GLRenderSystem::BindVertexArray(std::shared_ptr<GLVertexArray> p_vertex_array) {
	if (current_vertex_array != p_vertex_array) {
		current_vertex_array = p_vertex_array;
		glBindVertexArray(p_vertex_array.get()->GetHandle());
	}
}

void GLRenderSystem::UnBindVertexArray() {
	glBindVertexArray(0);
	current_vertex_array = NULL;
}

//Functions for OpenGL Textures

[[nodiscard]] std::shared_ptr<GLTexture> GLRenderSystem::CreateTexture(GLenum p_texture_type, std::vector<const char*> p_file_paths) {
	std::shared_ptr<GLTexture> texture = std::make_shared<GLTexture>(p_texture_type, p_file_paths);
	return texture;
}

void GLRenderSystem::BindTexture(std::shared_ptr<GLTexture> p_texture) {
	GLenum type = p_texture.get()->GetType();
	if (current_textures[type] != p_texture) {
		glBindTexture(type, p_texture.get()->GetHandle());
		current_textures[type] = p_texture;
	}
}