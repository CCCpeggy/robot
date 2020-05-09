﻿#include "../Include/Common.h"
#include "../Source/Robot.h"
#include "../Source/MyShader.h"
#include <conio.h>

#define SIZE_1		1
#define SIZE_2		2
#define MENU_EXIT   3

float					aspect;			
float					backgroundGray = 1.0f;
float					teapot_size = 1.0f;

std::vector<glm::mat4x4> stackMat;

glm::mat4x4 modelMt;
glm::mat4x4 viewMt;
glm::mat4x4 projectMt;

Robot *robot;
MyShader *robotShader;

// 渲染事件, 用來在場景上繪製東西

void My_Init() {
	glewInit();

	robotShader = new MyShader("../Source/basicShader.vs", "../Source/basicShader.fs");

	//ShaderInfo shaders[] = {
	//	{ GL_VERTEX_SHADER, "DSPhong_Material.vp" },//vertex shader
	//	{ GL_FRAGMENT_SHADER, "DSPhong_Material.fp" },//fragment shader
	//	{ GL_NONE, NULL } };
	//program = LoadShaders(shaders);//讀取shader

	//Attach Shader to program

	projectMt = glm::perspective(80.0f, 4.0f / 4.0f, 0.1f, 100.0f);
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	viewMt = glm::lookAt(
		glm::vec3(0, 10, 25), // Camera is at (0,10,25), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,1,0 to look upside-down)
	);

	robot = new Robot(robotShader);
}


void My_Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	modelMt = glm::mat4(1.0f);
	modelMt = glm::scale(modelMt, glm::vec3(4.0f));


	robot -> use();
	robot -> setMt(&modelMt, &viewMt, &projectMt);
	robot -> update();
	robot -> draw();

	glFlush();//強制執行上次的OpenGL commands
	glutSwapBuffers();
}


//計時器事件, 經指定時間後該函式被呼叫
void My_Timer(int val)
{
	glutPostRedisplay();     //使程式於下次迴圈執行時更新畫面
	glutTimerFunc(16, My_Timer, val);

	char ch;
	if (_kbhit()) {
	}
}


int main(int argc, char **argv)
{
#ifdef __APPLE__
	//更改工作路徑
	chdir(__FILEPATH__("/../Assets/"));
#endif

	// 初始化GLUT,並創立一個視窗.
	////////////////////
	glutInit(&argc, argv);

	//multisample for golygons smooth
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);

	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	
	glutCreateWindow("HW1"); 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	My_Init();
	
	//註冊GLUT回呼事件
	////////////////////
	glutDisplayFunc(My_Display);
	glutTimerFunc(16, My_Timer, 0);
    
	// 進入主迴圈
	glutMainLoop();
	
	return 0;
}
