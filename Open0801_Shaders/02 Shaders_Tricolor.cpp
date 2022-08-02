#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//declare
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//shader source
const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"   // 位置变量的属性位置值为 0 
"layout(location = 1) in vec3 aColor;\n" // 颜色变量的属性位置值为 1
"out vec3 ourColor;\n" // 向片段着色器输出一个颜色
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos, 1.0);\n"
"    ourColor = aColor;\n" // 将ourColor设置为我们从顶点数据那里得到的输入颜色
"}\n";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(ourColor, 1.0);\n"
"}\n";

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);       //创建Shader对象
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);             //加入源码
    glCompileShader(vertexShader);                                                              //编译源码
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);         //检查是否编译成功
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);                //获取错误消息
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);       //创建Shader对象
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);             //加入源码
    glCompileShader(fragmentShader);                                                                    //编译源码
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);              //检查是否编译成功
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);                     //获取错误消息
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();             //创建着色器程序对象
    glAttachShader(shaderProgram, vertexShader);                    //附加
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);                                           //链接
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);        //检测链接着色器程序是否失败
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);         //获取错误消息
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);           //删除着色器对象
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        // 位置              // 颜色
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };

    unsigned int VBO, VAO;              //unsigned int 无符号整型 0~65535
    glGenVertexArrays(1, &VAO);     //生成VAO
    glGenBuffers(1, &VBO);              //生成VBO
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);                                     //绑定VAO

    glBindBuffer(GL_ARRAY_BUFFER, VBO);             //绑定VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);              //缓存顶点数据

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);       //解绑VBO             glVertexAttribPointer注册了VBO的顶点属性，可以安全解绑

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);                              //解绑VAO              防止其他VAO修改这个VAO，虽然很少发生，通常我们在没必要时不解绑以上二者


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);

        // 渲染
        // 清除颜色缓冲
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 记得激活着色器
        glUseProgram(shaderProgram);

        // 更新uniform颜色
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // 绘制三角形
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 交换缓冲并查询IO事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);          //删除VAO
    glDeleteBuffers(1, &VBO);                   //删除VBO
    glDeleteProgram(shaderProgram);     //删除程序对象

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}