#ifndef DEBUG_UI_HPP
#define DEBUG_UI_HPP

#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "mesh.hpp"
#include "shader.hpp"

class DebugUI {
   private:
    inline static GLuint debug_program;
    inline static GLuint debug_program_2d;

    inline static glm::vec3 m_color{0};

    inline static GLint current_program;

   public:
    static void init() {
        debug_program = glCreateProgram();
        loadShader(debug_program, GL_VERTEX_SHADER, "../shaders/debug/vertex.glsl");
        loadShader(debug_program, GL_FRAGMENT_SHADER, "../shaders/debug/fragment.glsl");
        glLinkProgram(debug_program);

        debug_program_2d = glCreateProgram();
        loadShader(debug_program_2d, GL_VERTEX_SHADER, "../shaders/debug2D/vertex.glsl");
        loadShader(debug_program_2d, GL_FRAGMENT_SHADER, "../shaders/debug2D/fragment.glsl");
        glLinkProgram(debug_program_2d);
    }
    inline static void destroy() {
        glDeleteProgram(debug_program);
        glDeleteProgram(debug_program_2d);
    }

    inline static void prefix() {
        // save state
        current_program = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);

        glUseProgram(debug_program);
    }

    inline static void postfix() {
        // Restore state
        glUseProgram(current_program);
    }

   public:  // Drawing method
    static void debug_line(glm::vec3 start, glm::vec3 end) {
        glBegin(GL_LINES);
        glVertex3fv(&start.x);
        glVertex3fv(&end.x);
        glEnd();
    }
    static void debug_line_2D(glm::vec3 start, glm::vec3 end) {
    }
    static void debug_sphere(glm::vec3 center, float radius) {
    }

    static void setColor(glm::vec3 color) {
        m_color = color;
    }
};

#endif  // DEBUG_UI_HPP