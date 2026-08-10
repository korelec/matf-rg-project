//
// Created by tea on 8/9/26.
//

#ifndef MATF_RG_PROJECT_PARALLAXMAPPING_HPP
#define MATF_RG_PROJECT_PARALLAXMAPPING_HPP

#include <engine/resources/Texture.hpp>

namespace engine::resources {
class Parallax {
    friend class ResourcesController;

public:
    uint32_t vao() const { return m_vao; }
    Texture *diffuse() const { return m_diffuse; }
    Texture *normal() const { return m_normal; }
    Texture *height() const { return m_height; }
    void destroy();

private:
    Parallax() = default;
    Parallax(uint32_t vao, Texture *diffuse, Texture *normal, Texture *height)
        : m_vao(vao), m_diffuse(diffuse), m_normal(normal), m_height(height) {}

    uint32_t m_vao{0};
    Texture *m_diffuse{nullptr};
    Texture *m_normal{nullptr};
    Texture *m_height{nullptr};
};
}// namespace engine::resources

#endif //MATF_RG_PROJECT_PARALLAXMAPPING_HPP
