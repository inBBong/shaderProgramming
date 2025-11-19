#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	CompileAllShaderPrograms();
	
	//Create VBOs
	CreateVertexBufferObjects();
	CreateParticles(10000);
	CreateGridMesh(1000, 1000);
	if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}
	int index = 0;
	for (int i = 0; i < MAX_COUNTS; i++)
	{
		float x = 2*((float)rand() / RAND_MAX) - 1;
		float y = 2 * ((float)rand() / RAND_MAX) - 1;
		float sTime = 2 * ((float)rand() / RAND_MAX)*6;
		float lTime = 2 * ((float)rand() / RAND_MAX) * 0.5;
		m_Points[index] = x; index++;
		m_Points[index] = y; index++;
		m_Points[index] = sTime; index++;
		m_Points[index] = lTime; index++;
	}

	m_RGBTexture = CreatePngTexture("./Textures/rgb.png", GL_NEAREST);
	m_UsagiTexture = CreatePngTexture("./Textures/우사기.png", GL_NEAREST);
	m_0Texture = CreatePngTexture("./Textures/0.png", GL_NEAREST);
	m_1Texture = CreatePngTexture("./Textures/1.png", GL_NEAREST);
	m_2Texture = CreatePngTexture("./Textures/2.png", GL_NEAREST);
	m_3Texture = CreatePngTexture("./Textures/3.png", GL_NEAREST);
	m_4Texture = CreatePngTexture("./Textures/4.png", GL_NEAREST);
	m_5Texture = CreatePngTexture("./Textures/5.png", GL_NEAREST);
	m_6Texture = CreatePngTexture("./Textures/6.png", GL_NEAREST);
	m_7Texture = CreatePngTexture("./Textures/7.png", GL_NEAREST);
	m_8Texture = CreatePngTexture("./Textures/8.png", GL_NEAREST);
	m_9Texture = CreatePngTexture("./Textures/9.png", GL_NEAREST);
	m_TotalNumTexture= CreatePngTexture("./Textures/numbers.png", GL_NEAREST);

}

void Renderer::ReloadAllShaderPrograms()
{
	DeleteAllShaderPrograms();
	CompileAllShaderPrograms();
}

GLuint Renderer::CreatePngTexture(char* filePath, GLuint samplingMethod)
{
	//Load Png
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filePath);
	if (error != 0)
	{
		std::cout << "PNG image loading failed:" << filePath << std::endl;
		assert(0);
	}

	GLuint temp;
	glGenTextures(1, &temp);
	glBindTexture(GL_TEXTURE_2D, temp);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, &image[0]);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, samplingMethod);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplingMethod);

	return temp;
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::CreateVertexBufferObjects()
{
	float rect[]
		=
	{
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, -1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, //Triangle1
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f,  1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	float center = 0.5;
	float size = 0.1;
	float testPos[]
		=
	{
		(0 - center)* size,(0 - center)* size,0, 1,  //x, y, z, value
		(1 - center)* size,(0 - center)* size,0, 1,
		(1 - center)* size,(1 - center)* size,0, 1,
		(0 - center)* size,(0 - center)* size,0, 1,
		(1 - center)* size,(1 - center)* size,0, 1,
		(0 - center)* size,(1 - center)* size,0, 1,  //Quad1
		(0 - center)* size,(0 - center)* size,0, 0.5,  //x, y, z, value
		(1 - center)* size,(0 - center)* size,0, 0.5,
		(1 - center)* size,(1 - center)* size,0, 0.5,
		(0 - center)* size,(0 - center)* size,0, 0.5,
		(1 - center)* size,(1 - center)* size,0, 0.5,
		(0 - center)* size,(1 - center)* size,0, 0.5,  //Quad2
	};	
	
	glGenBuffers(1, &m_VBOTestRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(testPos), testPos, GL_STATIC_DRAW);
	
	
	float testColor[]
		=
	{
		1.f,0.f,0.f,1.f,
		0.f,1.f,0.f,1.f,
		0.f,0.f,1.f,1.f,
		1.f,0.f,0.f,1.f,
		0.f,1.f,0.f,1.f,
		0.f,0.f,1.f,1.f,
		1.f,0.f,0.f,1.f,
		0.f,1.f,0.f,1.f,
		0.f,0.f,1.f,1.f,
		1.f,0.f,0.f,1.f,
		0.f,1.f,0.f,1.f,
		0.f,0.f,1.f,1.f,
	};
	
	glGenBuffers(1, &m_VBOTestColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(testColor), testColor, GL_STATIC_DRAW);
	
	float fullRect[]
		=
	{
		-1,-1,0,1,1,0,-1,1,0,
		-1,-1,0,1,-1,0,1,1,0,
	};
	glGenBuffers(1, &m_FullScreenVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_FullScreenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullRect), fullRect, GL_STATIC_DRAW);

	float fullRectFS[] =
	{
	   -1,-1,0,0,1,
	   1,1,0,1,0,
	   -1,1,0,0,0,
	   -1,-1,0,0,1,
	   1,-1,0,1,1,
	   1,1,0,1,0,
	};

	glGenBuffers(1, &m_FSVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_FSVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullRectFS), fullRectFS, GL_STATIC_DRAW);

}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];

	size_t slen = strlen(pShaderText);
	if (slen > INT_MAX) {
		// Handle error
	}
	GLint len = (GLint)slen;

	Lengths[0] = len;
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram 에 attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

