cmake_minimum_required(VERSION 3.5)

project(TestRenderer)

set(SOURCES
    main.cpp
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

target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})