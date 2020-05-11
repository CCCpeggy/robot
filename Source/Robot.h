#ifndef __MY__ROBOT__
#define __MY__ROBOT__
#include "../Include/Common.h"
#include "MyObject.h"
#include "MyShader.h"
#define PARTSNUM 18

class Robot {
public:
	static const int MODE_WALK;
	static const int MODE_IDLE;
protected:
	MyObject body;
	MyObject ulefthand;
	MyObject dlefthand;
	MyObject lefthand;
	MyObject lshouder;
	MyObject head;
	MyObject urighthand;
	MyObject drighthand;
	MyObject righthand;
	MyObject rshouder;
	MyObject dbody;
	MyObject back2;
	MyObject uleftleg;
	MyObject dleftleg;
	MyObject leftfoot;
	MyObject urightleg;
	MyObject drightleg;
	MyObject rightfoot;
	std::vector<MyObject*> allObjs;
	glm::mat4x4 modelMt;
	std::vector<glm::mat4x4> stackMat;

	float angles[PARTSNUM];
	float position;
	float angle;

private:
	int frame;
	int mode;

public:
	Robot(MyShader* shader = nullptr):
		body(shader, MyObject::DRAW_TYPE_INSTANCE),
		ulefthand(shader, MyObject::DRAW_TYPE_INSTANCE),
		dlefthand(shader, MyObject::DRAW_TYPE_INSTANCE),
		lefthand(shader, MyObject::DRAW_TYPE_INSTANCE),
		lshouder(shader, MyObject::DRAW_TYPE_INSTANCE),
		head(shader, MyObject::DRAW_TYPE_INSTANCE),
		urighthand(shader, MyObject::DRAW_TYPE_INSTANCE),
		drighthand(shader, MyObject::DRAW_TYPE_INSTANCE),
		righthand(shader, MyObject::DRAW_TYPE_INSTANCE),
		rshouder(shader, MyObject::DRAW_TYPE_INSTANCE),
		dbody(shader, MyObject::DRAW_TYPE_INSTANCE),
		back2(shader, MyObject::DRAW_TYPE_INSTANCE),
		uleftleg(shader, MyObject::DRAW_TYPE_INSTANCE),
		dleftleg(shader, MyObject::DRAW_TYPE_INSTANCE),
		leftfoot(shader, MyObject::DRAW_TYPE_INSTANCE),
		urightleg(shader, MyObject::DRAW_TYPE_INSTANCE),
		drightleg(shader, MyObject::DRAW_TYPE_INSTANCE),
		rightfoot(shader, MyObject::DRAW_TYPE_INSTANCE),
		frame(0),
		mode(MODE_IDLE),
		angle(0),
		position(0),
		angles{0}
	{
		initRobotPart();
		addRobots();
	}

