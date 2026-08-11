//
// Created by tea on 8/9/26.
//
// clang-format off
#include <glad/glad.h>
// clang-format on
#include <engine/core/Controller.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/resources/ParallaxMapping.hpp>

namespace engine::resources {
void Parallax::destroy() {
    CHECKED_GL_CALL(glDeleteVertexArrays, 1, &m_vao);
}

Parallax::Parallax(Texture *diffuse, Texture *normal, Texture *height)
    : m_vao(engine::core::Controller::get<graphics::GraphicsController>()->quad().vao),
      m_diffuse(diffuse), m_normal(normal), m_height(height) {}

}// namespace engine::resources