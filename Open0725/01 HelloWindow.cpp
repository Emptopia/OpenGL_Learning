#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//函数声明
//回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//按键检测函数
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure 初始化和设置
	// ------------------------------
	glfwInit();																													//glfw初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);										//glfw版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//核心模式

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw  window creation 创建窗口
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);	//创建窗体(宽、高、名称、略、略)
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();			//创建失败则结束程序
		return -1;
	}
	glfwMakeContextCurrent(window);		//使指定窗口的上下文成为调用线程的当前上下文
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);		//注册回调函数(怎么不放循环里?)

	// glad: load all OpenGL function pointers 加载所有 OpenGL 函数指针
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// render loop 渲染循环
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);		//清空的颜色：深蓝绿色
		glClear(GL_COLOR_BUFFER_BIT);		//清空屏幕的颜色缓冲

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);					//交换颜色缓冲，绘制
		glfwPollEvents();									//检查事件发生并调用对应函数
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();										//结束，清楚所有当前GLFW资源
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)			//按键检测，esc = 关闭窗口
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);		//保证视口(Viewport)和窗口的维度(Dimension)相适应
}