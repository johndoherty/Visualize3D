#ifndef __RENDERER__
#define __RENDERER__

#include "Model.h"

#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>

class Renderer {
public:
    Renderer();
    Renderer(const std::string& title);
    ~Renderer();

    /* Callbacks */
    void AddClickCallback();
    void AddKeyPressCallback();

    /* Scene */
    int AddModel(const Model& model);

    int AddPoints(const std::vector<glm::vec3>& points);
    bool RemoveObject(int handle);
    void LookAt();

    /* Execute */
    bool Run();

    const bool IsInitialized() {return window_ != nullptr;}

private:
    void InitializeWindow(const std::string& title);

    static const char * const kDefaultTitle;

    int width_;
    int height_;
    GLFWwindow* window_;

    std::vector<Model> models_;
    std::vector<GLuint> vertex_buffers_;
    std::vector<GLuint> index_buffers_;
    std::unordered_map<int, Model> handle_to_model_;
};

#endif // __RENDERER__