	void initRobotPart() {
		allObjs.push_back(&body);
		body.init("../Assets/Robot/body.obj", "../Assets/Robot/gundam.mtl", 0);
		
		allObjs.push_back(&ulefthand);
		ulefthand.init("../Assets/Robot/ulefthand.obj", "../Assets/Robot/gundam.mtl", 1);
		
		allObjs.push_back(&dlefthand);
		dlefthand.init("../Assets/Robot/dlefthand.obj", "../Assets/Robot/gundam.mtl", 2);
		
		allObjs.push_back(&lefthand);
		lefthand.init("../Assets/Robot/lefthand.obj", "../Assets/Robot/gundam.mtl", 3);
		
		allObjs.push_back(&lshouder);
		lshouder.init("../Assets/Robot/lshouder.obj", "../Assets/Robot/gundam.mtl", 4);
		
		allObjs.push_back(&head);
		head.init("../Assets/Robot/head.obj", "../Assets/Robot/gundam.mtl", 5);
		
		allObjs.push_back(&urighthand);
		urighthand.init("../Assets/Robot/urighthand.obj", "../Assets/Robot/gundam.mtl", 6);
		
		allObjs.push_back(&drighthand);
		drighthand.init("../Assets/Robot/drighthand.obj", "../Assets/Robot/gundam.mtl", 7);
		
		allObjs.push_back(&righthand);
		righthand.init("../Assets/Robot/righthand.obj", "../Assets/Robot/gundam.mtl", 8);
		
		allObjs.push_back(&rshouder);
		rshouder.init("../Assets/Robot/rshouder.obj", "../Assets/Robot/gundam.mtl", 9);
		
		allObjs.push_back(&back2);
		back2.init("../Assets/Robot/back2.obj", "../Assets/Robot/gundam.mtl", 10);
		
		allObjs.push_back(&dbody);
		dbody.init("../Assets/Robot/dbody.obj", "../Assets/Robot/gundam.mtl", 11);
		
		allObjs.push_back(&uleftleg);
		uleftleg.init("../Assets/Robot/uleftleg.obj", "../Assets/Robot/gundam.mtl", 12);
		
		allObjs.push_back(&dleftleg);
		dleftleg.init("../Assets/Robot/dleftleg.obj", "../Assets/Robot/gundam.mtl", 13);
		
		allObjs.push_back(&leftfoot);
		leftfoot.init("../Assets/Robot/leftfoot.obj", "../Assets/Robot/gundam.mtl", 14);
		
		allObjs.push_back(&urightleg);
		urightleg.init("../Assets/Robot/urightleg.obj", "../Assets/Robot/gundam.mtl", 15);
		
		allObjs.push_back(&drightleg);
		drightleg.init("../Assets/Robot/drightleg.obj", "../Assets/Robot/gundam.mtl", 16);
		
		allObjs.push_back(&rightfoot);
		rightfoot.init("../Assets/Robot/rightfoot.obj", "../Assets/Robot/gundam.mtl", 17);
	}
	
	void addRobots() {
		glm::vec3 offsets[] = {
			glm::vec3(45.0f, 0.0f, -60.0f),
			glm::vec3(0.0f, 0.0f, -60.0f),
			glm::vec3(-45.0f, 0.0f, -60.0f),
			glm::vec3(-15.0f, 0.0f, -30.0f),
			glm::vec3(15.0f, 0.0f, -30.0f),
			glm::vec3(0.0f, 0.0f, 0.0f)
		};
		for (auto offset : offsets) {
			for (auto obj : allObjs) {
				obj -> addOffset(offset);
			}
		}
	}

	void setMt(glm::mat4x4* modelMt, glm::mat4x4* viewMt = nullptr, glm::mat4x4* projectMt = nullptr) {
		for (std::vector<MyObject*>::iterator iter = allObjs.begin();
			iter != allObjs.end();
			iter++
			) {
			(*iter)->use();
			this->modelMt = *modelMt;
			(*iter)->setViewProjectMt(viewMt, projectMt);
		}
	}
	
