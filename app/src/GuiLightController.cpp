
#include <GuiLightController.hpp>

#include <engine/graphics/GraphicsController.hpp>
#include <imgui.h>

namespace engine::app {
void GUILightController::initialize() {
    set_enable(true);
}

void GUILightController::poll_events() {
    const auto platform = engine::core::Controller::get<platform::PlatformController>();
    if (platform->key(platform::KeyId::KEY_F).state() == platform::Key::State::JustPressed) {
        set_enable(!is_enabled());
    }

}

void GUILightController::draw() {
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
    graphics->begin_gui();
    ImVec2 window_pos=ImVec2(ImGui::GetIO().DisplaySize.x-10.0f,ImGui::GetIO().DisplaySize.y-10.0f);
    ImVec2 pivot=ImVec2(1.0f,1.0f);
    ImGui::SetNextWindowPos(window_pos,ImGuiCond_Always,pivot);
    ImGui::Begin("Fire");
    ImGui::Text("podesavanje vatre");
    ImGui::SliderFloat("setlo",&strength_fire,0.01f,1.0f);
    ImGui::ColorEdit3("boja", reinterpret_cast<float *>(&color_fire));
    ImGui::End();
    graphics->end_gui();
}
} // namespace engine::app