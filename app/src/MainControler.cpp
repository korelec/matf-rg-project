//
// Created by tea on 4/5/26.
//

#include "../include/MainControler.hpp"
#include <GuiControler.hpp>
#include <GuiLightController.hpp>
#include <engine/graphics/Camera.hpp>

#include <engine/graphics/GraphicsController.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>
#include <spdlog/spdlog.h>

namespace engine::app {

    class MainPlatformEventObserver : public engine::platform::PlatformEventObserver {
    public:
        void on_mouse_move(engine::platform::MousePosition position) override;
        void on_scroll(platform::MousePosition position) override;
    };

    void MainPlatformEventObserver::on_mouse_move(engine::platform::MousePosition position) {
        auto gui_controller=engine::core::Controller::get<GUIController>();
        if (!gui_controller->is_enabled()) {
            auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
            camera->rotate_camera(position.dx, position.dy);

        }
    }

    void MainPlatformEventObserver::on_scroll(engine::platform::MousePosition position) {
        auto gui = engine::core::Controller::get<GUIController>();
        if (!gui->is_enabled()) {
            auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
            camera->zoom(position.y);
        }
    }

    void MainController::initialize() {
        engine::graphics::OpenGL::enable_depth_testing();

        auto camera=engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
        camera->Position=glm::vec3(-20.0,4.0,-4.0);
        camera->Yaw=5.0;
        camera->Pitch=-3.5;
        camera->rotate_camera(0.0f,0.0f);
    }

    bool MainController::loop() {
        const auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if (platform->key(engine::platform::KEY_ESCAPE).state() == engine::platform::Key::State::JustPressed) {
            return false;
        }
        return true;
    }

    void MainController::poll_events() {
    }

    void MainController::update() {
        update_camera();
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    void MainController::define_light(engine::resources::Shader *shader) {
        auto graphics= engine::core::Controller::get<engine::graphics::GraphicsController>();
        shader->use();

        auto guilight=engine::core::Controller::get<engine::app::GUILightController>();
        shader->set_vec3 ("fire.position",glm::vec3(0.0f, 1.25f, 0.0f));
        //shader->set_vec3 ("fire.color",glm::vec3(1.0f, 0.75f, 0.75f));
        shader->set_vec3("fire.color",guilight->colorfire());
        shader->set_float("fire.specStrength",guilight->strengthfire());
        shader->set_float("fire.ambientStrength",guilight->strengthfire());
        //shader->set_float("fire.ambientStrength", 0.2f);
        //shader->set_float("fire.specStrength",    0.5f);

        shader->set_vec3 ("moon.direction",glm::vec3(0.3f, 0.8f, 0.4f));
        shader->set_vec3 ("moon.color",glm::vec3(0.55f, 0.6f, 0.75f));
        shader->set_float("moon.ambientStrength", 0.08f);
        shader->set_float("moon.specStrength",    0.3f);

        shader->set_vec3("viewPos",graphics->camera()->Position);
    }


    void MainController::draw_firepit() {
        //model
        auto resources            = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics             = engine::core::Controller::get<engine::graphics::GraphicsController>();
        resources::Model *firepit = resources->model("firepit");
        resources::Shader* shader=resources->shader("first");
        define_light(shader);
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model           = glm::scale(model, glm::vec3(0.3f));
        shader->set_mat4("model", model);
        firepit->draw(shader);
    }

void MainController::draw_fire() {
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics  = engine::core::Controller::get<engine::graphics::GraphicsController>();

        resources::Model *fire  = resources->model("fire");
        resources::Shader *shader = resources->shader("fire");

        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        shader->set_float("time",platform->frame_time().current);

        auto guilight=engine::core::Controller::get<engine::app::GUILightController>();
        shader->set_float("brightness",guilight->strengthfire());
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.25f, 0.0f));
        model = glm::scale(model, glm::vec3(6.0f));
        shader->set_mat4("model", model);

        fire->draw(shader);
    }


void MainController::draw_log1() {
        //model
        auto resources            = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics             = engine::core::Controller::get<engine::graphics::GraphicsController>();
        resources::Model *log= resources->model("log");
        //shader
        resources::Shader *shader = resources->shader("first");
        define_light(shader);

        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        glm::mat4 model = glm::mat4(1.0f);

            model           = glm::translate(model, glm::vec3(-6.0f, 1.4f, 6.0f));
            model=glm::rotate(model,glm::pi<float>()/(-4.5f),glm::vec3(0.0f,1.0f,0.0f));
            model           = glm::scale(model, glm::vec3(2.75f));
            shader->set_mat4("model", model);
            log->draw(shader);

    }

