#ifndef __MODEL__
#define __MODEL__

#include "ModelBuffers.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>


struct Model {
    enum class Type{Triangles, Lines};

    glm::mat4 position;
    glm::vec3 color;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    Type type;
};

inline Model MakeTriangle(const glm::mat4& position, const glm::vec3& color) {
    Model model;

    model.position = position;
    model.color = color;
    model.vertices.assign(Triangle::kVertices, Triangle::kVertices + Triangle::kVerticesCount);
    model.indices.assign(Triangle::kIndices, Triangle::kIndices + Triangle::kIndicesCount);
    model.type = Model::Type::Triangles;
    return model;
}

inline Model MakeTriangleWireFrame(const glm::mat4& position, const glm::vec3& color) {
    Model model;

    model.position = position;
    model.color = color;
    model.vertices.assign(TriangleWireFrame::kVertices, TriangleWireFrame::kVertices + TriangleWireFrame::kVerticesCount);
    model.indices.assign(TriangleWireFrame::kIndices, TriangleWireFrame::kIndices + TriangleWireFrame::kIndicesCount);
    model.type = Model::Type::Lines;
    return model;
}

inline Model MakeCube(const glm::mat4& position, const glm::vec3& color) {
    Model model;

    model.position = position;
    model.color = color;
    model.vertices.assign(Cube::kVertices, Cube::kVertices + Cube::kVerticesCount);
    model.indices.assign(Cube::kIndices, Cube::kIndices + Cube::kIndicesCount);
    model.type = Model::Type::Triangles;
    return model;
}

inline Model MakeSphere(const glm::mat4& position) {return Model {};}


#endif // __MODEL__
