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
		ulefthand.position = glm::vec3(0, 2.9, 0);

		allObjs.push_back(&ulefthand);
		ulefthand.init("../Assets/Robot/ulefthand.obj", "../Assets/Robot/gundam.mtl", 1);
		ulefthand.position = glm::vec3(3.7, 1, -0.5);
		
		allObjs.push_back(&lefthand);
		dlefthand.init("../Assets/Robot/dlefthand.obj", "../Assets/Robot/gundam.mtl", 2);
		ulefthand.position = glm::vec3(3.7, 1, -0.5);

		allObjs.push_back(&lefthand);
		lefthand.init("../Assets/Robot/lefthand.obj", "../Assets/Robot/gundam.mtl", 3);
		ulefthand.position = glm::vec3(0, -3, 0);

		allObjs.push_back(&lshouder);
		lshouder.init("../Assets/Robot/lshouder.obj", "../Assets/Robot/gundam.mtl", 4);
		ulefthand.position = glm::vec3(3.7, 1, -0.5);

		allObjs.push_back(&head);
		head.init("../Assets/Robot/head.obj", "../Assets/Robot/gundam.mtl", 5);
		ulefthand.position = glm::vec3(0, 3.9, -0.5);

		allObjs.push_back(&urighthand);
		urighthand.init("../Assets/Robot/urighthand.obj", "../Assets/Robot/gundam.mtl", 6);
		ulefthand.position = glm::vec3(-3.9, 1.7, -0.2);

		allObjs.push_back(&drighthand);
		drighthand.init("../Assets/Robot/drighthand.obj", "../Assets/Robot/gundam.mtl", 7);
		ulefthand.position = glm::vec3(0, -3, 0);

		allObjs.push_back(&righthand);
		righthand.init("../Assets/Robot/righthand.obj", "../Assets/Robot/gundam.mtl", 8);
		ulefthand.position = glm::vec3(0, -6, 0);

		allObjs.push_back(&rshouder);
		rshouder.init("../Assets/Robot/rshouder.obj", "../Assets/Robot/gundam.mtl", 9);
		ulefthand.position = glm::vec3(-3.9, 1.1, -0.2);

		allObjs.push_back(&dbody);
		dbody.init("../Assets/Robot/dbody.obj", "../Assets/Robot/gundam.mtl", 10);
		ulefthand.position = glm::vec3(0, 2, -4.5);

		allObjs.push_back(&back2);
		back2.init("../Assets/Robot/back2.obj", "../Assets/Robot/gundam.mtl", 11);
		ulefthand.position = glm::vec3(0, -5.3, 0);

		allObjs.push_back(&uleftleg);
		uleftleg.init("../Assets/Robot/uleftleg.obj", "../Assets/Robot/gundam.mtl", 12);
		ulefthand.position = glm::vec3(1.8, -4.5, 0);

		allObjs.push_back(&dleftleg);
		dleftleg.init("../Assets/Robot/dleftleg.obj", "../Assets/Robot/gundam.mtl", 13);
		ulefthand.position = glm::vec3(1.8, -4.5, 0);

		// allObjs.push_back(&leftfoot);
		// urightleg.init("../Assets/Robot/leftfoot.obj", "../Assets/Robot/gundam.mtl", 14);
		// leftfoot.position = glm::vec3(0, -3, 0);
		// 
		// allObjs.push_back(&urightleg);
		// urightleg.init("../Assets/Robot/urightleg.obj", "../Assets/Robot/gundam.mtl", 15);
		// ulefthand.position = glm::vec3(0, -3, 0);
		// 
		// allObjs.push_back(&drightleg);
		// drightleg.init("../Assets/Robot/drightleg.obj", "../Assets/Robot/gundam.mtl", 16);
		// ulefthand.position = glm::vec3(0, -3, 0);
		// 
		// allObjs.push_back(&rightfoot);
		// rightfoot.init("../Assets/Robot/rightfoot.obj", "../Assets/Robot/gundam.mtl", 17);
		// ulefthand.position = glm::vec3(0, -3, 0);
	}
	void use() {
		for (std::vector<MyObject*>::iterator iter = allObjs.begin();
			iter != allObjs.end();
			iter++
			) {
			(*iter)->use();
		}
	}
	void setMt(glm::mat4x4* modelMt, glm::mat4x4* viewMt = nullptr, glm::mat4x4* projectMt = nullptr) {
		for (std::vector<MyObject*>::iterator iter = allObjs.begin();
			iter != allObjs.end();
			iter++
			) {
			this->modelMt = *modelMt;
			(*iter)->setViewProjectMt(viewMt, projectMt);
		}
	}
	void update() {
		updatePos(0);
		glm::mat4x4 modelMt = this->modelMt;
		stackMat.push_back(modelMt);
		modelMt = body.setModelMt(&modelMt);
		modelMt = ulefthand.setModelMt(&modelMt);
		modelMt = lefthand.setModelMt(&modelMt);
		stackMat.pop_back();
	}
	void updatePos(int frame) {
		switch (frame) {
		case 0:
			//¥ª¤â
			ulefthand.rotation.y = -45;
			//¥k¤â

			//»L
			uleftleg.rotation.y = 45;
			break;
		//case 1:
		//case 2:
		//case 3:
		//	angles[1] += 10;
		//	angles[12] -= 15;
		//	position += 0.1;
		//	break;
		//case 4:
		//case 5:
		//case 6:
		//	angles[1] -= 10;
		//	angles[12] += 15;
		//	angles[13] -= 15;
		//	position -= 0.1;
		//	break;
		//case 7:
		//case 8:
		//case 9:
		//	angles[1] -= 10;
		//	angles[12] += 15;
		//	angles[13] = 0;
		//	position += 0.1;
		//	break;
		//case 10:
		//case 11:
		//case 12:
		//	angles[1] += 10;
		//	angles[12] -= 15;
		//	angles[13] += 15;
		//	position -= 0.1;
		//	break;
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