#ifndef __MY__OBJECT__
#define __MY__OBJECT__
#include "../Include/Common.h"
#include "MyShader.h"

#define PI 3.14159265358979f
#define DOR(angle) ((angle) * PI / 180)

class MyObject {
protected:
	GLuint vao;
	GLuint offsets_vbo;
	GLuint vertexs_vbo;
	GLuint uvs_vbo;
	GLuint normals_vbo;
	GLuint kds_vbo;
	GLuint ebo;
	std::vector<glm::vec3>	offsets;
	std::vector<glm::vec3>	vertexs;
	std::vector<glm::vec2>	uvs;
	std::vector<glm::vec3>	normals;
	std::vector<std::string> mtls;
	std::vector<unsigned int> faces;
	std::vector<glm::vec3>	KDs;
	int indicesSize;
	int drawType;
	std::map<GLuint, GLenum> buffer;

public:
	static const int DRAW_TYPE_INSTANCE;
	static const int DRAW_TYPE_NORMAL;
	static const int DRAW_TYPE_ELEMENT;
	MyShader* shader;

	glm::mat4x4 modelMt;

private:

	void loadMyObj(char* objFIle, char* mtlFile) {

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objFIle, mtlFile);

		if (!warn.empty()) {
			std::cout << warn << std::endl;
		}

		if (!err.empty()) {
			std::cerr << err << std::endl;
		}

		if (!ret) {
			exit(1);
		}

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					glm::vec3 vertex;
					glm::vec2 uv;
					glm::vec3 normal;
					glm::vec3 kd;
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					vertex.x = attrib.vertices[3 * idx.vertex_index + 0];
					vertex.y = attrib.vertices[3 * idx.vertex_index + 1];
					vertex.z = attrib.vertices[3 * idx.vertex_index + 2];
					normal.x = attrib.normals[3 * idx.normal_index + 0];
					normal.y = attrib.normals[3 * idx.normal_index + 1];
					normal.z = attrib.normals[3 * idx.normal_index + 2];
					uv.x = attrib.texcoords[2 * idx.texcoord_index + 0];
					uv.y = attrib.texcoords[2 * idx.texcoord_index + 1];
					kd.x = materials[shapes[s].mesh.material_ids[f]].diffuse[0];
					kd.y = materials[shapes[s].mesh.material_ids[f]].diffuse[1];
					kd.z = materials[shapes[s].mesh.material_ids[f]].diffuse[2];
					vertexs.push_back(vertex);
					uvs.push_back(uv);
					normals.push_back(normal);
					KDs.push_back(kd);
				}
				index_offset += fv;
			}
		}
	}

public:
	MyObject(MyShader *shader, int type = DRAW_TYPE_NORMAL): 
		shader(shader),
		drawType(type)
	{
		glGenVertexArrays(1, &vao);
		// glBindVertexArray(vao);
	}
	void init(char* objFile, char* mtlFIle = nullptr, int index = 0) {
		glBindVertexArray(vao);
		loadMyObj(objFile, mtlFIle);
		if (drawType != DRAW_TYPE_NORMAL) {
			offsets.push_back(glm::vec3(0, 0, 0));
		}
		glGenBuffers(1, &vertexs_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vertexs_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(float) * 3, &vertexs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		buffer[vertexs_vbo] = GL_ARRAY_BUFFER;

		glGenBuffers(1, &uvs_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, uvs_vbo);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float) * 2, &uvs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		buffer[uvs_vbo] = GL_ARRAY_BUFFER;

		glGenBuffers(1, &normals_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float) * 3, &normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		buffer[normals_vbo] = GL_ARRAY_BUFFER;

		glGenBuffers(1, &kds_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, kds_vbo);
		glBufferData(GL_ARRAY_BUFFER, KDs.size() * sizeof(float) * 3, &KDs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		buffer[kds_vbo] = GL_ARRAY_BUFFER;

		glGenBuffers(1, &offsets_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, offsets_vbo);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glVertexAttribDivisor(3, 1);
		if (drawType == DRAW_TYPE_NORMAL) {
			glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(float) * 3, &offsets[0], GL_STATIC_DRAW);
		}
		buffer[offsets_vbo] = GL_ARRAY_BUFFER;

		glBindVertexArray(NULL);
	}

	void init(float* vertices, int* indices, int verticesSize, int indicesSize) {
		glBindVertexArray(vao);

		glGenBuffers(1, &vertexs_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vertexs_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesSize, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		buffer[vertexs_vbo] = GL_ARRAY_BUFFER;

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indicesSize, indices, GL_STATIC_DRAW);
		buffer[ebo] = GL_ELEMENT_ARRAY_BUFFER;

		glBindVertexArray(0);
		this->indicesSize = indicesSize;
	}

	void use() {
		shader->use();
		glBindVertexArray(vao);
		for (auto buf : buffer) {
			glBindBuffer(buf.second, buf.first);
		}
	}

	void setMt(glm::mat4x4* modelMt, glm::mat4x4* viewMt = nullptr, glm::mat4x4* projectMt = nullptr) {
		this->modelMt = (*modelMt);
		shader->setViewProjectMt(viewMt, projectMt);
	}

	glm::mat4x4 setModelMt(glm::mat4x4* modelMt) {
		glm::mat4x4 matrix = glm::mat4x4(1);
		this -> modelMt = matrix * (*modelMt);
		return this->modelMt;
	}

	void setViewProjectMt(glm::mat4x4* viewMt = nullptr, glm::mat4x4* projectMt = nullptr) {
		shader->setViewProjectMt(viewMt, projectMt);
	}

	void draw() {
		shader->setModelMt(&(modelMt));
		
		if (drawType == DRAW_TYPE_NORMAL) {
			glDrawArrays(GL_TRIANGLES, 0, size());
		}
		else if (drawType == DRAW_TYPE_INSTANCE && offsets.size()) {
			glDrawArraysInstanced(GL_TRIANGLES, 0, size(), offsets.size());
		}
		else if (drawType == DRAW_TYPE_ELEMENT) {
			glDrawElements(GL_TRIANGLES, this->indicesSize, GL_UNSIGNED_INT, 0);
		}
	}

	int size() {
		return vertexs.size();
	}

	void addOffset(glm::vec3 offset) {
		offsets.push_back(offset);

		if (drawType == DRAW_TYPE_INSTANCE) {
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, offsets_vbo);
			glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(float) * 3, &offsets[0], GL_STATIC_DRAW);
		}
	}

	void setDrawType(int drawType) {
		this->drawType = drawType;
	}
};

const int MyObject::DRAW_TYPE_INSTANCE = 0;
const int MyObject::DRAW_TYPE_NORMAL = 1;
const int MyObject::DRAW_TYPE_ELEMENT = 2;

#endif