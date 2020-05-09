#ifndef __MY__SHADER__
#define __MY__SHADER__
#include "../Include/Common.h"

class MyShader {
protected:
	GLuint vs;
	GLuint fs;
	GLuint program;
	GLuint locModel;
	GLuint locView;
	GLuint locProject;
	GLuint locKd;
	GLuint locKa;

public:
	MyShader(std::string vsPath = nullptr, std::string fsPath = nullptr) {
		program = glCreateProgram();
		if (!vsPath.empty()) {
			vs = glCreateShader(GL_VERTEX_SHADER);
			std::string vsSource = readFromFile(vsPath.c_str());
			const char* vsPointer = vsSource.c_str();
			glShaderSource(vs, 1, &vsPointer, NULL);
			glCompileShader(vs);
			glAttachShader(program, vs);
		}
		if (!fsPath.empty()) {
			fs = glCreateShader(GL_FRAGMENT_SHADER);
			std::string fsSource = readFromFile(fsPath.c_str());
			const char* fsPointer = fsSource.c_str();
			glShaderSource(fs, 1, &fsPointer, NULL);
			glCompileShader(fs);
			glAttachShader(program, fs);
		}
		glLinkProgram(program);

		glUseProgram(program);
		locModel = glGetUniformLocation(program, "Model");
		locView = glGetUniformLocation(program, "View");
		locProject = glGetUniformLocation(program, "Projection");
		locKd = glGetUniformLocation(program, "Kd");
		locKa = glGetUniformLocation(program, "Ka");
		glUseProgram(NULL);
	}

	void setViewProjectMt(glm::mat4x4* viewMt, glm::mat4x4* projectMt) {
		glUniformMatrix4fv(locView, 1, GL_FALSE, &(*viewMt)[0][0]);
		glUniformMatrix4fv(locProject, 1, GL_FALSE, &(*projectMt)[0][0]);
	}

	void setModelMt(glm::mat4x4 *modelMt) {
		glUniformMatrix4fv(locModel, 1, GL_FALSE, &(*modelMt)[0][0]);
	}

	void setMaterial(glm::vec3 kd, glm::vec3 ka) {
		glUniform3fv(locKd, 1, &kd[0]);
		glUniform3fv(locKa, 1, &ka[0]);
	}

	void use() {
		glUseProgram(program);
	}
private:
	std::string readFromFile(const GLchar* pathToFile)
	{
		std::string content = "";
		std::ifstream fileStream(pathToFile, std::ios::in);

		if (!fileStream.is_open()) {
			std::cerr << "Could not read file " << pathToFile << ". File does not exist." << std::endl;
			return "";
		}

		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			content.append(line + "\n");
		}
		// std::cout << content << std::endl;
		fileStream.close();
		return content;
	}
};
#endif