void Renderer::CompileAllShaderPrograms()
{
	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs",
		"./Shaders/SolidRect.fs");
	m_TestShader = CompileShaders("./Shaders/test.vs",
		"./Shaders/test.fs");
	m_ParticleShader = CompileShaders("./Shaders/Particle.vs",
		"./Shaders/Particle.fs");
	m_GridMeshShader = CompileShaders("./Shaders/GridMesh.vs",
		"./Shaders/GridMesh.fs");
	m_FullScreenShader = CompileShaders("./Shaders/FullScreen.vs",
		"./Shaders/FullScreen.fs");
	m_FSShader= CompileShaders("./Shaders/FS.vs",
		"./Shaders/FS.fs");
}

void Renderer::DeleteAllShaderPrograms()
{
	glDeleteShader(m_SolidRectShader);
	glDeleteShader(m_TestShader);
	glDeleteShader(m_GridMeshShader);
	glDeleteShader(m_GridMeshShader);
	glDeleteShader(m_ParticleShader);
	glDeleteShader(m_FSShader);
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}

void Renderer::DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a)
{
	float newX, newY;

	GetGLPosition(x, y, &newX, &newY);

	//Program select
	glUseProgram(m_SolidRectShader);

	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Trans"), newX, newY, 0, size);
	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Color"), r, g, b, a);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawTest()
{
	m_Time += 0.0016;
	
	//Program select
	glUseProgram(m_TestShader);	
	
	int uTimeLoc = glGetUniformLocation(m_TestShader, "u_Time");
	glUniform1f(uTimeLoc,m_Time);

	
	int attribPosition = glGetAttribLocation(m_TestShader, "a_Position");//x,y,z
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestRect);
	glVertexAttribPointer(attribPosition,
		3, GL_FLOAT, 
		GL_FALSE, sizeof(float) * 4,
		0);

	int aValueLoc = glGetAttribLocation(m_TestShader, "a_Value"); //value
	glEnableVertexAttribArray(aValueLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestRect);
	glVertexAttribPointer(aValueLoc,
		1, GL_FLOAT,				 //몇개씩 읽어오냐
		GL_FALSE, sizeof(float) * 4, //stride
		(GLvoid*)(sizeof(float)*3));//시작지점

	int aColorLoc = glGetAttribLocation(m_TestShader, "a_Color");
	glEnableVertexAttribArray(aColorLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestColor);
	glVertexAttribPointer(aColorLoc,
		4, GL_FLOAT, 
		GL_FALSE, sizeof(float) * 4, 
		0);

	glDrawArrays(GL_TRIANGLES, 0, 12);

	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(aColorLoc);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawParticle()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_Time += 0.016;

	//Program select
	GLuint shader = m_ParticleShader;
	glUseProgram(shader);

	int uTimeLoc = glGetUniformLocation(shader, "u_Time");
	int uForceLoc = glGetUniformLocation(shader, "u_Force");

	glUniform1f(uTimeLoc, m_Time);
	glUniform3f(uForceLoc, std::sin(m_Time) * 10.f, 0, 0);//-10~10

	int stride = 15;

	int attribPosition = glGetAttribLocation(shader, "a_Position");//x,y,z
	int aValueLoc = glGetAttribLocation(shader, "a_Value"); //value
	int aColorLoc = glGetAttribLocation(shader, "a_Color");
	int aSTime = glGetAttribLocation(shader, "a_STime");
	int aVelloc = glGetAttribLocation(shader, "a_Vel");
	int aLifeTimeLoc = glGetAttribLocation(shader, "a_LifeTime");
	int aMassLoc = glGetAttribLocation(shader, "a_Mass");
	int aPeriodLoc = glGetAttribLocation(shader, "a_Period");

	glEnableVertexAttribArray(attribPosition);
	glEnableVertexAttribArray(aValueLoc);
	glEnableVertexAttribArray(aColorLoc);
	glEnableVertexAttribArray(aSTime);
	glEnableVertexAttribArray(aVelloc);
	glEnableVertexAttribArray(aLifeTimeLoc);
	glEnableVertexAttribArray(aMassLoc);
	glEnableVertexAttribArray(aPeriodLoc);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticles);
	glVertexAttribPointer(attribPosition,
		3, GL_FLOAT,
		GL_FALSE, sizeof(float) * stride,
		0);

	glVertexAttribPointer(aValueLoc,
		1, GL_FLOAT,				 //몇개씩 읽어오냐
		GL_FALSE, sizeof(float) * stride, //stride
		(GLvoid*)(sizeof(float) * 3));//시작지점

	glVertexAttribPointer(aColorLoc,
		4, GL_FLOAT,
		GL_FALSE, sizeof(float) * stride,
		(GLvoid*)(sizeof(float) * 4));

	glVertexAttribPointer(aSTime,
		1, GL_FLOAT,
		GL_FALSE, sizeof(float) * stride,
		(GLvoid*)(sizeof(float) * 8));

	glVertexAttribPointer(aVelloc,
		3, GL_FLOAT,
		GL_FALSE, sizeof(float) * stride,
		(GLvoid*)(sizeof(float) * 9));
	glVertexAttribPointer(aLifeTimeLoc,
		1, GL_FLOAT,
		GL_FALSE, sizeof(float) * stride,
		(GLvoid*)(sizeof(float) * 12));

	glVertexAttribPointer(aMassLoc,
		1, GL_FLOAT,
		GL_FALSE, sizeof(float) * stride,
		(GLvoid*)(sizeof(float) * 13));
	glVertexAttribPointer(aPeriodLoc,
		1, GL_FLOAT,
		GL_FALSE, sizeof(float) * stride,
		(GLvoid*)(sizeof(float) * 14));

	glDrawArrays(GL_TRIANGLES, 0, m_VBOParticlesVertexCount);

	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(aValueLoc);
	glDisableVertexAttribArray(aColorLoc);
	glDisableVertexAttribArray(aSTime);
	glDisableVertexAttribArray(aVelloc);
	glDisableVertexAttribArray(aLifeTimeLoc);
	glDisableVertexAttribArray(aMassLoc); 
	glDisableVertexAttribArray(aPeriodLoc);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_BLEND);
}

