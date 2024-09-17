#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glad/glad.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

class Mesh {
   public:
    GLuint vao, pos_vbo, norm_vbo, ebo;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

   public:
    Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<unsigned int> indices) {
        this->positions = positions;
        this->normals = normals;
        this->indices = indices;
    }

    void init_mesh() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &pos_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
        glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &norm_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, norm_vbo);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }

    void render(GLuint shader, const glm::mat4& parentTransform = glm::mat4(1.0f)) {
        setUniform(shader, "model", parentTransform);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    ~Mesh() {
        if (pos_vbo)
            glDeleteBuffers(1, &pos_vbo);
        if (norm_vbo)
            glDeleteBuffers(1, &norm_vbo);
        if (ebo)
            glDeleteBuffers(1, &ebo);
        if (vao)
            glDeleteVertexArrays(1, &vao);
    }
};

#endif  // MESH_HPP