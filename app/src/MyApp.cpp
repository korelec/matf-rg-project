//
// Created by tea on 4/5/26.
//

#include "../include/MyApp.hpp"
#include "MyApp.hpp"

#include <GuiControler.hpp>
#include <GuiLightController.hpp>
#include <MainControler.hpp>
#include <spdlog/spdlog.h>

namespace myapp {
void MyApp::app_setup() {
    auto main_controller = register_controller<engine::app::MainController>();
    auto gui_controller  = register_controller<engine::app::GUIController>();
    auto gui_light_contoler = register_controller<engine::app::GUILightController>();
    main_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
    gui_controller->after(main_controller);
    gui_light_contoler->after(main_controller);
    spdlog::info("Application setup complete!");
}
} // myapp
