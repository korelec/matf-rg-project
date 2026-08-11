

#ifndef MATF_RG_PROJECT_GUILIGHTCONTROLLER_HPP
#define MATF_RG_PROJECT_GUILIGHTCONTROLLER_HPP



#include <engine/core/Engine.hpp>

namespace engine::app {
class GUILightController final : public engine::core::Controller {
public:
    std::string_view name() const override {
        return "app::GUILightController";
    }
    float strengthfire() const {return strength_fire;}
    glm::vec3 colorfire() const {return color_fire;}

private:
    float strength_fire=0.5f;
    glm::vec3 color_fire=glm::vec3(1.0f,0.75f,0.75f);
    void initialize() override;
    void poll_events() override;
    void draw() override;
};
} // namespace engine::app



#endif //MATF_RG_PROJECT_GUILIGHTCONTROLLER_HPP