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
		ActionMenu = glutCreateMenu(ActionMenuEvents);//建立右鍵菜單
		//加入右鍵物件
		glutAddMenuEntry("idle", robot->MODE_IDLE);
		glutAddMenuEntry("walk", robot->MODE_WALK);
		glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯

		// ModeMenu = glutCreateMenu(ModeMenuEvents);//建立右鍵菜單
		// //加入右鍵物件
		// glutAddMenuEntry("Line", 0);
		// glutAddMenuEntry("Fill", 1);
		// glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯

		glutCreateMenu(nullptr);//建立右鍵菜單
		//加入右鍵物件
		glutAddSubMenu("action", ActionMenu);
		// glutAddSubMenu("mode", ModeMenu);
		glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯
	}
}

#endif