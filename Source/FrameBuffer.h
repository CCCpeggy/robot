#ifndef __MY__FRAMEBUFFER__
#define __MY__FRAMEBUFFER__
#include "../Include/Common.h"
#include "../Source/MyShader.h"

class FrameBuffer {
public:
	MyShader* grayShader;

	GLuint window_vao;
	GLuint window_buffer;
	GLuint FBO;
	GLuint depthRBO;
	GLuint FBODataTexture;
	static const int SHADER_MODE_NORMAL;
	static const int SHADER_MODE_GRAY;
	static const int SHADER_MODE_PIXEL;
	static const int SHADER_MODE_KERNEL;
	static const int SHADER_MODE_GUSSIAN_BLUR;
	static const int SHADER_MODE_ANDROID_8;
	static const int SHADER_MODE_ANDROID;

	int mode;
	int mode2;
	float scale;
	static const GLfloat window_positions[16];
	FrameBuffer():mode(SHADER_MODE_NORMAL),
		mode2(-1),
		scale(1)
	{
	}
	void init()
	{
		grayShader = new MyShader("../Source/ColorShader.vs", "../Source/ColorShader.fs");

		glGenVertexArrays(1, &window_vao);
		glBindVertexArray(window_vao);

		glGenBuffers(1, &window_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, window_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(window_positions), window_positions, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 4, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 4, (const GLvoid*)(sizeof(GL_FLOAT) * 2));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glGenFramebuffers(1, &FBO);

		updateMode2();
		setScale(true, 0);
	}

	void reshape(int width, int height)
	{
		glDeleteRenderbuffers(1, &depthRBO);
		glDeleteTextures(1, &FBODataTexture);
		glGenRenderbuffers(1, &depthRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);

		glGenTextures(1, &FBODataTexture);
		glBindTexture(GL_TEXTURE_2D, FBODataTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBODataTexture, 0);
	}

	void use() {
		if (FBO > 0) {
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}

	void draw()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, FBODataTexture);
		glBindVertexArray(window_vao);
		grayShader->use();
		grayShader->setMode(mode);
		grayShader->setTime(clock());
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}

	void switchMode(int newMode) {
		mode = newMode;
	}

	void updateMode2() {
		grayShader->use();
		mode2++;
		mode2 %= 5;
		grayShader->setMode2(mode2 + 1);
	}

	void setScale(bool mode, float rate) {
		scale += scale * (mode ? -rate : rate);
		grayShader->use();
		grayShader->setScale(scale);
	}

};

const int FrameBuffer::SHADER_MODE_NORMAL = 0;
const int FrameBuffer::SHADER_MODE_GRAY = 1;
const int FrameBuffer::SHADER_MODE_PIXEL = 2;
const int FrameBuffer::SHADER_MODE_KERNEL = 3;
const int FrameBuffer::SHADER_MODE_GUSSIAN_BLUR = 4;
const int FrameBuffer::SHADER_MODE_ANDROID_8 = 5;
const int FrameBuffer::SHADER_MODE_ANDROID = 6;

const GLfloat FrameBuffer::window_positions[] =
{
	1.0f,-1.0f,1.0f,0.0f,
	-1.0f,-1.0f,0.0f,0.0f,
	-1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,1.0f,1.0f
};
#endif