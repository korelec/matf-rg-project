//
// Created by tea on 4/5/26.
//

#include "../include/MyApp.hpp"
#include "MyApp.hpp"

#include <MainControler.hpp>
#include <spdlog/spdlog.h>

namespace myapp {
void MyApp::app_setup() {
    auto main_controller = register_controller<engine::app::MainController>();
    main_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
    spdlog::info("Application setup complete!");
}
} // myapp
