#ifndef __MODEL__
#define __MODEL__

#include "ModelBuffers.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

struct Model {
    glm::mat4 position;
    glm::vec3 color;
    std::vector<GLfloat> vertices;
    std::vector<GLint> indices;
};

inline Model MakeTriangle(const glm::mat4& position, const glm::vec3& color) {
    Model model;

    model.position = position;
    model.color = color;
    model.vertices.assign(Triangle::kVertices, Triangle::kVertices + Triangle::kVerticesCount);
    model.indices.assign(Triangle::kIndices, Triangle::kIndices + Triangle::kIndicesCount);
    return model;
}

inline Model MakeTriangleWireFrame(const glm::mat4& position, const glm::vec3& color) {return Model {};}
inline Model MakeCube(const glm::mat4& position) {return Model {};}
inline Model MakeSphere(const glm::mat4& position) {return Model {};}


#endif // __MODEL__
