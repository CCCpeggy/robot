#ifndef __MY__OBJECT__
#define __MY__OBJECT__
#include "../Include/Common.h"
#include "MyShader.h"

#define INSTANCE 0
#define NORMAL 1

bool loadMTL(const char* path,
	std::vector<glm::vec3>& Kd,
	std::vector<glm::vec3>& Ka,
	std::vector<glm::vec3>& Ks,
	std::vector<std::string>& out_name,
	std::string& texture
)
{
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the .mtl file ! Are you in the right path ? See Tutorial 1 for details\n");
		return false;
	}
	while (1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if (strcmp(lineHeader, "newmtl") == 0) {
			char material[50];
			fscanf(file, "%s", material);
			out_name.push_back(material);
		}
		else if (strcmp(lineHeader, "Kd") == 0) {
			glm::vec3 diffuse;
			fscanf(file, "%f %f %f\n", &diffuse.x, &diffuse.y, &diffuse.z);
			Kd.push_back(diffuse);
		}
		else if (strcmp(lineHeader, "Ka") == 0) {
			glm::vec3 ambient;
			fscanf(file, "%f %f %f\n", &ambient.x, &ambient.y, &ambient.z);
			Ka.push_back(ambient);
		}
		else if (strcmp(lineHeader, "Ks") == 0) {
			glm::vec3 specular;
			fscanf(file, "%f %f %f\n", &specular.x, &specular.y, &specular.z);
			Ks.push_back(specular);
		}
		else if (strcmp(lineHeader, "map_Kd") == 0) {
			fscanf(file, "%s\n", texture);

		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	return true;
}

class MyObject {
protected:
	GLuint vao;
	GLuint offsets_vbo;
	GLuint vertexs_vbo;
	GLuint uvs_vbo;
	GLuint normals_vbo;
	GLuint kas_vbo;
	GLuint kds_vbo;
	std::vector<glm::vec3>	offsets;
	std::vector<glm::vec3>	vertexs;
	std::vector<glm::vec2>	uvs;
	std::vector<glm::vec3>	normals;
	glm::vec3 KDs;
	glm::vec3 KAs;
	glm::vec3 KSs;

public:

	MyShader* shader;

	glm::vec3 rotation;
	glm::vec3 translate;
	glm::vec3 position;
	glm::mat4x4 modelMt;

protected:

	void loadMyObj(char* inputfile) {

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile);

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
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					vertex.x = attrib.vertices[3 * idx.vertex_index + 0];
					vertex.y = attrib.vertices[3 * idx.vertex_index + 1];
					vertex.z = attrib.vertices[3 * idx.vertex_index + 2];
					normal.x = attrib.normals[3 * idx.normal_index + 0];
					normal.y = attrib.normals[3 * idx.normal_index + 1];
					normal.z = attrib.normals[3 * idx.normal_index + 2];
					uv.x = attrib.texcoords[2 * idx.texcoord_index + 0];
					uv.y = attrib.texcoords[2 * idx.texcoord_index + 1];
					// Optional: vertex colors
					// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
					// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
					// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
					//std::cout << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
					vertexs.push_back(vertex);
					uvs.push_back(uv);
					normals.push_back(normal);
				}
				index_offset += fv;

				// per-face material
				shapes[s].mesh.material_ids[f];
			}
		}
	}
	void loadMyMtl(char* inputfile, int index = 0) {
		std::vector<glm::vec3> Kds;
		std::vector<glm::vec3> Kas;
		std::vector<glm::vec3> Kss;
		std::vector<std::string> Materials;//mtl-name
		std::string texture;
		loadMTL(inputfile, Kds, Kas, Kss, Materials, texture);
		//printf("%d\n",texture);
		if (Kds.size() > index) {
			KDs = Kds[index];
		}
		if (Kas.size() > index) {
			KAs = Kas[index];
		}
		if (Kss.size() > index) {
			KSs = Kss[index];
		}
	}

public:
	MyObject(MyShader *shader, int Type = NORMAL): shader(shader)
	{
		if (Type == NORMAL) {
			offsets.push_back(glm::vec3(0, 0, 0));
		}
	}
	void init(char* objFile, char* mtlFIle = nullptr, int index = 0) {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		loadMyObj(objFile);

		glGenBuffers(1, &vertexs_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vertexs_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(float) * 3, &vertexs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glGenBuffers(1, &uvs_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, uvs_vbo);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float) * 2, &uvs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glGenBuffers(1, &normals_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float) * 3, &normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glGenBuffers(1, &offsets_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, offsets_vbo);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glVertexAttribDivisor(3, 1);

		if (mtlFIle) {
			loadMyMtl(mtlFIle, index);
		}
		glBindVertexArray(NULL);
	}

	void use() {
		shader->use();
		if (offsets.size()) {
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, offsets_vbo);
			glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(float) * 3, &offsets[0], GL_DYNAMIC_DRAW);
		}
	}

	glm::mat4x4 getModelMt (glm::mat4x4* modelMt) {
		glm::mat4x4 matrix = glm::mat4x4(1);
		matrix = glm::translate(matrix, glm::vec3(4.0f));
		// TODO: rotation
		return (*modelMt) * matrix;
	}

	void setMt(glm::mat4x4* modelMt, glm::mat4x4* viewMt = nullptr, glm::mat4x4* projectMt = nullptr) {
		this->modelMt = (*modelMt);
		shader->setViewProjectMt(viewMt, projectMt);
	}

	glm::mat4x4 setModelMt(glm::mat4x4* modelMt) {
		glm::mat4x4 matrix = glm::mat4x4(1);
		matrix = glm::translate(matrix, translate);
		matrix = glm::translate(matrix, position);
		// TODO: rotation
		this -> modelMt = (*modelMt) * matrix;
		return matrix;
	}

	void setViewProjectMt(glm::mat4x4* viewMt = nullptr, glm::mat4x4* projectMt = nullptr) {
		shader->setViewProjectMt(viewMt, projectMt);
	}

	void draw() {
		shader->setModelMt(&modelMt);
		shader->setMaterial(KDs, KAs);
		if (offsets.size()) {
			glDrawArraysInstanced(GL_TRIANGLES, 0, size(), offsets.size());
		}
	}

	int size() {
		return vertexs.size();
	}
};
#endif