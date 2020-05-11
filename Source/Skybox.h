#include "../Include/Common.h"
#include "../Source/MyShader.h"
#include "../Source/MyObject.h"

namespace Skybox {
	GLuint textureID;

	MyShader* skyboxShader;
	MyObject *skybox;

	std::string fileName[6] = {
		"./Skybox/posx.png",
		"./Skybox/negx.png",
		"./Skybox/posy.png",
		"./Skybox/negy.png",
		"./Skybox/posz.png",
		"./Skybox/negz.png"
	};

	GLenum type[6] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
	};

	float vertices[] = {
		-0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, 0.5, -0.5,
		-0.5, 0.5, -0.5,
		-0.5, -0.5, 0.5,
		0.5, -0.5, 0.5,
		0.5, 0.5, 0.5,
		-0.5, 0.5, 0.5
	};

	int indices[] = {
		// posx
		1, 5, 6,
		6, 2, 1,
		// negx
		4, 0, 3,
		3, 7, 4,
		// posy
		3, 2, 6,
		6, 7, 3,
		// neg y
		4, 5, 1,
		1, 0, 4,
		// posz
		5, 4, 7,
		7, 6, 5,
		// negz
		0, 1, 2,
		2, 3, 0
	};

	void loadTextures()
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		for (int i = 0; i < 6; ++i)
		{
			TextureData texData = Load_png(fileName[i].c_str());
			if (texData.data != nullptr)
			{
				glTexImage2D(type[i], 0, GL_RGBA, texData.width, texData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData.data);
				delete[] texData.data;
			}
			else
			{
				printf("Load texture file error %s\n", fileName[i].c_str());
				return;
			}
		}

		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		// CheckGLError();
	}

	void init() {
		skyboxShader = new MyShader("../Source/SkyboxShader.vs", "../Source/SkyboxShader.fs");
		skybox = new MyObject(skyboxShader, MyObject::DRAW_TYPE_ELEMENT);

		skybox -> init(vertices, indices, sizeof(vertices) / sizeof(float), sizeof(indices)/sizeof(int));

		glEnable(GL_TEXTURE_2D);
		loadTextures();
	}

	void use()
	{
		glEnable(GL_TEXTURE_2D);
		skybox->use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	}

	void draw()
	{
		skybox->draw();
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void setViewProjectMt(glm::mat4x4* viewMt = nullptr, glm::mat4x4* projectMt = nullptr) {
		skybox->setViewProjectMt(viewMt, projectMt);
	}
};