#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <vector>
#include <glm/glm.hpp>
#include "mesh.hpp"

class SceneNode {
   public:
    SceneNode() : m_transform(1.0f) {}

    void setTransform(const glm::mat4& transform) { m_transform = transform; }
    const glm::mat4& getTransform() const { return m_transform; }

    void render(const glm::mat4& parentTransform = glm::mat4(1.0f)) {
        glm::mat4 globalTransform = parentTransform * m_transform;

        for (auto& mesh : m_meshes) {
            mesh.render(globalTransform);
        }

        for (auto& child : m_children) {
            child.render(globalTransform);
        }
    }

   private:
    glm::mat4 m_transform;

    std::vector<SceneNode> m_children;
    std::vector<Mesh> m_meshes;
};

#endif  // SCENE_NODE_HPP