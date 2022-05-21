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

void RenderWindow::add_particle(std::shared_ptr<Particle>& particle) {
    // add to set and logger
    std::cerr << "adding particle" << std::endl;
    scene_objects.insert(particle);
    logger.attach(particle);
}
void RenderWindow::remove_particle(std::shared_ptr<Particle>& particle) {
    // remove from set and logger
    std::cerr << "removing particle" << std::endl;
    scene_objects.erase(particle);
    logger.remove(particle);
}

glm::vec3 RenderWindow::calculate_look() {
    return glm::vec3(cos(glm::radians(camera_phi)) * cos(glm::radians(camera_theta)),
                     cos(glm::radians(camera_phi)) * sin(glm::radians(camera_theta)),
                     sin(glm::radians(camera_phi))
                     );
}

void RenderWindow::render() {
    // render all renderables

    // generate camera stuff
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) d_width / (float) d_height, 0.1f, 200.0f);
    
    glm::mat4 view = glm::lookAt(
        camera_position,
        camera_focus_length * calculate_look() + camera_position,
        camera_up
        );
        

    glm::mat4 transform = projection * view;
    glUseProgram(Shader::shaders[Shader::SHADER_DEFAULT]->get_program());

    glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, &transform[0][0]);


    
    for (auto prend : scene_objects) 
        prend->mesh->render();
    
    
    // render non-tangibles
    for (auto prend : objects) 
        prend->render();
    

}
void RenderWindow::norm_no_up_axis(glm::vec3& vec) {
    // this just means no z, plus normalize
    // the proper way to do this would be to find the complement of the vector projected onto the up axis and normalize it
    vec.z = 0;
    vec = glm::normalize(vec);
}

void RenderWindow::physics_tick() {

    for (auto pobj : scene_objects) {
        v3d cumulative_field(0,0,0);
        for (auto pobj_ : scene_objects) {
            if (pobj == pobj_)
                continue;
            cumulative_field += pobj_->physics->get_electric_field(*(pobj->physics));
        }

        pobj->physics->apply_field(cumulative_field);
        pobj->physics->apply_magnetic(magnetic_field);
    }

    std::vector<std::shared_ptr<Particle> > to_remove;

    //heterogenous data types of the same type :skull:
    v3d cam_pos_tmp(camera_position.x, camera_position.y, camera_position.z);

    for (auto pobj : scene_objects) {

        pobj->tick();

        v3d r = cam_pos_tmp - pobj->physics->get_pos();

        // if more than 1000 units away, remove
        if (r.dot(r) > 1000000.0) {
            to_remove.push_back(pobj);
        }
    }

    logger.log_data();

    for (auto pobj : to_remove) {
        remove_particle(pobj);
    }
}

void RenderWindow::tick() {
    // poll the events
    // check for inputs mess w camera pos
    // also does interactions and movement here

    current_tick++;

    // should have submethods for "press and hold", "single press" and "pressed" to make this more readable
    // is_pressed_and_hold(key, seconds), is_pressed_single(key), is_pressed(key)

    // movement checks
    glm::vec3 movement_vector(0,0,0);

    if (keyboard_buttons[GLFW_KEY_A].pressed) {
        // move to the side, so cross look with up
        glm::vec3 side_vec = glm::cross(calculate_look(), camera_up);
        norm_no_up_axis(side_vec);
        movement_vector += -side_vec * MOVEMENT_SPEED;
    }
    
    if (keyboard_buttons[GLFW_KEY_D].pressed) {
        glm::vec3 side_vec = glm::cross(calculate_look(), camera_up);
        norm_no_up_axis(side_vec);
        movement_vector += side_vec * MOVEMENT_SPEED;
    }

    if (keyboard_buttons[GLFW_KEY_W].pressed) {
        glm::vec3 delta_vec = calculate_look();
        norm_no_up_axis(delta_vec);
        movement_vector += delta_vec * MOVEMENT_SPEED;
    }

    if (keyboard_buttons[GLFW_KEY_S].pressed) {
        glm::vec3 delta_vec = calculate_look();
        norm_no_up_axis(delta_vec);
        movement_vector += -delta_vec * MOVEMENT_SPEED;
    }

    if (keyboard_buttons[GLFW_KEY_LEFT_SHIFT].pressed) {
        movement_vector += -camera_up * MOVEMENT_SPEED;
    }

    if (keyboard_buttons[GLFW_KEY_SPACE].pressed) {
        movement_vector += camera_up * MOVEMENT_SPEED;
    }


    // control check
    if (keyboard_buttons[GLFW_KEY_T].pressed && !keyboard_buttons[GLFW_KEY_T].held) {
        keyboard_buttons[GLFW_KEY_T].held = true;

        if (cursor_enabled)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        cursor_enabled = !cursor_enabled;

    }

    // speed up & pause
    int time_steps = 1;

    if (keyboard_buttons[GLFW_KEY_0].pressed && !keyboard_buttons[GLFW_KEY_0].held) {
        keyboard_buttons[GLFW_KEY_0].held = true;
        paused = !paused;
    }

    if (keyboard_buttons[GLFW_KEY_2].pressed) {
        time_steps = 200;
    }

    // have a key check for the advance one frame

    bool advance_one = false;

    if (keyboard_buttons[GLFW_KEY_PERIOD].pressed && !keyboard_buttons[GLFW_KEY_PERIOD].held) {
        keyboard_buttons[GLFW_KEY_PERIOD].held = true;

        advance_one = true;
    }
    if (keyboard_buttons[GLFW_KEY_PERIOD].pressed && keyboard_buttons[GLFW_KEY_PERIOD].start_press + 60 < current_tick) {
        advance_one = true;
        Global::TIME_STEP = Global::DEFAULT_TIME_STEP * 0.5;
    }
    int movement_cycles = 1;
    if (keyboard_buttons[GLFW_KEY_F].pressed) {
        keyboard_buttons[GLFW_KEY_F].held = true;
        movement_cycles = 10;
    }


    // add a particle 
    if (keyboard_buttons[GLFW_KEY_C].pressed && !keyboard_buttons[GLFW_KEY_C].held) {
        keyboard_buttons[GLFW_KEY_C].held = true;

        std::shared_ptr<Particle> to_add = std::make_shared<Particle>(-5,1, 0.5);
        glm::vec3 particle_position = calculate_look() + camera_position;
        to_add->set_position(v3d(particle_position.x, particle_position.y, particle_position.z));
        add_particle(to_add);
    }


    if (!paused || advance_one) {
        while (time_steps--) {
            physics_tick();
            current_time += Global::TIME_STEP;
        }
    }
    while (movement_cycles--) {
        camera_position += movement_vector;
    }

    Global::TIME_STEP = Global::DEFAULT_TIME_STEP;


}
void RenderWindow::main_loop() {
    // adjust for camera new positions

    camera_position = glm::vec3(0,2,1);
    camera_up = glm::vec3(0,0,1);

    camera_theta = 0;
    camera_phi= 0;


    mvp_uniform = glGetUniformLocation(Shader::shaders[Shader::SHADER_DEFAULT]->get_program(), "camera_mat");

    auto prev = util::clock();
    while(!glfwWindowShouldClose(window))
    {
        auto now = util::clock();
        double elapsed = util::elapsed(prev, now);
        prev = util::clock();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        

        this->tick();
        this->render();

      
        glfwSwapBuffers(window);

        glfwPollEvents();    
    }

}

