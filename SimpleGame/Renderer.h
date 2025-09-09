#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	void DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a);
	void DrawTest();

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();
	void GetGLPosition(float x, float y, float *newX, float *newY);

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_VBOTestRect = 0;
	GLuint m_SolidRectShader = 0;
};

/*렌더링을 담당하는 Renderer 클래스 정의.

주요 기능:

Initialize() : 셰이더 로드, VBO 생성

DrawSolidRect() : 사각형을 화면에 그림

DrawTest() : 테스트용 삼각형 그림

CompileShaders() : 버텍스/프래그먼트 셰이더 컴파일 & 링크

ReadFile() : 셰이더 소스 파일 읽기

AddShader() : 개별 셰이더 attach

CreateVertexBufferObjects() : VBO 생성 (사각형, 삼각형)

GetGLPosition() : 윈도우 좌표 → OpenGL 좌표 변환*/