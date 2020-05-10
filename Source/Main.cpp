#include "../Include/Common.h"
#include "../Source/Robot.h"
#include "../Source/MyShader.h"
#include <conio.h>

glm::mat4x4 modelMt;
glm::mat4x4 viewMt;
glm::mat4x4 projectMt;
float eyeAngley = 0.0;
float eyedistance = 20.0;

Robot *robot;
MyShader *robotShader;

// 渲染事件, 用來在場景上繪製東西

void My_Init() {
	robotShader = new MyShader("../Source/basicShader.vs", "../Source/basicShader.fs");

	projectMt = glm::perspective(80.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	viewMt = glm::lookAt(
		glm::vec3(0, 10, 25), // Camera is at (0,10,25), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, -1, 0)  // Head is up (set to 0,1,0 to look upside-down)
	);

	robot = new Robot(robotShader);
}


void My_Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float eyey = DOR(eyeAngley);
	viewMt = glm::lookAt(
		glm::vec3(eyedistance * sin(eyey), 2, eyedistance * cos(eyey)),
		glm::vec3(0, 0, 0), 
		glm::vec3(0, -1, 0)
	);

	modelMt = glm::mat4(1.0f);

	robot -> setMt(&modelMt, &viewMt, &projectMt);
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

	robot -> update();
	My_Display();
}

void keyUpdate(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		eyedistance -= 0.2;
		break;
	case 's':
		eyedistance += 0.2;
		break;
	case 'a':
		eyeAngley -= 10;
		break;
	case 'd':
		eyeAngley += 10;
		break;
	}
	robot->keyUpdate(key, x, y);
	glutPostRedisplay();
}


int main(int argc, char **argv)
{
	// 初始化GLUT,並創立一個視窗.
	////////////////////
	glutInit(&argc, argv);
	glutInitContextVersion(4, 3);//以OpenGL version4.3版本為基準
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);//是否向下相容,GLUT_FORWARD_COMPATIBLE不支援(?
	glutInitContextProfile(GLUT_CORE_PROFILE);

	//multisample for golygons smooth
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	//glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	
	glutCreateWindow("HW1"); 

	glewExperimental = GL_TRUE; //置於glewInit()之前
	if (glewInit()) {
		std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;//c error
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	My_Init();

	glutKeyboardFunc(keyUpdate);
	
	//註冊GLUT回呼事件
	////////////////////
	glutDisplayFunc(My_Display);
	glutTimerFunc(60, My_Timer, 0);
    
	// 進入主迴圈
	glutMainLoop();
	
	return 0;
}
