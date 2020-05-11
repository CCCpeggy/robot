#ifndef __MY__MENU__
#define __MY__MENU__
#include "../Include/Common.h"
#include "Robot.h"
#include "MyObject.h"

Robot* robot;

namespace Menu{

	void ActionMenuEvents(int option) {
		robot->switchMode(option);
	}

	void DrawTypeMenuEvents(int drawType) {
		robot->setDrawType(drawType);
	}

	void create() {
		int ActionMenu, ModeMenu, ShaderMenu, DrawTypeMenu;

		ActionMenu = glutCreateMenu(ActionMenuEvents);//�إߥk����
		//�[�J�k�䪫��
		glutAddMenuEntry("idle", Robot::MODE_IDLE);
		glutAddMenuEntry("walk", Robot::MODE_WALK);
		glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p

		// ModeMenu = glutCreateMenu(ModeMenuEvents);//�إߥk����
		// //�[�J�k�䪫��
		// glutAddMenuEntry("Line", 0);
		// glutAddMenuEntry("Fill", 1);
		// glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p

		DrawTypeMenu = glutCreateMenu(DrawTypeMenuEvents);//�إߥk����
		//�[�J�k�䪫��
		glutAddMenuEntry("one robot", MyObject::DRAW_TYPE_NORMAL);
		glutAddMenuEntry("a lot of robots", MyObject::DRAW_TYPE_INSTANCE);
		glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p

		glutCreateMenu(nullptr);//�إߥk����
		//�[�J�k�䪫��
		glutAddSubMenu("action", ActionMenu);
		glutAddSubMenu("draw type", DrawTypeMenu);
		// glutAddSubMenu("mode", ModeMenu);
		glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p
	}
}

#endif