#ifndef __MY__TEXTURE__
#define __MY__TEXTURE__
#include "../Include/Common.h"
#include "MyObject.h"

class MyTexture: public MyObject {
protected:
	float vertexs[8];

public:

private:
	std::string texturePath;
	GLuint textureID;
public:
	MyTexture(MyShader *shader, const char* texturePath, float width = 1, float height = 1):
		MyObject(shader), texturePath(texturePath),
		vertexs {
			-width, height, 
			width, height,
			-width, -height, 
			width, -height, 
		}
	{
		
	}
	void init() {
		loadTextures(textureID, texturePath.c_str());
		MyObject::init();

		glGenBuffers(1, &vertexs_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vertexs_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindVertexArray(NULL);
	}

	void use() {
		MyObject::use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void draw() {
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(NULL);
	}

	void drawInstance() {
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, offsets.size());
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(NULL);
	}

	void setPos(glm::vec2 pos) {
		shader->use();
		shader->setPos(pos);
	}

	void setPos(float posX, float posY) {
		shader->use();
		shader->setPos(glm::vec2(posX, posY));
	}

};


#endif