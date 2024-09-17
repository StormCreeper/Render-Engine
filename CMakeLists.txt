cmake_minimum_required(VERSION 3.5)

project(TestRenderer)

set(SOURCES
    main.cpp
    shader.hpp
    shader.cpp
    scene_node.hpp
    scene_descriptor.hpp
    mesh.hpp
    camera.hpp
    debug_ui.hpp
    event_system.hpp

    tinyfiledialogs.c
    stb_image.h
    tinyfiledialogs.h
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_sources(${PROJECT_NAME} PRIVATE dep/glad/src/glad.c)
target_include_directories(${PROJECT_NAME} PRIVATE dep/glad/include)

add_subdirectory(dep/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(dep/glm)
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory(dep/imgui)
target_link_libraries(${PROJECT_NAME} IMGUI)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/libs CACHE PATH "Missing description." FORCE)
FetchContent_Declare(assimp
GIT_REPOSITORY https://github.com/assimp/assimp.git
GIT_TAG master)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(assimp)
target_include_directories(${PROJECT_NAME} PRIVATE libs/assimp-src/include)
target_link_libraries(${PROJECT_NAME} assimp)


target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})