#include "Config.h"
#include "Visualize3D/Model.h"
#include "Visualize3D/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>
#include <thread>

void RunRenderer() {
    Renderer renderer;
    // renderer.AddModel(MakeTriangleWireFrame(glm::mat4(1.0f), glm::vec3(1.f, 0.f, 0.f)));
    // renderer.AddModel(MakeTriangle(glm::translate(glm::mat4(2.0f), glm::vec3(1.0f, 0.f, 0.f)), glm::vec3(1.f, 0.f, 0.f)));
    renderer.AddModel(MakeCube(glm::mat4(1.0f), glm::vec3(1.f, 0.f, 0.f)));

    const glm::mat4 view_matrix = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    renderer.SetViewMatrix(view_matrix);

    if(!renderer.Run()) {
        printf("Renderer failed to run\n");
    }
}

int main() {
    printf("Version: %d.%d\n", VERSION_MAJOR, VERSION_MINOR);

    RunRenderer();

    return 0;
}