	void update() {
		if (mode == MODE_WALK) {
			updateWalkFrame();
		}
		else if (mode == MODE_IDLE) {
			updateIdleFrame();
		}
		glm::mat4 Rotatation[PARTSNUM];
		glm::mat4 Translation[PARTSNUM];
		for (int i = 0; i < PARTSNUM; i++) {
			Rotatation[i] = glm::mat4(1.0f);
			Translation[i] = glm::mat4(1.0f);
		}
		float r, pitch, yaw, roll;
		float alpha, beta, gamma;

		angles[6] = -angles[1];
		angles[7] = angles[2];
		angles[15] = -angles[12];
		angles[16] = angles[13];

		//Body
		beta = DOR(angle);
		Rotatation[0] = glm::rotate(beta, glm::vec3(0, 1, 0));
		Translation[0] = glm::translate(glm::vec3(0, 2.9 + position, 0));
		body.setModelMt(&(this->modelMt * Translation[0] * Rotatation[0]));
		//左手=======================================================
		//左上手臂
		yaw = DOR(beta); r = 3.7;
		alpha = DOR(angles[1]);
		gamma = DOR(10);
		Rotatation[1] = glm::rotate(alpha, glm::vec3(1, 0, 0)) * glm::rotate(gamma, glm::vec3(0, 0, 1));//向前旋轉*向右旋轉
		Translation[1] = glm::translate(glm::vec3(3.7, 1, -0.5));

		ulefthand.setModelMt(&(body.modelMt * Translation[1] * Rotatation[1]));

		//左肩膀
		lshouder.setModelMt(&(ulefthand.modelMt));

		//左下手臂
		alpha = DOR(angles[2] - 20);
		//上手臂+下手臂向前旋轉*向右旋轉
		Rotatation[2] = glm::rotate(alpha, glm::vec3(1, 0, 0));
		Translation[2] = glm::translate(glm::vec3(0, -3, 0));

		dlefthand.setModelMt(&(ulefthand.modelMt * Translation[2] * Rotatation[2]));

		pitch = DOR(alpha);
		roll = DOR(gamma);
		//延x軸位移以上手臂為半徑的圓周長:translate(0,r*cos,r*sin) ,角度為上手臂+下手臂
		Translation[3] = glm::translate(glm::vec3(0, -4.8, 0));
		lefthand.setModelMt(&(dlefthand.modelMt * Translation[3]));

		//============================================================
		//頭==========================================================
		Translation[5] = glm::translate(glm::vec3(0, 3.9, -0.5));
		head.setModelMt(&(body.modelMt * Translation[5]));
		//============================================================
		//右手=========================================================
		gamma = DOR(-10); 
		alpha = DOR(angles[6]);
		Rotatation[6] = glm::rotate(alpha, glm::vec3(1, 0, 0)) * glm::rotate(gamma, glm::vec3(0, 0, 1));
		Translation[6] = glm::translate(glm::vec3(-3.9, 1.7, -0.2));
		urighthand.setModelMt(&(body.modelMt * Translation[6] * Rotatation[6]));

		rshouder.setModelMt(&(urighthand.modelMt));

		alpha = DOR(angles[7] - 20);
		Rotatation[7] = glm::rotate(alpha, glm::vec3(1, 0, 0));
		Translation[7] = glm::translate(glm::vec3(0, -3, 0));
		drighthand.setModelMt(&(urighthand.modelMt * Translation[7] * Rotatation[7]));

		pitch = (alpha);
		roll = (gamma);
		Translation[8] = glm::translate(glm::vec3(0, -6, 0));
		righthand.setModelMt(&(drighthand.modelMt * Translation[8]));
		//=============================================================
		//back&DBody===================================================
		Translation[10] = translate(glm::vec3(0, 2, -4.5));
		back2.setModelMt(&(body.modelMt * Translation[10]));

		Translation[11] = translate(glm::vec3(0, -5.3, 0));
		dbody.setModelMt(&(body.modelMt * Translation[11]));
		//=============================================================
		//左腳
		alpha = DOR(angles[12]); gamma = DOR(10);
		Rotatation[12] = glm::rotate(alpha, glm::vec3(1, 0, 0)) * glm::rotate(gamma, glm::vec3(0, 0, 1));
		Translation[12] = glm::translate(glm::vec3(1.8, -4.5, 0));
		uleftleg.setModelMt(&(this->modelMt * Translation[12] * Rotatation[12]));

		pitch = (alpha); r = -7;
		roll = (gamma);
		alpha = DOR(angles[13] + angles[12]);
		Translation[13] = glm::translate(glm::vec3(-r * sin(roll), r * cos(pitch), r * sin(pitch))) * Translation[12];
		Rotatation[13] = glm::rotate(alpha, glm::vec3(1, 0, 0));
		dleftleg.setModelMt(&(this->modelMt * Translation[13] * Rotatation[13]));

		pitch = (alpha); r = -5;
		roll = (gamma);
		Translation[14] = glm::translate(glm::vec3(-(r + 2) * sin(roll), r * cos(pitch), r * sin(pitch) - 1)) * Translation[13];
		Rotatation[14] = glm::rotate(alpha, glm::vec3(1, 0, 0));
		leftfoot.setModelMt(&(this->modelMt * Translation[14] * Rotatation[14]));
		//=============================================================
		//右腳
		alpha = DOR(angles[15]);
		gamma = DOR(-10);
		Rotatation[15] = glm::rotate(alpha, glm::vec3(1, 0, 0)) * glm::rotate(gamma, glm::vec3(0, 0, 1));
		Translation[15] = glm::translate(glm::vec3(-1.8, -4.5, 0));
		urightleg.setModelMt(&(this->modelMt* Translation[15] * Rotatation[15]));

		pitch = (alpha); r = -7;
		roll = (gamma);
		alpha = DOR(angles[16] + angles[15]);
		Rotatation[16] = glm::rotate(alpha, glm::vec3(1, 0, 0));
		Translation[16] = glm::translate(glm::vec3(-r * sin(roll), r * cos(pitch), r * sin(pitch))) * Translation[15];
		drightleg.setModelMt(&(this->modelMt* Translation[16] * Rotatation[16]));

		pitch = (alpha); r = -5;
		roll = (gamma);
		Translation[17] = glm::translate(glm::vec3(-(r + 2) * sin(roll), r * cos(pitch), r * sin(pitch) - 0.5)) * Translation[16];
		Rotatation[17] = glm::rotate(alpha, glm::vec3(1, 0, 0));
		rightfoot.setModelMt(&(this->modelMt* Translation[17] * Rotatation[17]));
		//=============================================================
	}

