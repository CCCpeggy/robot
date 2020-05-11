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

		ActionMenu = glutCreateMenu(ActionMenuEvents);//建立右鍵菜單
		//加入右鍵物件
		glutAddMenuEntry("idle", Robot::MODE_IDLE);
		glutAddMenuEntry("walk", Robot::MODE_WALK);
		glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯

		// ModeMenu = glutCreateMenu(ModeMenuEvents);//建立右鍵菜單
		// //加入右鍵物件
		// glutAddMenuEntry("Line", 0);
		// glutAddMenuEntry("Fill", 1);
		// glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯

		DrawTypeMenu = glutCreateMenu(DrawTypeMenuEvents);//建立右鍵菜單
		//加入右鍵物件
		glutAddMenuEntry("one robot", MyObject::DRAW_TYPE_NORMAL);
		glutAddMenuEntry("a lot of robots", MyObject::DRAW_TYPE_INSTANCE);
		glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯

		glutCreateMenu(nullptr);//建立右鍵菜單
		//加入右鍵物件
		glutAddSubMenu("action", ActionMenu);
		glutAddSubMenu("draw type", DrawTypeMenu);
		// glutAddSubMenu("mode", ModeMenu);
		glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯
	}
}

#endif