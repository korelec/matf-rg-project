//
// Created by tea on 4/5/26.
//

#include "../include/MainControler.hpp"


#include <engine/graphics/GraphicsController.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/graphics/OpenGL.hpp>

namespace engine::app {
    void MainPlatformEventObserver::on_key(engine::platform::Key) {
    }

    void MainPlatformEventObserver::on_mouse_move(engine::platform::MousePosition) {
    }

    void MainController::initialize() {
        engine::graphics::OpenGL::enable_depth_testing();
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
    }

    void MainController::begin_draw() {
    }



    void MainController::draw() {
    }

    void MainController::end_draw() {
    }


} // namespace engine::app
