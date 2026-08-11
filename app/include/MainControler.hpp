//
// Created by tea on 4/5/26.
//

#ifndef MATF_RG_PROJECT_MYCONTROLER_HPP
#define MATF_RG_PROJECT_MYCONTROLER_HPP

#include <engine/core/Controller.hpp>

#include <engine/platform/Input.hpp>
#include <engine/platform/PlatformEventObserver.hpp>
#include <engine/resources/Shader.hpp>

namespace engine::app {

class MainController final : public engine::core::Controller {
public:
    std::string_view name() const override {
        return "app::MainController";
    }

private:
    void initialize() override;

    bool loop() override;



    void update() override;

    void begin_draw() override;

    void define_light(engine::resources::Shader* shader);

    void draw_firepit();
    void draw_fire();
    void draw_log1();
    void draw_log2();
    void draw_cottage();
    void draw_trees();
    void draw_floor();

    void draw() override;

    void end_draw() override;

    void draw_skybox();

    void update_camera();
    float holdTime = 0.0f;
};
}



#endif //MATF_RG_PROJECT_MYCONTROLER_HPP
