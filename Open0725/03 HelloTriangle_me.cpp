#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
using namespace std;

//declaration
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

//Source
const char* vertextShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShader1Source =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.2f, 0.7f, 0.5f);\n"
"}\n\0";
const char* fragmentShader2Source = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.5f, 1.0f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	//Init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "114514", NULL, NULL);
	if (window == NULL)
	{
		cout << "创建窗体失败" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "初始化glad失败" << endl;
	}

	//Shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int shaderProgram1 = glCreateProgram();
	unsigned int shaderProgram2 = glCreateProgram();
	glShaderSource(vertexShader, 1, &vertextShaderSource, NULL);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmentShader1);
	glShaderSource(fragmentShader2, 1, &fragmentShader2Source, NULL);
	glCompileShader(fragmentShader2);
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(fragmentShader2);

	//vertex data
	float Triangle1[] = {
		-0.9f, -0.5f, 0.0f, 
		-0.0f, -0.5f, 0.0f,  
		-0.45f, 1.0f, 0.0f,  
	};
	float Triangle2[] = {
		0.0f, -0.5f, 0.0f,  
		0.9f, -0.5f, 0.0f,  
		0.45f, -1.0f, 0.0f   
	};

	//VBO&VAO
	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle1), Triangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle2), Triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw
		glUseProgram(shaderProgram1);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//swap buffer and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//delete VAO&VBO
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram1);
	glDeleteProgram(shaderProgram2);

	//terminate
	glfwTerminate();
	return 0;
}


//implementation
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
