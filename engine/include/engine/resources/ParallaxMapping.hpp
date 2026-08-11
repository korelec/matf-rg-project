//
// Created by tea on 8/9/26.
//
/**
 * @file ParallaxMapping.hpp
 * @brief Defines the Parallax class that serves as the interface for parallax-mapped surface rendering.
*/

#ifndef MATF_RG_PROJECT_PARALLAXMAPPING_HPP
#define MATF_RG_PROJECT_PARALLAXMAPPING_HPP

#include <engine/resources/Texture.hpp>

namespace engine::resources {
/**
* @class Parallax
* @brief Represents a flat, parallax-mapped surface within the OpenGL context.
*/
class Parallax {
    friend class ResourcesController;

public:
    /**
    * @brief Returns the OpenGL ID of the shared quad's vertex array object.
    * @returns The OpenGL ID of the vertex array object.
    */
    uint32_t vao() const { return m_vao; }
    /**
    * @brief Returns the diffuse (color) texture of the surface.
    * @returns Pointer to the diffuse Texture.
    */
    Texture *diffuse() const { return m_diffuse; }

    /**
    * @brief Returns the normal map texture of the surface.
    * @returns Pointer to the normal Texture.
    */
    Texture *normal() const { return m_normal; }

    /**
    * @brief Returns the height map texture of the surface, used for the parallax offset.
    * @returns Pointer to the height Texture.
    */
    Texture *height() const { return m_height; }

    /**
    * @brief Destroys the surface's vertex array object in the OpenGL context.
    */
    void destroy();

private:
    Parallax() = default;

    /**
    * @brief Constructs a Parallax surface object, taking its VAO from the shared @ref GraphicsController quad.
    * @param diffuse Pointer to the diffuse Texture.
    * @param normal Pointer to the normal Texture.
    * @param height Pointer to the height Texture.
    */
    Parallax( Texture *diffuse, Texture *normal, Texture *height);

    uint32_t m_vao{0};
    Texture *m_diffuse{nullptr};
    Texture *m_normal{nullptr};
    Texture *m_height{nullptr};
};
}// namespace engine::resources

#endif //MATF_RG_PROJECT_PARALLAXMAPPING_HPP
