#ifndef SCENE_DESCRIPTOR_HPP
#define SCENE_DESCRIPTOR_HPP

#include "scene_node.hpp"
#include "camera.hpp"

class SceneDescriptor {
   public:
    SceneNode *scene_root;
    std::vector<Camera *> cameras;
    int cameraIndex = 0;

   public:
    SceneDescriptor() {
    }

    void render(GLuint shader) {
        if (scene_root)
            scene_root->render(shader);
    }
    ~SceneDescriptor() {
        delete scene_root;
    }
};

#endif  // SCENE_DESCRIPTOR_HPP