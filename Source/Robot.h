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
	static const int MODE_RUN;
	static const int MODE_WAVE;
protected:
	MyObject body;
	MyObject dlefthand;
	MyObject lefthand;
	MyObject lshouder;
	MyObject head;
	MyObject drighthand;
	MyObject righthand;
	MyObject rshouder;
	MyObject uleftleg;
	MyObject dleftleg;
	MyObject leftfoot;
	MyObject urightleg;
	MyObject drightleg;
	MyObject rightfoot;
	MyObject ball;
	std::vector<MyObject*> allObjs;
	glm::mat4x4 modelMt;
	std::vector<glm::mat4x4> stackMat;

	float alpha[PARTSNUM];
	float beta[PARTSNUM];
	float gamma[PARTSNUM];
	glm::vec3 pos[PARTSNUM];
	float position;
	float angle;

private:
	int frame;
	int mode;

public:
	Robot(MyShader* shader = nullptr):
		body(shader, MyObject::DRAW_TYPE_INSTANCE),
		dlefthand(shader, MyObject::DRAW_TYPE_INSTANCE),
		lefthand(shader, MyObject::DRAW_TYPE_INSTANCE),
		lshouder(shader, MyObject::DRAW_TYPE_INSTANCE),
		head(shader, MyObject::DRAW_TYPE_INSTANCE),
		drighthand(shader, MyObject::DRAW_TYPE_INSTANCE),
		righthand(shader, MyObject::DRAW_TYPE_INSTANCE),
		rshouder(shader, MyObject::DRAW_TYPE_INSTANCE),
		uleftleg(shader, MyObject::DRAW_TYPE_INSTANCE),
		dleftleg(shader, MyObject::DRAW_TYPE_INSTANCE),
		leftfoot(shader, MyObject::DRAW_TYPE_INSTANCE),
		urightleg(shader, MyObject::DRAW_TYPE_INSTANCE),
		drightleg(shader, MyObject::DRAW_TYPE_INSTANCE),
		rightfoot(shader, MyObject::DRAW_TYPE_INSTANCE),
		ball(shader, MyObject::DRAW_TYPE_INSTANCE),
		frame(0),
		mode(MODE_WALK)
	{
		initRobotPart();
		addRobots();
		reset();
	}

	void initRobotPart() {
		allObjs.push_back(&body);
		body.init("../Assets/Robot2/Body.obj", "../Assets/Robot2/Body.mtl", 0);
		
		allObjs.push_back(&dlefthand);
		dlefthand.init("../Assets/Robot2/LArm.obj", "../Assets/Robot2/LArm.mtl", 2);
		
		allObjs.push_back(&lefthand);
		lefthand.init("../Assets/Robot2/LHand.obj", "../Assets/Robot2/LHand.mtl", 3);

		allObjs.push_back(&lshouder);
		lshouder.init("../Assets/Robot2/LShoulder.obj", "../Assets/Robot2/LShoulder.mtl", 4);
		
		allObjs.push_back(&head);
		head.init("../Assets/Robot2/Head.obj", "../Assets/Robot2/Head.mtl", 5);
		
		allObjs.push_back(&drighthand);
		drighthand.init("../Assets/Robot2/RArm.obj", "../Assets/Robot2/RArm.mtl", 7);
		
		allObjs.push_back(&righthand);
		righthand.init("../Assets/Robot2/RHand.obj", "../Assets/Robot2/RHand.mtl", 8);
		
		allObjs.push_back(&rshouder);
		rshouder.init("../Assets/Robot2/RShoulder.obj", "../Assets/Robot2/RShoulder.mtl", 9);
		
		allObjs.push_back(&uleftleg);
		uleftleg.init("../Assets/Robot2/LUpLeg.obj", "../Assets/Robot2/LUpLeg.mtl", 12);
		
		allObjs.push_back(&dleftleg);
		dleftleg.init("../Assets/Robot2/LDownLeg.obj", "../Assets/Robot2/LDownLeg.mtl", 13);
		
		allObjs.push_back(&leftfoot);
		leftfoot.init("../Assets/Robot2/LFeet.obj", "../Assets/Robot2/LFeet.mtl", 14);
		
		allObjs.push_back(&urightleg);
		urightleg.init("../Assets/Robot2/RUpLeg.obj", "../Assets/Robot2/RUpLeg.mtl", 15);
		
		allObjs.push_back(&drightleg);
		drightleg.init("../Assets/Robot2/RDownLeg.obj", "../Assets/Robot2/RDownLeg.mtl", 16);
		
		allObjs.push_back(&rightfoot);
		rightfoot.init("../Assets/Robot2/RFeet.obj", "../Assets/Robot2/RFeet.mtl", 17);

		allObjs.push_back(&ball);
		ball.init("../Assets/ball.obj", "../Assets/ball.mtl", 18);
	}
	
	void addRobots() {
		glm::vec3 offsets[] = {
			//glm::vec3(35.0f, 3.0f, -30.0f),
			//glm::vec3(0.0f, 0.0f, -30.0f),
			//glm::vec3(-35.0f, 3.0f, -30.0f),
			//glm::vec3(-12.0f, 3.0f, -10.0f),
			//glm::vec3(12.0f, 3.0f, -10.0f),
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
		else if (mode == MODE_WAVE) {
			updateWaveFrame();
		}
		glm::mat4 Rotatation[PARTSNUM];
		glm::mat4 Translation[PARTSNUM];
		for (int i = 0; i < PARTSNUM; i++) {
			Rotatation[i] = glm::mat4(1.0f);
			Translation[i] = glm::mat4(1.0f);
		}
		float r;

		//Body
		Rotatation[0] = glm::rotate(DOR(alpha[0]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[0]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[0]), glm::vec3(0, 1, 0));
		Translation[0] = glm::translate(glm::vec3(0, position, 0) + pos[0]);
		body.setModelMt(&(this->modelMt * Translation[0] * Rotatation[0]));

		//¥ªªÓ»H
		Rotatation[4] = glm::rotate(DOR(alpha[4]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[4]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[4]), glm::vec3(0, 1, 0));
		Translation[4] = glm::translate(pos[4]);
		lshouder.setModelMt(&(body.modelMt * Translation[4] * Rotatation[4] * glm::translate(-pos[4])));

		//¥ª¤U¤âÁu
		r = -8;
		Rotatation[2] = Rotatation[4] * glm::rotate(DOR(alpha[2]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[2]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[2]), glm::vec3(0, 1, 0));
		Translation[2] = Translation[4] * glm::translate(glm::vec3(-r * cos(DOR(alpha[4])) * sin(DOR(gamma[4])), r * cos(DOR(alpha[4])) * cos(DOR(gamma[4])), r * sin(DOR(alpha[4]))));
		dlefthand.setModelMt(&(body.modelMt * Translation[2] * Rotatation[2] * glm::translate(-pos[2])));

		r = -9.5;
		Rotatation[3] = Rotatation[2] * glm::rotate(DOR(alpha[3]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[3]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[3]), glm::vec3(0, 1, 0));
		Translation[3] = Translation[2] * glm::translate(glm::vec3(-r * cos(DOR(alpha[2] + alpha[4])) * sin(DOR(gamma[2] + gamma[4])), r * cos(DOR(alpha[2] + alpha[4])) * cos(DOR(gamma[2] + gamma[4])), r * sin(DOR(alpha[2] + alpha[4]))));
		lefthand.setModelMt(&(body.modelMt * Translation[3] * Rotatation[3] * glm::translate(-pos[3])));

		//============================================================
		//ÀY==========================================================
		Rotatation[5] = glm::rotate(DOR(alpha[5]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[5]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[5]), glm::vec3(0, 1, 0));
		Translation[5] = glm::translate(pos[5]);
		head.setModelMt(&(body.modelMt * Translation[5] * Rotatation[5] * glm::translate(-pos[5])));
		//============================================================
		//¥k¤â=========================================================
		Rotatation[9] = glm::rotate(DOR(alpha[9]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[9]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[9]), glm::vec3(0, 1, 0));
		Translation[9] = glm::translate(pos[9]);
		rshouder.setModelMt(&(body.modelMt * Translation[9] * Rotatation[9] * glm::translate(-pos[9])));

		r = -8;
		Rotatation[7] = Rotatation[9] * glm::rotate(DOR(alpha[7]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[7]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[7]), glm::vec3(0, 1, 0));
		Translation[7] = Translation[9] * glm::translate(glm::vec3(-r * cos(DOR(alpha[9])) * sin(DOR(gamma[9])), r * cos(DOR(alpha[9])) * cos(DOR(gamma[9])), r * sin(DOR(alpha[9]))));
		drighthand.setModelMt(&(body.modelMt * Translation[7] * Rotatation[7] * glm::translate(-pos[7])));

		r = -9.5;
		Rotatation[8] = Rotatation[7] * glm::rotate(DOR(alpha[8]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[8]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[8]), glm::vec3(0, 1, 0));
		Translation[8] = Translation[7] * glm::translate(glm::vec3(-r * cos(DOR(alpha[7] + alpha[9])) * sin(DOR(gamma[7] + gamma[9])), r * cos(DOR(alpha[7] + alpha[9])) * cos(DOR(gamma[7] + gamma[9])), r * sin(DOR(alpha[7] + alpha[9]))));
		righthand.setModelMt(&(body.modelMt * Translation[8] * Rotatation[8] * glm::translate(-pos[8])));
		//=============================================================
		//¥ª¸}
		r = -10;
		Rotatation[12] = glm::rotate(DOR(alpha[12]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[12]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[12]), glm::vec3(0, 1, 0));
		Translation[12] = glm::translate(pos[12]);
		uleftleg.setModelMt(&(this->modelMt * Translation[12] * Rotatation[12] * glm::translate(-pos[12])));

		Rotatation[13] = Rotatation[12] * glm::rotate(DOR(alpha[13]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[13]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[13]), glm::vec3(0, 1, 0));
		Translation[13] = Translation[12] * glm::translate(glm::vec3(-r * cos(DOR(alpha[12])) * sin(DOR(gamma[12])), r * cos(DOR(alpha[12])) * cos(DOR(gamma[12])), r * sin(DOR(alpha[12])))) ;
		dleftleg.setModelMt(&(this->modelMt * Translation[13] * Rotatation[13] * glm::translate(-pos[13])));

		Rotatation[14] = Rotatation[13] * glm::rotate(DOR(alpha[14]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[14]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[14]), glm::vec3(0, 1, 0));
		Translation[14] = Translation[13] * glm::translate(glm::vec3(-r * cos(DOR(alpha[13] + alpha[12])) * sin(DOR(gamma[13] + gamma[12])), r * cos(DOR(alpha[13] + alpha[12])) * cos(DOR(gamma[13] + gamma[12])), r * sin(DOR(alpha[13] + alpha[12]))));
		leftfoot.setModelMt(&(this->modelMt * Translation[14] * Rotatation[14] * glm::translate(-pos[14])));
		//=============================================================
		////¥k¸}
		Rotatation[15] = glm::rotate(DOR(alpha[15]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[15]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[15]), glm::vec3(0, 1, 0));
		Translation[15] = glm::translate(pos[15]);
		urightleg.setModelMt(&(this->modelMt * Translation[15] * Rotatation[15] * glm::translate(-pos[15])));

		Rotatation[16] = Rotatation[15] * glm::rotate(DOR(alpha[16]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[16]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[16]), glm::vec3(0, 1, 0));
		Translation[16] = Translation[15] * glm::translate(glm::vec3(-r * cos(DOR(alpha[15])) * sin(DOR(gamma[15])), r * cos(DOR(alpha[15])) * cos(DOR(gamma[15])), r * sin(DOR(alpha[15]))));
		drightleg.setModelMt(&(this->modelMt * Translation[16] * Rotatation[16] * glm::translate(-pos[16])));

		Rotatation[17] = Rotatation[16] * glm::rotate(DOR(alpha[17]), glm::vec3(1, 0, 0)) * glm::rotate(DOR(gamma[17]), glm::vec3(0, 0, 1)) * glm::rotate(DOR(beta[17]), glm::vec3(0, 1, 0));
		Translation[17] = Translation[16] * glm::translate(glm::vec3(-r * cos(DOR(alpha[16] + alpha[15])) * sin(DOR(gamma[16] + gamma[15])), r * cos(DOR(alpha[16] + alpha[15])) * cos(DOR(gamma[16] + gamma[15])), r * sin(DOR(alpha[16] + alpha[15]))));
		rightfoot.setModelMt(&(this->modelMt * Translation[17] * Rotatation[17] * glm::translate(-pos[17])));
		ball.setModelMt(&(this->modelMt * glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f) * 20.0f)));
		//=============================================================
	}
	int index = 14;
	void keyUpdate(unsigned char key, int x, int y) {
		switch (key) {
		case '1':
			angle += 5;
			if (angle >= 360) angle = 0;
			break;
		case '2':
			angle -= 5;
			if (angle <= 0) angle = 360;
			break;
		
		case 'r':
			alpha[4] -= 5;
			if (alpha[4] == -360) alpha[4] = 0;
			break;
		case 't':
			alpha[2] -= 5;
			if (alpha[2] == -360) alpha[2] = 0;
			break;
		case 'q':
			break;
		case 'e':
			break;
		case 'j':
			pos[index].x -= 0.3;
			break;
		case 'l':
			pos[index].x += 0.3;
			break;
		case 'i':
			pos[index].y += 0.3;
			break;
		case 'k':
			pos[index].y -= 0.3;
			break;
		case 'p':
			pos[index].z += 0.3;
			break;
		case ';':
			pos[index].z -= 0.3;
			break;
		case 'y':
			index++;
			break;
		case 'h':
			index--;
			break;
		case '.':
			alpha[index] += 5;
			break;
		case '/':
			alpha[index] -= 5;
			break;
		case 'm':
			beta[index] += 5;
			break;
		case ',':
			beta[index] -= 5;
			break;
		case 'b':
			gamma[index] += 5;
			break;
		case 'n':
			gamma[index] -= 5;
			break;
		}
		std::cout << index << ":" << pos[index].x << ", " << pos[index].y << ", " << pos[index].z << std::endl;
		std::cout << index << ":" << alpha[index] << ", " << beta[index] << ", " << gamma[index] << std::endl;
		glutPostRedisplay();
	}

	void switchMode(int mode) {
		if (this->mode != mode) {
			this->mode = mode;
			frame = 0;
		}

	}

	void updateIdleFrame() {
		if (frame++) {
			reset();
		}
	}

	void reset() {
		for (int i = 0; i < PARTSNUM; i++) {
			alpha[i] = 0;
			beta[i] = 0;
			gamma[i] = 0;
			pos[i].x = pos[i].y = pos[i].z = 0;
		}
		position = 0;
		angle = 0;
		pos[2] = glm::vec3(20, -2, 0);
		pos[3] = glm::vec3(20, -11.5, 0);
		pos[4] = glm::vec3(20, 6, 0);
		pos[7] = glm::vec3(-20, -2, 0);
		pos[8] = glm::vec3(-20, -11.5, 0);
		pos[9] = glm::vec3(-20, 6, 0);
		pos[12] = glm::vec3(5.4, -18, 0);
		pos[13] = glm::vec3(5.4, -28, 0);
		pos[14] = glm::vec3(5.4, -37.3, 0);
		pos[15] = glm::vec3(-5.4, -18, 0);
		pos[16] = glm::vec3(-5.4, -28, 0);
		pos[17] = glm::vec3(-5.4, -37.3, 0);

		alpha[2] = -20;
		alpha[7] = -20;
		gamma[12] = 10;
		gamma[15] = -10;
	}

	void updateWalkFrame() {
		int speed = 10;
		if (frame >= 13 * speed) {
			frame  = speed;
		}
		if (frame++ % speed) return;
		switch (frame / speed) {
		case 0:
			reset();
			alpha[2] = -45;
			alpha[13] = 45;
			break;
		case 1:
		case 2:
		case 3:
			alpha[4] += 10;
			alpha[12] -= 15;
			alpha[13] = 0;
			position += 0.1;
			break;
		case 4:
		case 5:
		case 6:
			alpha[4] -= 10;
			alpha[12] += 15;
			alpha[13] -= 15;
			position -= 0.1;
			break;
		case 7:
		case 8:
		case 9:
			alpha[4] -= 10;
			alpha[12] += 15;
			alpha[13] = 0;
			position += 0.1;
			break;
		case 10:
		case 11:
		case 12:
			alpha[4] += 10;
			alpha[12] -= 15;
			alpha[13] += 15;
			position -= 0.1;
			break;
		}
		alpha[9] = -alpha[4];
		alpha[7] = alpha[2];
		alpha[15] = -alpha[12];
		alpha[16] = alpha[13];

		// gamma[4] = 10 + gamma[3];
		// gamma[9] = -10 + gamma[8];
	}
	
	void updateWaveFrame() {
		int speed = 7;
		if (frame >= 7 * speed) {
			frame = speed;
		}
		if (frame++ % speed) return;
		switch (frame / speed) {
		case 0:
			reset();
			beta[3] = beta[8] = -90;
			alpha[8] = 15;
			alpha[8] = -15;
			alpha[4] = 200;
			alpha[8] = 200;
			gamma[3] -= 45;
			break;
		case 1:
		case 2:
		case 3:
			gamma[3] += 10;
			break;
		case 4:
		case 5:
		case 6:
			gamma[3] -= 10;
			break;
		}
		gamma[7] = gamma[3];
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

	void setDrawType(int drawType) {
		for (std::vector<MyObject*>::iterator iter = allObjs.begin();
			iter != allObjs.end();
			iter++
			) {
			(*iter)->setDrawType(drawType);
		}
	}
};

const int Robot::MODE_WALK = 1;
const int Robot::MODE_IDLE = 0;
const int Robot::MODE_RUN = 2;
const int Robot::MODE_WAVE = 3;
#endif