void Renderer::DrawGridMesh()
{
	m_Time += 0.016;
	int shader = m_GridMeshShader;
	int uSampler = glGetUniformLocation(shader, "u_Texture");
	glUniform1i(uSampler, 0);
	glBindTexture(GL_TEXTURE_2D, m_UsagiTexture);
	//glBindTexture(GL_TEXTURE_2D, m_RGBTexture);
	//Program select
	glUseProgram(shader);
	int uTimeLoc = glGetUniformLocation(shader, "u_Time");
	glUniform1f(uTimeLoc, m_Time);
	
	int uPointsLoc = glGetUniformLocation(shader, "u_Points");
	glUniform4fv(uPointsLoc,500, m_Points);

	int uDropCountLoc = glGetUniformLocation(shader, "u_DropCount");
	glUniform1i(uDropCountLoc,m_DropCount);

	int attribPosition = glGetAttribLocation(shader, "a_Position");//x,y,z
	glEnableVertexAttribArray(attribPosition);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_GridMeshVBO);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, m_GridMeshVertexCount);

	glDisableVertexAttribArray(attribPosition);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawFullScreenColor(float r, float g, float b, float a)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int shader = m_FullScreenShader;
	glUseProgram(shader);
	
	glUniform4f(glGetUniformLocation(shader, "u_Color"), r, g, b, a);

	int attribPosition = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_FullScreenVBO);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawFS()
{
	m_Time += 0.016;
	int number = (int)floor(m_Time)%10;
	int shader = m_FSShader;
	glUseProgram(shader);

	int uTimeLoc = glGetUniformLocation(shader, "u_Time");
	glUniform1f(uTimeLoc, m_Time);
	int uSampler = glGetUniformLocation(shader, "u_RGBTexture");
	glUniform1i(uSampler, 0);
	int uSamplerNum = glGetUniformLocation(shader, "u_NumTexture");
	glUniform1i(uSamplerNum, 2+number);
	int uSamplerTotalNum = glGetUniformLocation(shader, "u_TotalNumTexture");
	glUniform1i(uSamplerTotalNum, 12);
	int uSamplerNumber = glGetUniformLocation(shader, "u_Number");
	glUniform1i(uSamplerNumber, 5123);
	


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_RGBTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_UsagiTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_0Texture);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_1Texture);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, m_2Texture);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, m_3Texture);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, m_4Texture);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, m_5Texture);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, m_6Texture);
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, m_7Texture);
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, m_8Texture);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, m_9Texture);
	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_2D, m_TotalNumTexture);
	
	

	int attribPosition = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_FSVBO);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	int attribTexPosition = glGetAttribLocation(shader, "a_TexPos");
	glEnableVertexAttribArray(attribTexPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_FSVBO);
	glVertexAttribPointer(attribTexPosition, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Renderer::GetGLPosition(float x, float y, float *newX, float *newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}

void Renderer::CreateParticles(int Count)
{
	int particleCounts = Count; //파티클 개수 
	int verticesCount = particleCounts * 6;//버텍스 개수
	int floatCountsPerVertex = 3 + 1 + 4 + 1 + 3 + 1 + 1 + 1;//array에서 Index를 계산하기 위함 x,y,z,value,r,g,b,a, startTime, vx, vy, vz, LifeTime, mass , period
	int totalfloatCounts = floatCountsPerVertex * verticesCount; //버텍스당 필요한 정보의 수
	int floatCountsPerParticle = floatCountsPerVertex* 6;

	float* temp = NULL;
	temp = new float[totalfloatCounts];
	for (int i = 0; i < particleCounts; i++)
	{
		float size = 0.01 * (float)rand() / (float)RAND_MAX;//0.001~0.01
		float centerX = 0;//((float)rand() / (float)RAND_MAX)* 2.f-1.f;
		float centerY = 0;//((float)rand() / (float)RAND_MAX) * 2.f - 1.f;
		float value = (float)rand() / (float)RAND_MAX;//0~1
		float r= ((float)rand() / (float)RAND_MAX);//0~1
		float g= ((float)rand() / (float)RAND_MAX);//0~1
		float b= ((float)rand() / (float)RAND_MAX);//0~1
		float a = ((float)rand() / (float)RAND_MAX);//0~1
		float sTime = ((float)rand() / (float)RAND_MAX) * 2.f;//0~2
		float vx = /*0.f;*/ (((float)rand() / (float)RAND_MAX) * 2.f - 1.f)*5;//-5~5
		float vy = /*0.f;*/ ((float)rand() / (float)RAND_MAX) * 5;//0~5
		float vz = 0.f;

		float LifeTime = ((float)rand() / (float)RAND_MAX)*1.5f;    //0~1.5

		float mass = (((float)rand() / (float)RAND_MAX)) * 1.f + 1.f; //1~2
		float period = (((float)rand() / (float)RAND_MAX));				//0~1

		int Index = i * floatCountsPerParticle;
		temp[Index] = centerX - size; Index++;//x
		temp[Index] = centerY - size; Index++;//y
		temp[Index] = 0; Index++;//z
		temp[Index] = value; Index++;//value
		temp[Index] = r; Index++;//r
		temp[Index] = g; Index++;//g
		temp[Index] = b; Index++;//b
		temp[Index] = a; Index++;//a
		temp[Index] = sTime; Index++;//sTime
		temp[Index] = vx; Index++;//vx
		temp[Index] = vy; Index++;//vy
		temp[Index] = vz; Index++;//vz
		temp[Index] = LifeTime; Index++;
		temp[Index] = mass; Index++;
		temp[Index] = period; Index++;

		temp[Index] = centerX + size; Index++;
		temp[Index] = centerY + size; Index++;
		temp[Index] = 0; Index++;
		temp[Index] = value; Index++;
		temp[Index] = r; Index++;//r
		temp[Index] = g; Index++;//g
		temp[Index] = b; Index++;//b
		temp[Index] = a; Index++;//a
		temp[Index] = sTime; Index++;//sTime
		temp[Index] = vx; Index++;//vx
		temp[Index] = vy; Index++;//vy
		temp[Index] = vz; Index++;//vz
		temp[Index] = LifeTime; Index++;
		temp[Index] = mass; Index++;
		temp[Index] = period; Index++;

		temp[Index] = centerX - size; Index++;
		temp[Index] = centerY + size; Index++;
		temp[Index] = 0; Index++;
		temp[Index] = value; Index++;
		temp[Index] = r; Index++;//r
		temp[Index] = g; Index++;//g
		temp[Index] = b; Index++;//b
		temp[Index] = a; Index++;//a
		temp[Index] = sTime; Index++;//sTime
		temp[Index] = vx; Index++;//vx
		temp[Index] = vy; Index++;//vy
		temp[Index] = vz; Index++;//vz
		temp[Index] = LifeTime; Index++;
		temp[Index] = mass; Index++;
		temp[Index] = period; Index++;

		temp[Index] = centerX - size; Index++;
		temp[Index] = centerY - size; Index++;
		temp[Index] = 0; Index++;
		temp[Index] = value; Index++;
		temp[Index] = r; Index++;//r
		temp[Index] = g; Index++;//g
		temp[Index] = b; Index++;//b
		temp[Index] = a; Index++;//a
		temp[Index] = sTime; Index++;//sTime
		temp[Index] = vx; Index++;//vx
		temp[Index] = vy; Index++;//vy
		temp[Index] = vz; Index++;//vz
		temp[Index] = LifeTime; Index++;
		temp[Index] = mass; Index++;
		temp[Index] = period; Index++;

		temp[Index] = centerX + size; Index++;
		temp[Index] = centerY - size; Index++;
		temp[Index] = 0; Index++;
		temp[Index] = value; Index++;
		temp[Index] = r; Index++;//r
		temp[Index] = g; Index++;//g
		temp[Index] = b; Index++;//b
		temp[Index] = a; Index++;//a
		temp[Index] = sTime; Index++;//sTime
		temp[Index] = vx; Index++;//vx
		temp[Index] = vy; Index++;//vy
		temp[Index] = vz; Index++;//vz
		temp[Index] = LifeTime; Index++;
		temp[Index] = mass; Index++;
		temp[Index] = period; Index++;

		temp[Index] = centerX + size; Index++;
		temp[Index] = centerY + size; Index++;
		temp[Index] = 0; Index++;
		temp[Index] = value; Index++;
		temp[Index] = r; Index++;//r
		temp[Index] = g; Index++;//g
		temp[Index] = b; Index++;//b
		temp[Index] = a; Index++;//a
		temp[Index] = sTime; Index++;//sTime
		temp[Index] = vx; Index++;//vx
		temp[Index] = vy; Index++;//vy
		temp[Index] = vz; Index++;//vz
		temp[Index] = LifeTime; Index++;
		temp[Index] = mass; Index++;
		temp[Index] = period; Index++;

	}

	glGenBuffers(1, &m_VBOParticles);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticles);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(float)*totalfloatCounts, 
		temp, GL_STATIC_DRAW);
	delete[] temp;	
	m_VBOParticlesVertexCount = verticesCount;
}
void Renderer::CreateGridMesh(int x, int y)