void RenderWindow::set_magnetic_field(const v3d& field) {
    magnetic_field = field;
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



    ShapeFactory::generate_sphere(5.0, v3d(0,0,0), 11, 10, v3d(1.0,1,1));
    v3d quad_a(1.0, 0, 5.0);
    v3d quad_b(1.0,2.0,5.0);
    v3d quad_d(1.0,0.0, 0.0);
    v3d quad_c(1.0, 2.0, 0.0);

    std::pair<Triangle, Triangle> mesh = ShapeFactory::generate_quad(quad_a,quad_b,quad_c,quad_d,col2);
    std::vector<Triangle> abcbc = {mesh.first, mesh.second};


    std::vector<Triangle> sphere = ShapeFactory::generate_sphere(0.5, v3d(0,0,0), 63, 63, v3d(1,.65,.65));
    std::cerr << "how many triangles? " << sphere.size() << " triangles!\n";
    std::vector<Triangle> vec = {tri}, vec2 = {tri2};
    std::shared_ptr<Renderable> quad = std::make_shared<Renderable>(abcbc, Shader::shaders[Shader::SHADER_DEFAULT]);
    std::shared_ptr<Renderable> cool_triangle = std::make_shared<Renderable>(vec, Shader::shaders[Shader::SHADER_DEFAULT]);
    std::shared_ptr<Renderable> cool2 = std::make_shared<Renderable>(vec2, Shader::shaders[Shader::SHADER_DEFAULT]);

    std::shared_ptr<Renderable> cool3 = std::make_shared<Renderable>(sphere, Shader::shaders[Shader::SHADER_DEFAULT]);
    // objects.push_back(cool_triangle);
    // objects.push_back(cool2);
    objects.push_back(cool3);
    // objects.push_back(std::make_shared<Renderable>(vec2, Shader::shaders[Shader::SHADER_DEFAULT]));
}

void RenderWindow::test2() {

    std::shared_ptr<Particle> p = std::make_shared<Particle>(5,1,.5);
    std::shared_ptr<Particle> p3 = std::make_shared<Particle>(-5, 1, .5);

    std::shared_ptr<Particle> p2 = std::make_shared<Particle>(10, 3, .6);

    p3->set_position(v3d(1,1,0));
    p2->set_position(v3d(20,20,0));
    p->physics->make_static();
    p3->physics->make_static();
    // std::cerr << "CHARGE: " << p3.physics->get_electric_field(*(p.physics)) << "\n";
    // p.physics->apply_field(p3.physics->get_electric_field(*(p.physics)));
    // p.tick();
    // p.log_dbg();
    scene_objects.insert(p);
    scene_objects.insert(p3);

    add_particle(p2);

}

void RenderWindow::magnetic_field_test() {
    std::shared_ptr<Particle> p = std::make_shared<Particle>(5,1,0.5);

    p->physics->set_velocity(v3d(0.02,0,0));


    set_magnetic_field(v3d(0,1,0));

    add_particle(p);

}


