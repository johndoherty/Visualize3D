#ifndef __MODEL__
#define __MODEL__

#include "ModelBuffers.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

class Model {
public:
    Model() = default;
    Model(const glm::mat4& position, const glm::vec3& color) : position_(position), color_(color) {}

    const glm::mat4& GetModelMatrix() const {return position_;}
    void SetModelMatrix(const glm::mat4& model_matrix);

    const glm::vec3& GetColor() const;
    void SetColor(const glm::vec3& color);

    const GLfloat* GetVertexBuffer() const {return vertices_.data();}
    const size_t GetVertexCount() const {return vertices_.size();}
    const GLint* GetIndexBuffer() const {return indices_.data();}
    const size_t GetIndexCount() const {return indices_.size();}
private:
    glm::mat4 position_;
    glm::vec3 color_;
    std::vector<GLfloat> vertices_;
    std::vector<GLint> indices_;
};

inline Model MakeTriangle(const glm::mat4& position, const glm::vec3& color) {

    Model model(position, color);
    model.vertices_.assign(Triangle::kVertices, Triangle::kVertices + Triangle::kVerticesCount);
    model.indices_.assign(Triangle::kIndices, Triangle::kIndices + Triangle::kIndicesCount);
    return model;
}

inline Model MakeTriangleWireFrame(const glm::mat4& position, const glm::vec3& color) {return Model();}
inline Model MakeCube(const glm::mat4& position) {return Model();}
inline Model MakeSphere(const glm::mat4& position) {return Model();}


#endif // __MODEL__