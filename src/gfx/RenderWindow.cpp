#include "RenderWindow.h"

#define DEBUG_MODE
#include "../core/debug.h"

void RenderWindow::initGlfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
}
void RenderWindow::init_shaders() {
    // find all the shaders
    // RenderWindow::shaders[0] = NULL;

}
RenderWindow::RenderWindow(int width, int height, std::string name) {

    ASSERT(width > 0 && height > 0, "Invalid dimensions/name for window");

    d_width = width;
    d_height= height;
    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

    throw_if(window == NULL, "Failed to create glfw window");

    glfwMakeContextCurrent(window);


    int res = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    throw_if(res == 0, "Failed to load glad");


    glfwMakeContextCurrent(window);


    glViewport(0,0,height,width);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnable(GL_MULTISAMPLE);  
    // glEnable(GL_CULL_FACE);  
    std::cerr << d_width << " " << d_height << "\n";

}
void RenderWindow::init_callbacks() {

    /*
    RenderWindow* mywindow = this;

    auto func = (void (*) (GLFWwindow* w, int, int, int, int)) [](GLFWwindow* w, int key, int scancode, int action, int mods)
    {
        mywindow->key_callback(w, key, scancode, action, mods); 
    };
    glfwSetKeyCallback(window, func);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);
    */

}

void RenderWindow::render() {
    // render all renderables

    // generate camera stuff?
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) d_width / (float) d_height, 0.1f, 200.0f);

    glm::mat4 view = glm::lookAt(
        glm::vec3(1,1,0),
        glm::vec3(0,0,0),
        glm::vec3(0,1,0)

        );
    glm::mat4 Model = glm::mat4(1.0f);

    glm::mat4 transform = projection * view * glm::mat4(1.0f);

    glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, &transform[0][0]);


    std::cerr << glm::to_string(transform) << std::endl;

    // can put them all into temp rendering arrays
    // i think that is faster than binding a ton of vbos
    int cnt=0;
    for (auto prend : objects) {
        prend->render();
        // std::cout << "rendering " << ++cnt << std::endl;
    }

    // std::cout << "hi lol" << std::endl;
    // glVertexAttribPointer(0);
}

void RenderWindow::tick() {
    // poll the events
    // check for inputs mess w camera pos
    // also does interactions and movement here

    //
    // if ()



}
void RenderWindow::main_loop() {
    // adjust for camera new positions
    mvp_uniform = glGetUniformLocation(Shader::shaders[Shader::SHADER_DEFAULT]->get_program(), "mvp");
    std::cerr << mvp_uniform << " mvp uniform" << std::endl;

    auto prev = util::clock();
    while(!glfwWindowShouldClose(window))
    {
        auto now = util::clock();
        double elapsed = util::elapsed(prev, now);
        prev = util::clock();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);
        

        // should have time values no?
        this->tick();
        this->render();

      
        glfwSwapBuffers(window);

        glfwPollEvents();    
    }

}

void RenderWindow::init_test() {
    // add the render objects to the thing
    v3d a(-0.5,-0.5,0);
    v3d b(0.5, -0.5, 0.0);
    v3d c(0.0, 0.5, 0.0);
    v3d rgb(0.2, 0.6, 0.7);

    Triangle tri(a,b,c,rgb);


    v3d x(0.50,-.50,0.0);
    v3d y(0.30,.25,0.0);
    v3d z(-0.5, 0.5, 0.0);

    v3d col2(0.4, 0.2, 0.2);

    v3d col1(0.1, 0.9, 0.9);
    Triangle::Point x1(x, col1);
    Triangle::Point y1(y, col2);
    Triangle::Point z1(z, rgb);
    Triangle tri2(x1,y1,z1);
    // Triangle tri2(x,y,z,rgb);
    // std::cerr << tri2.a.vertex << " " << tri2.a.rgb << std::endl;
    // std::cerr << tri2.b.vertex << " " << tri2.b.rgb << std::endl;
    // std::cerr << tri2.c.vertex << " " << tri2.c.rgb << std::endl;

    // Triangle tri2(x,y,z,col1);

    // tri2.a.rgb = rgb;
    std::vector<Triangle> vec = {tri}, vec2 = {tri2};
    std::shared_ptr<Renderable> cool_triangle = std::make_shared<Renderable>(vec, Shader::shaders[Shader::SHADER_DEFAULT]);
    std::shared_ptr<Renderable> cool2 = std::make_shared<Renderable>(vec2, Shader::shaders[Shader::SHADER_DEFAULT]);

    objects.push_back(cool_triangle);
    objects.push_back(cool2);
    // objects.push_back(std::make_shared<Renderable>(vec2, Shader::shaders[Shader::SHADER_DEFAULT]));
}
