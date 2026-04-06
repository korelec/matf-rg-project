//
// Created by tea on 4/6/26.
//

#ifndef MATF_RG_PROJECT_GUICONTROLER_HPP
#define MATF_RG_PROJECT_GUICONTROLER_HPP



#include <engine/core/Engine.hpp>

namespace engine::app {
class GUIController final : public engine::core::Controller {
public:
    std::string_view name() const override {
        return "app::GUIController";
    }

private:
    void initialize() override;
    void poll_events() override;
    void draw() override;
};
} // namespace engine::app



#endif //MATF_RG_PROJECT_GUICONTROLER_HPP
