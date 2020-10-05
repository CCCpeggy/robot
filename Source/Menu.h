#ifndef __MY__MENU__
#define __MY__MENU__
#include "../Include/Common.h"
#include "Robot.h"
#include "MyObject.h"
#include "Framebuffer.h"

Robot* robot;
FrameBuffer mainFBO;

namespace Menu{

	void ActionMenuEvents(int option) {
		robot->switchMode(option);
	}

	void DrawTypeMenuEvents(int drawType) {
		robot->setDrawType(drawType);
	}

	void ShaderModeMenuEvents(int mode) {
		mainFBO.switchMode(mode);
	}

	void RobotModeMenuEvents(int mode) {
		robot->setShaderType(mode);
	}

	void create() {
		int ActionMenu, ModeMenu, FBOShaderMenu, RobotShaderMenu, DrawTypeMenu;

		ActionMenu = glutCreateMenu(ActionMenuEvents);//�إߥk����
		//�[�J�k�䪫��
		glutAddMenuEntry("idle", Robot::MODE_IDLE);
		glutAddMenuEntry("walk", Robot::MODE_WALK);
		glutAddMenuEntry("wave", Robot::MODE_WAVE);
		glutAddMenuEntry("dance", Robot::MODE_DANCE);
		glutAddMenuEntry("jump", Robot::MODE_JUMP);
		glutAddMenuEntry("kick", Robot::MODE_CROUCH_DOWN);
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

		FBOShaderMenu = glutCreateMenu(ShaderModeMenuEvents);//�إߥk����
		//�[�J�k�䪫��
		glutAddMenuEntry("normal", FrameBuffer::SHADER_MODE_NORMAL);
		glutAddMenuEntry("gray", FrameBuffer::SHADER_MODE_GRAY);
		glutAddMenuEntry("pixel", FrameBuffer::SHADER_MODE_PIXEL);
		glutAddMenuEntry("sharpen", FrameBuffer::SHADER_MODE_KERNEL);
		glutAddMenuEntry("Gussian blur", FrameBuffer::SHADER_MODE_GUSSIAN_BLUR);
		glutAddMenuEntry("Android 8", FrameBuffer::SHADER_MODE_ANDROID_8);
		glutAddMenuEntry("Android 9", FrameBuffer::SHADER_MODE_ANDROID);

		glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p

		RobotShaderMenu = glutCreateMenu(RobotModeMenuEvents);//�إߥk����
		//�[�J�k�䪫��
		glutAddMenuEntry("mtl", 1);
		glutAddMenuEntry("cartoon", 2);
		glutAddMenuEntry("normal map", 3);
		glutAddMenuEntry("matcap", 4);

		glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p

		glutCreateMenu(nullptr);//�إߥk����
		//�[�J�k�䪫��
		glutAddSubMenu("action", ActionMenu);
		glutAddSubMenu("draw type", DrawTypeMenu);
		glutAddSubMenu("fbo shader mode", FBOShaderMenu);
		glutAddSubMenu("robot shader mode", RobotShaderMenu);
		// glutAddSubMenu("mode", ModeMenu);
		glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p
	}
}

#endif