	void keyUpdate(unsigned char key, int x, int y) {
		switch (key) {
		case '1':
			angle += 5;
			if (angle >= 360) angle = 0;
			printf("beta:%f\n", angle);
			break;
		case '2':
			angle -= 5;
			if (angle <= 0) angle = 360;
			printf("beta:%f\n", angle);
			break;
		
		case 'r':
			angles[1] -= 5;
			if (angles[1] == -360) angles[1] = 0;
			break;
		case 't':
			angles[2] -= 5;
			if (angles[2] == -360) angles[2] = 0;
			break;
		case 'q':
			break;
		case 'e':
			break;
		}
		glutPostRedisplay();
	}

	void switchMode(int mode) {
		if (this->mode != mode) {
			this->mode = mode;
			frame = 0;
		}
	}

	void updateIdleFrame() {
		angles[1] = 0;
		angles[2] = 0;
		angles[12] = 0;
		angles[13] = 0;
		position = 0;
	}

	void updateWalkFrame() {
		frame++;
		int speed = 6;
		frame %= 13 * speed;
		if (frame % speed) return;
		switch (frame / speed) {
		case 0:
			//左手
			angles[2] = -45;
			//右手

			//腿
			angles[13] = 45;

			break;
		case 1:
		case 2:
		case 3:
			angles[1] += 10;
			angles[12] -= 15;
			position += 0.1;
			break;
		case 4:
		case 5:
		case 6:
			angles[1] -= 10;
			angles[12] += 15;
			angles[13] -= 15;
			position -= 0.1;
			break;
		case 7:
		case 8:
		case 9:
			angles[1] -= 10;
			angles[12] += 15;
			angles[13] = 0;
			position += 0.1;
			break;
		case 10:
		case 11:
		case 12:
			angles[1] += 10;
			angles[12] -= 15;
			angles[13] += 15;
			position -= 0.1;
			break;
		}
	}
	
	void draw() {
		for (std::vector<MyObject*>::iterator iter = allObjs.begin();
			iter != allObjs.end();
			iter++
			) {
			(*iter)->use();
			(*iter)->draw();
		}
	}
};

const int Robot::MODE_WALK = 1;
const int Robot::MODE_IDLE = 0;
#endif