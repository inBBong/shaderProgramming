/*
Copyright 2022 Lee Taek Hee (Tech University of Korea)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"

Renderer *g_Renderer = NULL;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
	g_Renderer->DrawTest();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

/*
프로그램의 **진입점(main 함수)**이 있는 파일.

GLUT 초기화:

glutInit, glutInitDisplayMode, glutInitWindowSize, glutCreateWindow로 500x500 윈도우를 생성.

GLEW 초기화: OpenGL 3.0 지원 여부 확인.

Renderer 객체(g_Renderer)를 생성 → 실제 렌더링을 담당.

이벤트 함수 등록:

glutDisplayFunc(RenderScene)

glutIdleFunc(Idle)

glutKeyboardFunc(KeyInput)

glutMouseFunc(MouseInput)

glutSpecialFunc(SpecialKeyInput)

RenderScene(): 화면을 지우고(glClear) g_Renderer->DrawTest() 호출 → 삼각형 하나 그림.

이벤트 입력(Key/Mouse/Special Key)이 들어와도 결국 RenderScene()만 호출 → 지금은 단순히 다시 그리기만 함.

정리: GLUT + GLEW 초기화, Renderer를 불러서 그리는 틀 역할.
*/