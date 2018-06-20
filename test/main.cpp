#include "Config.h"
#include "Model.h"
#include "Renderer.h"
#include "Utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>

int main() {
    printf("Version: %d.%d\n", VERSION_MAJOR, VERSION_MINOR);

    Renderer renderer;
    renderer.AddModel(Model::Triangle(glm::mat4(1.0f), glm::vec3(1.f, 0.f, 0.f)));
    renderer.AddModel(Model::Triangle(glm::translate(glm::mat4(2.0f), glm::vec3(1.0f, 0.f, 0.f)), glm::vec3(1.f, 0.f, 0.f)));

    const glm::mat4 view_matrix = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    renderer.SetViewMatrix(view_matrix);

    if(!renderer.Run()) {
        printf("Renderer failed to run\n");
    }

    return 0;
}
