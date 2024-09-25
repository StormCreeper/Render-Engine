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

inline void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                                            GLenum severity, GLsizei length,
                                            const GLchar* msg, const void* data) {
    char* _source;
    char* _type;
    char* _severity;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
            _source = "API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            _source = "WINDOW SYSTEM";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            _source = "SHADER COMPILER";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            _source = "THIRD PARTY";
            break;

        case GL_DEBUG_SOURCE_APPLICATION:
            _source = "APPLICATION";
            break;

        case GL_DEBUG_SOURCE_OTHER:
            _source = "UNKNOWN";
            break;

        default:
            _source = "UNKNOWN";
            break;
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            _type = "ERROR";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            _type = "DEPRECATED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            _type = "UDEFINED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_PORTABILITY:
            _type = "PORTABILITY";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE:
            _type = "PERFORMANCE";
            break;

        case GL_DEBUG_TYPE_OTHER:
            _type = "OTHER";
            break;

        case GL_DEBUG_TYPE_MARKER:
            _type = "MARKER";
            break;

        default:
            _type = "UNKNOWN";
            break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            _severity = "HIGH";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            _severity = "MEDIUM";
            break;

        case GL_DEBUG_SEVERITY_LOW:
            _severity = "LOW";
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            _severity = "NOTIFICATION";
            break;

        default:
            _severity = "UNKNOWN";
            break;
    }

    printf("%d: %s of %s severity, raised from %s: %s\n",
           id, _type, _severity, _source, msg);
}

#endif  // DEBUG_UI_HPP