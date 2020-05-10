#ifndef __MY__MENU__
#define __MY__MENU__
#include "../Include/Common.h"
#include "Robot.h"

Robot* robot;

namespace Menu{

	void ActionMenuEvents(int option) {
		robot->switchMode(option);
	}

	void create() {
		int ActionMenu, ModeMenu, ShaderMenu;
		ActionMenu = glutCreateMenu(ActionMenuEvents);//�إߥk����
		//�[�J�k�䪫��
		glutAddMenuEntry("idle", robot->MODE_IDLE);
		glutAddMenuEntry("walk", robot->MODE_WALK);
		glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p

		// ModeMenu = glutCreateMenu(ModeMenuEvents);//�إߥk����
		// //�[�J�k�䪫��
		// glutAddMenuEntry("Line", 0);
		// glutAddMenuEntry("Fill", 1);
		// glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p

		glutCreateMenu(nullptr);//�إߥk����
		//�[�J�k�䪫��
		glutAddSubMenu("action", ActionMenu);
		// glutAddSubMenu("mode", ModeMenu);
		glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p
	}
}

#endif