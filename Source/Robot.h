#ifndef __MY__ROBOT__
#define __MY__ROBOT__
#include "../Include/Common.h"
#include "MyObject.h"
#include "MyShader.h"
#define PARTSNUM 18

class Robot {
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
	float position = 0.0;
	float angle = 0.0;
	float eyeAngley = 0.0;
	float eyedistance = 20.0;

public:
	Robot(MyShader* shader):
	body(shader),
	ulefthand(shader),
	dlefthand(shader),
	lefthand(shader),
	lshouder(shader),
	head(shader),
	urighthand(shader),
	drighthand(shader),
	righthand(shader),
	rshouder(shader),
	dbody(shader),
	back2(shader),
	uleftleg(shader),
	dleftleg(shader),
	leftfoot(shader),
	urightleg(shader),
	drightleg(shader),
	rightfoot(shader)
	{
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
		urightleg.init("../Assets/Robot/leftfoot.obj", "../Assets/Robot/gundam.mtl", 14);
		
		allObjs.push_back(&urightleg);
		urightleg.init("../Assets/Robot/urightleg.obj", "../Assets/Robot/gundam.mtl", 15);
		
		allObjs.push_back(&drightleg);
		drightleg.init("../Assets/Robot/drightleg.obj", "../Assets/Robot/gundam.mtl", 16);
		
		allObjs.push_back(&rightfoot);
		rightfoot.init("../Assets/Robot/rightfoot.obj", "../Assets/Robot/gundam.mtl", 17);
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
		updatePos(0);
		glm::mat4x4 modelMt = this->modelMt;
		modelMt = glm::rotate(PI, glm::vec3(0, 0, 1));
		stackMat.push_back(modelMt);

		modelMt = glm::vec3(0, 2.9 + position, 0);
		modelMt = body.setModelMt(&modelMt);
		stackMat.push_back(modelMt);

#pragma region 左手

		// 左上臂
		ulefthand.setRotateZ(10);
		modelMt = ulefthand.setModelMt(&modelMt);
		ulefthand.position = glm::vec3(3.7, 1, -0.5);

		// 左肩
		modelMt = lshouder.setModelMt(&modelMt);

		// 左下臂
		dlefthand.setRotateX(ulefthand.rotationX - 20);
		dlefthand.position = glm::vec3(0, -3, 0);
		modelMt = dlefthand.setModelMt(&modelMt);

		// 左手掌
		lefthand.position = glm::vec3(0, -4.8, 0);
		modelMt = lefthand.setModelMt(&modelMt);

#pragma endregion

#pragma region 頭
		modelMt = stackMat.back();
		head.position = glm::vec3(0, 3.9, -0.5);
		modelMt = head.setModelMt(&modelMt);
#pragma endregion

#pragma region 右手
		modelMt = rshouder.setModelMt(&modelMt);
		modelMt = urighthand.setModelMt(&modelMt);
		modelMt = drighthand.setModelMt(&modelMt);
		modelMt = righthand.setModelMt(&modelMt);
		
		modelMt = stackMat.back();
		stackMat.pop_back();
		stackMat.push_back(modelMt);
#pragma endregion
		
		modelMt = uleftleg.setModelMt(&modelMt);
		modelMt = dleftleg.setModelMt(&modelMt);
		modelMt = leftfoot.setModelMt(&modelMt);
		
		modelMt = stackMat.back();
		stackMat.pop_back();
		stackMat.push_back(modelMt);
		
		modelMt = urightleg.setModelMt(&modelMt);
		modelMt = drightleg.setModelMt(&modelMt);
		modelMt = rightfoot.setModelMt(&modelMt);
		stackMat.pop_back();
		stackMat.pop_back();
	}

	void updatePos(int frame) {
		switch (frame) {
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
#endif