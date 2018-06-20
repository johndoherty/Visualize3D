#include "Renderer.h"
#include "Utils.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>

using namespace glm;

const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

struct InteractionState {
    bool mouse_down;
    bool dragging;
    glm::vec2 drag_origin;
    float zoom;
    glm::mat4 rotation;
};

InteractionState g_interaction_state;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) { 
       g_interaction_state.mouse_down = true;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        g_interaction_state.mouse_down = false;
        g_interaction_state.dragging = false;
    }
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset < 0) {
        g_interaction_state.zoom *= 0.5f;
    } else if (yoffset > 0) {
        g_interaction_state.zoom *= 2.f;
    }

}

static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (g_interaction_state.mouse_down) {
        if (!g_interaction_state.dragging) {
            g_interaction_state.dragging = true;
            g_interaction_state.drag_origin = glm::vec2(xpos, ypos);
        } else {
            glm::vec2 drag_position = glm::vec2(xpos, ypos);
            glm::vec2 delta = drag_position - g_interaction_state.drag_origin;

            glm::mat4 rotation_x = glm::rotate(glm::mat4(1.f), glm::radians(delta[1]), glm::vec3(1.f, 0.f, 0.f));
            glm::mat4 rotation_y = glm::rotate(glm::mat4(1.f), glm::radians(delta[0]), glm::vec3(0.f, 1.f, 0.f));
            g_interaction_state.rotation = rotation_x * rotation_y;
        }
    }
}

const char * const Renderer::kDefaultTitle = "Renderer";

Renderer::Renderer() {
    InitializeWindow(std::string(kDefaultTitle));
}

Renderer::Renderer(const std::string& title) {
    InitializeWindow(title);
}

void Renderer::InitializeWindow(const std::string& title) {
    window_ = nullptr;

    g_interaction_state.mouse_down = false;
    g_interaction_state.dragging = false;
    g_interaction_state.zoom = 1.f;
    g_interaction_state.rotation = glm::mat4(1.f);

    /* Initialize the library */
    if (!glfwInit()) {
        printf("Initialization failed\n");
        return;
    }

    /* Create window */
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    width_ = 1024;
    height_ = 768;

    window_ = glfwCreateWindow(width_, height_, title.c_str(), NULL, NULL);
    if (!window_) {
        printf("Failed to open window\n");
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window_);

    glewExperimental=true;
    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        return;
    }

    /* Callbacks */
    glfwSetKeyCallback(window_, KeyCallback);
    glfwSetMouseButtonCallback(window_, MouseButtonCallback);
    glfwSetScrollCallback(window_, ScrollCallback);
    glfwSetCursorPosCallback(window_, CursorPositionCallback);

    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    view_matrix_ = glm::lookAt(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
}

Renderer::~Renderer() {
    if (window_) {
        glfwTerminate();
        window_ = nullptr;
    }
}


void Renderer::AddClickCallback() {

}

void Renderer::AddKeyPressCallback() {

}

int Renderer::AddModel(const Model& model) {
    models_.push_back(model);

    const Model& new_model = models_.back();
    const GLfloat* vertex_buffer = new_model.GetVertexBuffer();
    const size_t vertex_buffer_size = sizeof(GLfloat) * new_model.GetVertexCount();

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, vertex_buffer, GL_STATIC_DRAW);

    vertex_buffers_.push_back(vertexbuffer);

    return models_.size() - 1;
}

void Renderer::SetViewMatrix(const glm::mat4& view_matrix) {
    view_matrix_ = view_matrix;
}


bool Renderer::Run() {
    if (!window_) {
        printf("Failed to initialize context\n");
        return false;
    }

    glfwMakeContextCurrent(window_);

    GLuint program_id = LoadShaders("../VertexShader.glsl", "../FragmentShader.glsl");
    GLuint mvp_id = glGetUniformLocation(program_id, "MVP");

    glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float) width_ / (float)height_, 0.1f, 100.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window_)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program_id);

        const float zoom = g_interaction_state.zoom;

        const glm::mat4 rotated_view = g_interaction_state.rotation * view_matrix_;
        const glm::mat4 frame_view_matrix = glm::scale(rotated_view, glm::vec3(zoom, zoom, zoom));
        const glm::mat4 view_projection = projection_matrix * frame_view_matrix;

        for (int i = 0; i < models_.size(); i++) {
            const Model& model = models_[i];
            const GLuint vertex_buffer = vertex_buffers_[i];
            const glm::mat4 mvp = view_projection * model.GetModelMatrix();

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
            glVertexAttribPointer(
               0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
               3,                  // size
               GL_FLOAT,           // type
               GL_FALSE,           // normalized?
               0,                  // stride
               (void*)0            // array buffer offset
            );

            glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);

            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, model.GetVertexCount());
            glDisableVertexAttribArray(0);
        }


        /* Swap front and back buffers */
        glfwSwapBuffers(window_);

        /* Poll for and process events */
        glfwWaitEvents();
    }

    // glfwTerminate();
    return true;
}
