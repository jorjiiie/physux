#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

/* garbage code but whatever */
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,

     1.0f, 1.0f, 0.0f,
     1.0f, -0.5f, 0.0f,
     0.5f, 0.0f, 0.0f
};
void modVertex(int x, float v) {
    printf("vertex 1 : %f %f %f\n", vertices[0], vertices[1], vertices[2]);
    if (x) {
        // modify x!
        for (int i=0;i<9;i+=3) {
            vertices[i] += v;
        }
    } else {
        for (int i=1;i<9;i+=3) {
            vertices[i] += v;
        }
    }
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // printf("hui %d %d %d %d\n", scancode, action, mods, key);
    // GLFWwindow* carl = window;
    // window = NULL;
    // window = carl;    
    printf("%d %d %d\n", action, GLFW_PRESS, action == GLFW_PRESS);
    fflush(stdout);
    // instead of this it should go until the thing is done
    // so we do have the other things lol
    //
    if (action != GLFW_PRESS && action != GLFW_REPEAT)
        return;

    printf("hello\n");
    fflush(stdout);
    switch (key) {
        case GLFW_KEY_A:
            modVertex(1,-0.1);
            break;
        case GLFW_KEY_D:
            modVertex(1,0.1);
            break;
        case GLFW_KEY_W:
            modVertex(0,0.1);
            break;
        case GLFW_KEY_S:
            modVertex(0,-0.1);

    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    GLFWwindow* carl = window;
    window = NULL;
    window = carl;
    glViewport(0, 0, width, height);
}  
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int msain()
{


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Physical Science :sunglasses:", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    glViewport(0, 0, 800, 600);
    glfwSetKeyCallback(window, glfwKeyCallback);



    /* more garbage */

    unsigned int VBO;
    GLuint vao;
    glGenBuffers(1, &VBO);  

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "float x = gl_FragCoord.y / 700.0f;"
        "FragColor = mix(vec4(0.3f, 0.5f, 0.8f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), x);\n"
    "} ";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        std::cout << "ASJDKLASJD\n";
        return 0;
    }
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    clock_t last = clock();
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClearColor(0.0f,0.0f,0.0f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(0);


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glUseProgram(0);

        glfwSwapBuffers(window);


        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // last = clock();
        glfwPollEvents();    
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  
    glfwTerminate();
    return 0;
}
