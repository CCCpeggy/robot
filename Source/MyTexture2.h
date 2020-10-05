#ifndef __MY__TEXTURE2__
#define __MY__TEXTURE2__
#include "../Include/Common.h"
#include "MyObject.h"

class MyTexture2: public MyObject {
protected:
	float vertexs[8];

public:

private:
	std::string texturePath1;
	std::string texturePath2;
	GLuint textureID1, textureID2;
public:
	MyTexture2(MyShader *shader, const char* texturePath1, const char* texturePath2, float width = 1, float height = 1):
		MyObject(shader), texturePath1(texturePath1), texturePath2(texturePath2),
		vertexs {
			-width, height, 
			width, height,
			-width, -height, 
			width, -height, 
		}
	{
		
	}
	void init() {
		loadTextures(textureID1, texturePath1.c_str());
		loadTextures(textureID2, texturePath2.c_str());
		MyObject::init();

		glGenBuffers(1, &vertexs_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vertexs_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindVertexArray(NULL);

		shader->use();
		shader->setTex(0);
		shader->setTex(1);
	}

	void use() {
		MyObject::use();
		shader->activeTexture(0, textureID1);
		shader->activeTexture(1, textureID2);
	}

	void draw() {
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		shader->activeTexture(0, 0);
		shader->activeTexture(1, 0);
		glBindVertexArray(NULL);
	}

	void drawInstance() {
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, offsets.size());
		shader->activeTexture(0, 0);
		shader->activeTexture(1, 0);
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