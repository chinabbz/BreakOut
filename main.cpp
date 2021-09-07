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

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

int SCR_WIDTH = 900, SCR_HEIGHT = 600, fps = 240;

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) //__FILE__和__LINE__这两个预处理指令，会在编译的时候被替换成编译时对应的文件与行号


int main()
{
	//初始化GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //主版本号设置为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //次版本号设置为3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //使用核心模式（无需向后兼容）
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //使用Macos

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//通知GLFW将我们窗口的上下文设置为当前线程的主上下文
	//glfwSetCursorPosCallback(window, mouse_callback);//光标回调函数

	//初始化GLAD，因为GLAD是用来管理OpenGL函数指针的，所以调用任何OpenGL函数都要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//创建视口
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);//前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
	//实际上也可以将视口的维度设置为比GLFW 的维度小，这样子之后所有的OpenGL渲染将会在一个更小的窗口中显示，
	//这样子的话我们也可以将一些其它元素显示在OpenGL视口之外。

	Game myGame;
	myGame.GameInit(SCR_WIDTH, SCR_HEIGHT);
	myGame.MapLoad("one.lvl");

	
	glCheckError();

	// 渲染循环
	while (!glfwWindowShouldClose(window)) {

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		myGame.ProcessInput(window);

		// 清空颜色缓冲和深度缓冲
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myGame.update(deltaTime);
		myGame.Rend();


		glfwSwapBuffers(window);//交换颜色缓冲
		glfwPollEvents();//检查是否有触发事件(比如键盘输入、鼠标移动等）
		std::this_thread::sleep_for(std::chrono::milliseconds(int(1000/fps)));
	}

	// 清理所有的资源并正确退出程序
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