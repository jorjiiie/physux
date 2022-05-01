#include "RenderWindow.h"

#define DEBUG_MODE
#include "../core/debug.h"

void RenderWindow::initGlfw() {
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}
void RenderWindow::init_shaders() {
    // find all the shaders
    // RenderWindow::shaders[0] = NULL;

}
RenderWindow::RenderWindow(int width, int height, std::string name) {

	ASSERT(width > 0 && height > 0, "Invalid dimensions/name for window");
	
    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

    throw_if(window == NULL, "Failed to create glfw window");

	glfwMakeContextCurrent(window);


    int res = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    throw_if(res == 0, "Failed to load glad");


	glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glViewport(0,0,height,width);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}


void RenderWindow::main_loop() {

    while(!glfwWindowShouldClose(window))
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);
        
      
        glfwSwapBuffers(window);

        glfwPollEvents();    
    }


}

