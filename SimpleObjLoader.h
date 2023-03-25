#ifndef _SIMPLE_OBJ_LOADER_H_
#define _SIMPLE_OBJ_LOADER_H_
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

typedef struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec4 color;
} Vertex;

namespace SimpleObjLoader {
	static void LoadObj(const char* file_path, std::vector<glm::vec3>& output_vertices) {
		std::fstream file(file_path);
		std::string line;
		std::vector<unsigned int> vertex_indices, normal_indices, uv_indices;
		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec3> temp_normals;
		std::vector<glm::vec2> temp_uvs;
		while (std::getline(file, line)) {
			std::string header = line.substr(0, 2);
			if (header == "v ") {
				std::istringstream iss(line.substr(2));
				float x, y, z;
				iss >> x >> y >> z;
				temp_vertices.push_back(glm::vec3(x, y, z));
			}
			else if (header == "vn") {
				std::istringstream iss(line.substr(2));
				float x, y, z;
				iss >> x >> y >> z;
				temp_normals.push_back(glm::vec3(x, y, z));
			}
			else if (header == "vt") {
				std::istringstream iss(line.substr(2));
				float x, y;
				iss >> x >> y;
				temp_uvs.push_back(glm::vec2(x, y));
			}
			else if (header == "f ") {
				std::istringstream iss(line.substr(2));
				unsigned int indices[9];
				char blank;
				iss >> indices[0] >> blank >> indices[1] >> blank >> indices[2] >> indices[3] >> blank >> indices[4] >> blank >> indices[5] >> indices[6] >> blank >> indices[7] >> blank >> indices[8];

				vertex_indices.push_back(indices[0]);
				vertex_indices.push_back(indices[3]);
				vertex_indices.push_back(indices[6]);

				normal_indices.push_back(indices[1]);
				normal_indices.push_back(indices[4]);
				normal_indices.push_back(indices[7]);

				uv_indices.push_back(indices[2]);
				uv_indices.push_back(indices[5]);
				uv_indices.push_back(indices[8]);
			}
		}

		for (int i = 0; i < vertex_indices.size(); ++i) {
			output_vertices.push_back(temp_vertices[vertex_indices[i]-1]);
		}
	}

	static void LoadObj(const char* file_path, std::vector<Vertex>& output_vertices) {
		std::fstream file(file_path);
		std::string line;
		std::vector<unsigned int> vertex_indices, normal_indices, uv_indices;
		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec3> temp_normals;
		std::vector<glm::vec2> temp_uvs;
		while (std::getline(file, line)) {
			std::string header = line.substr(0, 2);
			if (header == "v ") {
				std::istringstream iss(line.substr(2));
				float x, y, z;
				iss >> x >> y >> z;
				temp_vertices.push_back(glm::vec3(x, y, z));
			}
			else if (header == "vn") {
				std::istringstream iss(line.substr(2));
				float x, y, z;
				iss >> x >> y >> z;
				temp_normals.push_back(glm::vec3(x, y, z));
			}
			else if (header == "vt") {
				std::istringstream iss(line.substr(2));
				float x, y;
				iss >> x >> y;
				temp_uvs.push_back(glm::vec2(x, y));
			}
			else if (header == "f ") {
				std::istringstream iss(line.substr(2));
				unsigned int indices[9];
				char blank;
				iss >> indices[0] >> blank >> indices[1] >> blank >> indices[2] >> indices[3] >> blank >> indices[4] >> blank >> indices[5] >> indices[6] >> blank >> indices[7] >> blank >> indices[8];

				vertex_indices.push_back(indices[0]);
				vertex_indices.push_back(indices[3]);
				vertex_indices.push_back(indices[6]);

				uv_indices.push_back(indices[1]);
				uv_indices.push_back(indices[4]);
				uv_indices.push_back(indices[7]);

				normal_indices.push_back(indices[2]);
				normal_indices.push_back(indices[5]);
				normal_indices.push_back(indices[8]);
			}
		}

		for (int i = 0; i < vertex_indices.size(); ++i) {
			Vertex vertex{
				temp_vertices[vertex_indices[i] - 1],
				temp_normals[normal_indices[i] - 1],
				temp_uvs[uv_indices[i] - 1]
			};
			output_vertices.push_back(vertex);
		}
	}
};
#endif