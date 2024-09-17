#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "shader.hpp"
#include "scene_descriptor.hpp"
#include "scene_node.hpp"
#include "mesh.hpp"

#include "debug_ui.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "tinyfiledialogs.h"

Mesh* load_model(std::string& filepath) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Failed to load model: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    Mesh* mesh = new Mesh({}, {}, {});
    auto assimpMesh = scene->mMeshes[0];
    for (unsigned int i = 0; i < assimpMesh->mNumVertices; i++) {
        mesh->positions.push_back({assimpMesh->mVertices[i].x, assimpMesh->mVertices[i].y, assimpMesh->mVertices[i].z});
        mesh->normals.push_back({assimpMesh->mNormals[i].x, assimpMesh->mNormals[i].y, assimpMesh->mNormals[i].z});
    }

    for (unsigned int i = 0; i < assimpMesh->mNumFaces; i++) {
        aiFace face = assimpMesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            mesh->indices.push_back(face.mIndices[j]);
        }
    }

    return mesh;
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(1400, 800, "OpenGL Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize Glad" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Setup ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup ImGui platform/renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    /*// Create quad mesh

    std::vector<glm::vec3> positions = {
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {0.5f, 0.5f, 0.0f},
        {-0.5f, 0.5f, 0.0f}};

    std::vector<glm::vec2> texCoords = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}};

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0};
        */

    // Load model

    std::string full_path = "/";
    std::string filepath = tinyfd_openFileDialog("Open Model", full_path.c_str(), 0, nullptr, nullptr, 0);

    Mesh* mesh = load_model(filepath);

    mesh->init_mesh();

    // Scene tree

    SceneNode* _root = new SceneNode{};
    _root->m_meshes.push_back(mesh);
    SceneNode* _subnode = new SceneNode{glm::translate(glm::mat4(1.0f), {0.1, 0, 0.1})};
    _subnode->m_meshes.push_back(mesh);
    _root->m_children.push_back(_subnode);

    SceneDescriptor g_scene{};
    g_scene.scene_root = _root;

    // Load shaders

    GLuint g_program = glCreateProgram();
    loadShader(g_program, GL_VERTEX_SHADER, "../shaders/main/vertex.glsl");
    loadShader(g_program, GL_FRAGMENT_SHADER, "../shaders/main/fragment.glsl");
    glLinkProgram(g_program);

    // MPV Matrices

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.2f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1400.0f / 800.0f, 0.1f, 100.0f);

    // Debug

    DebugUI::init();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll events
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render ImGui
        ImGui::Render();

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update rotation
        glm::mat4 view_transform = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

        // Draw quad
        glUseProgram(g_program);
        setUniform(g_program, "model", glm::mat4{1.0f});
        setUniform(g_program, "view", view * view_transform);
        setUniform(g_program, "projection", projection);

        g_scene.render(g_program);

        // Swap buffers
        glfwSwapBuffers(window);
    }

    DebugUI::destroy();

    delete mesh;

    // Cleanup
    glDeleteProgram(g_program);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}