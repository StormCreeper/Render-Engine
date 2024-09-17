#ifndef DEBUG_UI_HPP
#define DEBUG_UI_HPP

#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

class DebugUI {
   private:
    GLuint debug_program;

   public:
    inline static void init() {}
    inline static void destroy() {}
};

#endif  // DEBUG_UI_HPP