void MainController::draw_log2() {
        //model
        auto resources            = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics             = engine::core::Controller::get<engine::graphics::GraphicsController>();
        resources::Model *log= resources->model("log");
        //shader
        resources::Shader *shader = resources->shader("first");
        define_light(shader);

        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        glm::mat4 model = glm::mat4(1.0f);

        model           = glm::translate(model, glm::vec3(6.0f, 1.4f, 6.0f));
        model=glm::rotate(model,glm::pi<float>()/(4.5f)+glm::pi<float>(),glm::vec3(0.0f,1.0f,0.0f));
        model           = glm::scale(model, glm::vec3(2.75f));
        shader->set_mat4("model", model);
        log->draw(shader);

    }
void MainController::draw_cottage() {
        //model
        auto resources            = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics             = engine::core::Controller::get<engine::graphics::GraphicsController>();
        resources::Model *cottage = resources->model("cottage");
        //shader
        resources::Shader *shader = resources->shader("first");
        define_light(shader);
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());

        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::translate(model, glm::vec3(20.0f, -2.0f, -15.0f));
        model = glm::scale(model, glm::vec3(0.025f));
        shader->set_mat4("model", model);
        cottage->draw(shader);
    }

void MainController::draw_trees() {
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics  = engine::core::Controller::get<engine::graphics::GraphicsController>();

        resources::Model  *tree=resources->model("tree1");
        resources::Shader *shader = resources->shader("first");

        define_light(shader);
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view",       graphics->camera()->view_matrix());

        for (int j=1;j<10;j++) {
            float p=0.0f;
            if (j%2)    p=glm::pi<float>()/20;
            for (int i=0;i<20;i++) {

                float ugao=(2.0f* glm::pi<float>() / 20)*i+p;
                float x=cos(ugao)*(45.0f+8.0f*j)+10.0f;
                float z=sin(ugao)*(45.0f+8.0f*j)-30.0f;
                //resources::Model *tree=tree_models[i%3];
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(x, 0.0f, z));
                model = glm::rotate(model, ugao + glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::scale(model, glm::vec3(0.03f));
                shader->set_mat4("model", model);
                tree->draw(shader);
            }
        }
    }

void MainController::draw_floor() {
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics  = engine::core::Controller::get<engine::graphics::GraphicsController>();

        auto *surface = resources->parallax("ground",
            "resources/models/ground/ground_0029_color_2k.jpg",
            "resources/models/ground/ground_0029_normal_opengl_2k.png",
            "resources/models/ground/ground_0029_height_2k.png");

        resources::Shader *shader = resources->shader("floor");
        define_light(shader);
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view",       graphics->camera()->view_matrix());
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(150.0f, 1.0f, 150.0f));//pokirva krug drveca ne menjaj vise
        shader->set_mat4("model", model);
        //shader->set_mat4("model",      glm::mat4(1.0f));
        shader->set_vec3("viewPos",    graphics->camera()->Position);
        shader->set_float("tileScale",15.0);

        graphics->draw_parallax_mapping(shader, surface);

        // resources->model("ground")->draw(shader);
    }

void MainController::draw_skybox() {
        auto resources=engine::core::Controller::get<engine::resources::ResourcesController>();
        auto skybox=resources->skybox("night_sky");
        auto shader=resources->shader("skybox");
        auto graphics=engine::core::Controller::get<engine::graphics::GraphicsController>();
        shader->use();
        shader->set_int("skybox", 0);
        graphics->draw_skybox(shader,skybox);
    }

    void MainController::draw() {
        draw_firepit();
        draw_fire();
        draw_trees();
        draw_cottage();
        draw_log1();
        draw_log2();
        draw_floor();
        draw_skybox();
    }

    void MainController::end_draw() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        platform->swap_buffers();
    }

    void MainController::update_camera() {
        auto gui = engine::core::Controller::get<app::GUIController>();
        if (gui->is_enabled()) {
            return;
        }

        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        auto graphic  = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto camera   = graphic->camera();
        float dt      = platform->dt();

        // Use Pressed so holding the key moves continuously (JustPressed moves only for one frame).
        if (platform->key(engine::platform::KeyId::KEY_W).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_A).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_S).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_D).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_Q).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::UP, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_E).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::DOWN, dt);
        }
        auto mouse = platform->mouse();
        //spdlog::info("Scroll value: {}",  mouse.scroll);
        camera->rotate_camera(mouse.dx, mouse.dy);
        if (mouse.scroll != 0.0f){
            camera->zoom(mouse.scroll);
            graphic->perspective_params().FOV = glm::radians(camera->Zoom);
        }
    }
} // namespace engine::app