{

	float basePosX = -1.f;

	float basePosY = -1.f;

	float targetPosX = 1.f;

	float targetPosY = 1.f;



	int pointCountX = x;

	int pointCountY = y;



	float width = targetPosX - basePosX;

	float height = targetPosY - basePosY;



	float* point = new float[pointCountX * pointCountY * 2];

	float* vertices = new float[(pointCountX - 1) * (pointCountY - 1) * 2 * 3 * 3];

	m_GridMeshVertexCount = (pointCountX - 1) * (pointCountY - 1) * 2 * 3;



	//Prepare points

	for (int x = 0; x < pointCountX; x++)

	{

		for (int y = 0; y < pointCountY; y++)

		{

			point[(y * pointCountX + x) * 2 + 0] = basePosX + width * (x / (float)(pointCountX - 1));

			point[(y * pointCountX + x) * 2 + 1] = basePosY + height * (y / (float)(pointCountY - 1));

		}

	}



	//Make triangles

	int vertIndex = 0;

	for (int x = 0; x < pointCountX - 1; x++)

	{

		for (int y = 0; y < pointCountY - 1; y++)

		{

			//Triangle part 1

			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + x) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + x) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;



			//Triangle part 2

			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;

			vertices[vertIndex] = point[(y * pointCountX + (x + 1)) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[(y * pointCountX + (x + 1)) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;

		}

	}



	glGenBuffers(1, &m_GridMeshVBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_GridMeshVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (pointCountX - 1) * (pointCountY - 1) * 2 * 3 * 3, vertices, GL_STATIC_DRAW);

	delete[] point;
	delete[] vertices;

}


/*초기화 (Initialize)

윈도우 크기 저장

셰이더 프로그램 컴파일 (SolidRect.vs, SolidRect.fs)

VBO(Rectangle, Test 삼각형) 생성

성공 여부 확인 후 m_Initialized = true

VBO 생성 (CreateVertexBufferObjects)

사각형: 두 개의 삼각형으로 정의.

삼각형 (Test용): (0,0,0), (1,0,0), (1,1,0)

셰이더 관련

ReadFile : 텍스트 파일 읽기

AddShader : 셰이더 소스를 OpenGL 객체에 attach

CompileShaders : 버텍스 & 프래그먼트 셰이더를 로드, attach, 링크 후 프로그램 반환

렌더링

DrawSolidRect(x, y, z, size, r,g,b,a)

좌표 변환, 색상/변환값 uniform으로 전달

m_VBORect 바인딩 후 그리기

DrawTest()

m_VBOTestRect 삼각형 바인딩 후 그리기

현재 SimpleGame.cpp에서 이 함수만 호출됨 → 삼각형 하나 그려줌*/