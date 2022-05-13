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

    Global::window_map[window] = this;


    auto keycall = [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Global::window_map[window]->key_callback(window, key, scancode, action, mods); 
    };
    glfwSetKeyCallback(window, keycall);

    auto framebuffercall = [](GLFWwindow* window, int width, int height)
    {
        Global::window_map[window]->framebuffer_size_callback(window, width, height);
    };
    glfwSetFramebufferSizeCallback(window, framebuffercall);

    auto mousebuttoncall = [](GLFWwindow* window, int button, int action, int mods)
    {
        Global::window_map[window]->mouse_button_callback(window, button, action, mods);
    };
    glfwSetMouseButtonCallback(window, mousebuttoncall);


    auto cursorpositioncall = [](GLFWwindow* window, double x, double y) 
    {
        Global::window_map[window]->cursor_position_callback(window, x, y);
    };
    glfwSetCursorPosCallback(window, cursorpositioncall);
    
    auto scrollcall = [](GLFWwindow* window, double x, double y) 
    {
        Global::window_map[window]->scroll_callback(window, x, y);
    };
    glfwSetScrollCallback(window, scrollcall);

    camera_focus_length = 1;

    glfwGetCursorPos(window, &mouse_last[0], &mouse_last[1]);


    glEnable(GL_DEPTH_TEST);  
    glDepthFunc(GL_LESS);  

}

glm::vec3 RenderWindow::calculate_look() {
    return glm::vec3(cos(glm::radians(camera_phi)) * cos(glm::radians(camera_theta)),
                     cos(glm::radians(camera_phi)) * sin(glm::radians(camera_theta)),
                     sin(glm::radians(camera_phi))
                     );
}

void RenderWindow::render() {
    // render all renderables

    //clear z buffer


    // generate camera stuff?
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) d_width / (float) d_height, 0.1f, 200.0f);

    // std::cerr << glm::to_string(camera_focus_length * calculate_look() + camera_position) << "\n";
    
    glm::mat4 view = glm::lookAt(
        camera_position,
        camera_focus_length * calculate_look() + camera_position,
        camera_up
        );
        

    glm::mat4 transform = projection * view;
    glUseProgram(Shader::shaders[Shader::SHADER_DEFAULT]->get_program());

    glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, &transform[0][0]);


    // std::cerr << glm::to_string(transform[0]) << std::endl;

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
void RenderWindow::norm_no_up_axis(glm::vec3& vec) {
    // this just means no z, plus normalize
    vec.z = 0;
    vec = glm::normalize(vec);
}
void RenderWindow::tick() {
    // poll the events
    // check for inputs mess w camera pos
    // also does interactions and movement here

    current_tick++;

    // std::cerr << keyboard_buttons[GLFW_KEY_A] << " abc\n";
    if (keyboard_buttons[GLFW_KEY_A].pressed) {
        // move to the side, so cross look with up
        glm::vec3 side_vec = glm::cross(calculate_look(), camera_up);
        norm_no_up_axis(side_vec);
        std::cerr << glm::to_string(side_vec) << std::endl;
        camera_position += -side_vec * MOVEMENT_SPEED;
    }
    
    if (keyboard_buttons[GLFW_KEY_D].pressed) {
        glm::vec3 side_vec = glm::cross(calculate_look(), camera_up);
        norm_no_up_axis(side_vec);
        camera_position += side_vec * MOVEMENT_SPEED;
    }

    if (keyboard_buttons[GLFW_KEY_W].pressed) {
        glm::vec3 delta_vec = calculate_look();
        norm_no_up_axis(delta_vec);
        camera_position += delta_vec * MOVEMENT_SPEED;
    }

    if (keyboard_buttons[GLFW_KEY_S].pressed) {
        glm::vec3 delta_vec = calculate_look();
        norm_no_up_axis(delta_vec);
        camera_position += -delta_vec * MOVEMENT_SPEED;
    }

    if (keyboard_buttons[GLFW_KEY_LEFT_SHIFT].pressed) {
        camera_position += -camera_up * MOVEMENT_SPEED;
    }

    if (keyboard_buttons[GLFW_KEY_SPACE].pressed) {
        camera_position += camera_up * MOVEMENT_SPEED;
    }


    if (keyboard_buttons[GLFW_KEY_T].pressed && keyboard_buttons[GLFW_KEY_T].start_press + 30 > current_tick) {

        if (cursor_enabled)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        cursor_enabled = !cursor_enabled;

    }


    if (keyboard_buttons[GLFW_KEY_J].pressed) {
        // move the first thing by 10 or smth
        objects[0]->update_position(glm::vec3(1.0,1.0,1.0));
    }

    if (keyboard_buttons[GLFW_KEY_K].pressed) {
        objects[0]->update_position(glm::vec3(0.0,0.0,0.0));

    }


}
void RenderWindow::main_loop() {
    // adjust for camera new positions


    mvp_uniform = glGetUniformLocation(Shader::shaders[Shader::SHADER_DEFAULT]->get_program(), "camera_mat");
    std::cerr << mvp_uniform << " mvp uniform" << std::endl;

    auto prev = util::clock();
    while(!glfwWindowShouldClose(window))
    {
        auto now = util::clock();
        double elapsed = util::elapsed(prev, now);
        prev = util::clock();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        

        // should have time values no?
        this->tick();
        this->render();

      
        glfwSwapBuffers(window);

        glfwPollEvents();    
    }

}

void RenderWindow::init_test() {

    std::cerr << glm::to_string(glm::mat4(1.0f)) << std::endl;
    camera_position = glm::vec3(0,2,1);
    camera_up = glm::vec3(0,0,1);

    camera_theta = 0;
    camera_phi= 0;

    // add the render objects to the thing
    v3d a(-0.5,-0.5,1);
    v3d b(0.5, -0.5, 1.0);
    v3d c(0.0, 0.5, 1.0);
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

    v3d quad_a(1.0, 0, 5.0);
    v3d quad_b(1.0,2.0,5.0);
    v3d quad_d(1.0,0.0, 0.0);
    v3d quad_c(1.0, 2.0, 0.0);

    std::pair<Triangle, Triangle> mesh = ShapeFactory::generate_quad(quad_a,quad_b,quad_c,quad_d,col2);
    std::vector<Triangle> abcbc = {mesh.first, mesh.second};


    std::vector<Triangle> vec = {tri}, vec2 = {tri2};
    std::shared_ptr<Renderable> quad = std::make_shared<Renderable>(abcbc, Shader::shaders[Shader::SHADER_DEFAULT]);
    std::shared_ptr<Renderable> cool_triangle = std::make_shared<Renderable>(vec, Shader::shaders[Shader::SHADER_DEFAULT]);
    std::shared_ptr<Renderable> cool2 = std::make_shared<Renderable>(vec2, Shader::shaders[Shader::SHADER_DEFAULT]);

    // objects.push_back(cool_triangle);
    // objects.push_back(cool2);
    objects.push_back(quad);
    // objects.push_back(std::make_shared<Renderable>(vec2, Shader::shaders[Shader::SHADER_DEFAULT]));
}
