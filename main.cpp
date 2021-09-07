#include "Game.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//freetype
#include <ft2build.h>
#include FT_FREETYPE_H

#include <vector>
#include <thread>
#include <chrono>

float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��

int SCR_WIDTH = 900, SCR_HEIGHT = 600, fps = 240;

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) //__FILE__��__LINE__������Ԥ����ָ����ڱ����ʱ���滻�ɱ���ʱ��Ӧ���ļ����к�


int main()
{
	//��ʼ��GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //���汾������Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //�ΰ汾������Ϊ3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //ʹ�ú���ģʽ�����������ݣ�
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //ʹ��Macos

	//��������
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	//glfwSetCursorPosCallback(window, mouse_callback);//���ص�����

	//��ʼ��GLAD����ΪGLAD����������OpenGL����ָ��ģ����Ե����κ�OpenGL������Ҫ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//�����ӿ�
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);//ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
	//ʵ����Ҳ���Խ��ӿڵ�ά������Ϊ��GLFW ��ά��С��������֮�����е�OpenGL��Ⱦ������һ����С�Ĵ�������ʾ��
	//�����ӵĻ�����Ҳ���Խ�һЩ����Ԫ����ʾ��OpenGL�ӿ�֮�⡣

	Game myGame;
	myGame.GameInit(SCR_WIDTH, SCR_HEIGHT);
	myGame.MapLoad("one.lvl");

	
	glCheckError();

	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		myGame.ProcessInput(window);

		// �����ɫ�������Ȼ���
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myGame.update(deltaTime);
		myGame.Rend();


		glfwSwapBuffers(window);//������ɫ����
		glfwPollEvents();//����Ƿ��д����¼�(����������롢����ƶ��ȣ�
		std::this_thread::sleep_for(std::chrono::milliseconds(int(1000/fps)));
	}

	// �������е���Դ����ȷ�˳�����
	glfwTerminate();

	return 0;
}

GLenum glCheckError_(const char *file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}