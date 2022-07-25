#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//��������
//�ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//������⺯��
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure ��ʼ��������
	// ------------------------------
	glfwInit();																													//glfw��ʼ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);										//glfw�汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//����ģʽ

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw  window creation ��������
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);	//��������(���ߡ����ơ��ԡ���)
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();			//����ʧ�����������
		return -1;
	}
	glfwMakeContextCurrent(window);		//ʹָ�����ڵ������ĳ�Ϊ�����̵߳ĵ�ǰ������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);		//ע��ص�����(��ô����ѭ����?)

	// glad: load all OpenGL function pointers �������� OpenGL ����ָ��
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// render loop ��Ⱦѭ��
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);		//��յ���ɫ��������ɫ
		glClear(GL_COLOR_BUFFER_BIT);		//�����Ļ����ɫ����

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);					//������ɫ���壬����
		glfwPollEvents();									//����¼����������ö�Ӧ����
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();										//������������е�ǰGLFW��Դ
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)			//������⣬esc = �رմ���
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);		//��֤�ӿ�(Viewport)�ʹ��ڵ�ά��(Dimension)����Ӧ
}