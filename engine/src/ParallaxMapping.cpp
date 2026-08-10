//
// Created by tea on 8/9/26.
//
// clang-format off
#include <glad/glad.h>
// clang-format on
#include <engine/graphics/OpenGL.hpp>
#include <engine/resources/ParallaxMapping.hpp>

namespace engine::resources {
void Parallax::destroy() {
    CHECKED_GL_CALL(glDeleteVertexArrays, 1, &m_vao);
}
}// namespace engine::resources