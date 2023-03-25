#include <stdlib.h>
#include <iostream>
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include "GLRenderSystem.h"
#include "SimpleObjLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stbi.h"

const int resolution = 500;
const int last_index = resolution - 1;

//Helper Functions
int clamp_index(int x) {
	if (x < 0) {
		return 0;
	}
	else if (x > last_index) {
		return last_index;
	}
	return x;
}

float clamp_velocity(float x, float y) {
	if (x > y) {
		return y;
	}
	else if (x < -y) {
		return -y;
	}
	return x;
}

float min(double x, double y) {
	return (x < y) ? x : y;
}


int main(int argc, char* argv[]) {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "Height Field", NULL, NULL);
	glfwMakeContextCurrent(window);
	gl3wInit();

	float **u = (float**)malloc(sizeof(float*) * resolution);
	float **v = (float**)malloc(sizeof(float*) * resolution);
	const float c = 2.0f;
	const float h = 0.1f;
	const float c2 = c * c;
	const float h2 = h * h;
	const float k = 0.5f;

	GLRenderSystem render_system = GLRenderSystem();

	for (int i = 0; i < resolution; ++i) {
		u[i] = (float*)malloc(sizeof(float) * resolution);
		v[i] = (float*)malloc(sizeof(float) * resolution);

		for (int j = 0; j < resolution; ++j) {
			u[i][j] = 0.0f;
			v[i][j] = 0.0f;
		}
	}

	std::vector<unsigned int> indices = std::vector<unsigned int>();

	for (int i = 0; i < resolution-1; ++i) {
		for (int j = 0; j < resolution - 1; ++j) {
			indices.push_back((i * resolution) + (j));
			indices.push_back(((i + 1) * resolution) + (j));
			indices.push_back((i * resolution) + (j + 1));

			indices.push_back(((i + 1) * resolution) + (j));
			indices.push_back(((i + 1) * resolution) + (j + 1));
			indices.push_back((i * resolution) + (j + 1));
		}
	}

	std::vector<glm::vec3> vertices;
	for (int i = 0; i < resolution; ++i) {
		for (int j = 0; j < resolution; ++j) {
			glm::vec3 v = glm::vec3((i - (resolution / 2)) * h, u[i][j], j * h);
			vertices.push_back(v);
		}
	}

	std::shared_ptr<GLProgram> program = render_system.CreateProgram(
		"water", {
		{"./shaders/reflect/reflect.vertex", GL_VERTEX_SHADER},
		{"./shaders/face_normal/face_normal.geometry", GL_GEOMETRY_SHADER},
		{"./shaders/reflect/reflect.fragment", GL_FRAGMENT_SHADER},
	});


	GLBufferLayout layout = GLBufferLayout({
		{3, GL_FLOAT, false, NULL},
	});
	std::shared_ptr<GLBuffer> vbo = render_system.CreateBuffer(GL_ARRAY_BUFFER, vertices.data(), vertices.size() * sizeof(glm::vec3));
	std::shared_ptr<GLBuffer> ibo = render_system.CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, indices.data(), indices.size() * sizeof(unsigned int));
	std::shared_ptr<GLVertexArray> vao = render_system.CreateVertexArray({ {layout, vbo}, {GLBufferLayout({}), ibo} });


	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 30.0f, 90.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	program.get()->SetUniformMat4("projection_matrix", projection, false);
	program.get()->SetUniformMat4("model_view_matrix", view, false);

	std::vector<glm::vec3> cube_vertices;
	SimpleObjLoader::LoadObj("./meshes/cube.obj", cube_vertices);
	std::shared_ptr<GLBuffer> cube_vbo = render_system.CreateBuffer(GL_ARRAY_BUFFER, cube_vertices.data(), cube_vertices.size() * sizeof(glm::vec3));
	GLBufferLayout simple_layout = GLBufferLayout({
		GLBufferLayoutElement {3, GL_FLOAT, false, NULL},
	});
	std::shared_ptr<GLVertexArray> cube_vao = render_system.CreateVertexArray({ {simple_layout, cube_vbo} });
	std::shared_ptr<GLTexture> cube_map = render_system.CreateTexture(GL_TEXTURE_CUBE_MAP, { "./skybox/right.png", "./skybox/left.png", "./skybox/top.png", "./skybox/bottom.png", "./skybox/front.png", "./skybox/back.png" });
	render_system.BindTexture(cube_map);

	std::shared_ptr<GLProgram> skybox_program = render_system.CreateProgram("skybox", {
		{"./shaders/skybox/skybox.vertex", GL_VERTEX_SHADER},
		{"./shaders/skybox/skybox.fragment", GL_FRAGMENT_SHADER}
	});

	skybox_program.get()->SetUniformMat4("view_projection_matrix", projection * glm::mat4(glm::mat3(view)), false);

	float delta_time = 0;
	float last_frame = 0;
	float timer = 0;
	
	render_system.Enable(GL_DEPTH_TEST);
	render_system.Enable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	render_system.Disable(GL_CULL_FACE);
	

	while (!glfwWindowShouldClose(window)) {
		float current_frame = static_cast<float>(glfwGetTime());
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		timer += delta_time;

		//Add Forces to the grid (rain drops)
		if (timer >= 0.25f) {
			int x = ((double)rand() / (RAND_MAX)) * resolution;
			int y = ((double)rand() / (RAND_MAX)) * resolution;
			v[y][x] = -1.0f;
			timer = 0.0;
		}

		//Update Start
		for (int i = 0; i < resolution; ++i) {
			for (int j = 0; j < resolution; ++j) {				
				float force = c2 * (u[clamp_index(i+1)][j] + u[clamp_index(i-1)][j] + u[i][clamp_index(j+1)] + u[i][clamp_index(j-1)] - (4 * u[i][j])) / h2;
				float damping_force = -k * force;
				v[i][j] += (force + damping_force) * delta_time;
				v[i][j] *= 0.99f;
				v[i][j] = clamp_velocity(v[i][j], 5.0);
			}
		}

		for (int i = 0; i < resolution; ++i) {
			for (int j = 0; j < resolution; ++j) {
				u[i][j] += v[i][j] * delta_time;
				vertices[(i * resolution) + j].y = u[i][j];
			}
		}
		//Update End

		//render mesh
		render_system.Clear();
		render_system.SetPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		vbo.get()->UpdateData(vertices.data());
		render_system.BindProgram("water");
		render_system.BindVertexArray(vao);
		render_system.DrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

		///skybox rendering
		render_system.SetPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		render_system.BindProgram("skybox");
		render_system.SetDepthFunction(GL_LEQUAL);
		render_system.BindVertexArray(cube_vao);
		render_system.Draw(GL_TRIANGLES, 0, cube_vertices.size());
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	free(u);
	free(v);
	return 0;
}