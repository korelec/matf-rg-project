//
// Created by tea on 4/5/26.
//

#ifndef MATF_RG_PROJECT_MYCONTROLER_HPP
#define MATF_RG_PROJECT_MYCONTROLER_HPP

#include <engine/core/Controller.hpp>

#include <engine/platform/Input.hpp>
#include <engine/platform/PlatformEventObserver.hpp>

namespace engine::app {

class MainController final : public engine::core::Controller {
public:
    std::string_view name() const override {
        return "app::MainController";
    }

private:
    void initialize() override;

    bool loop() override;

    void poll_events() override;

    void update() override;

    void begin_draw() override;

    void draw_firepit();
    void draw_fire();

    void draw() override;

    void end_draw() override;

    void draw_skybox();

    void update_camera();
};
}



#endif //MATF_RG_PROJECT_MYCONTROLER_HPP
