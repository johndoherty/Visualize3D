#ifndef __MODEL_BUFFERS__
#define __MODEL_BUFFERS__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


struct Triangle {
    static constexpr int kVerticesCount = 9;
    static constexpr int kIndicesCount = 3;

    static const GLfloat kVertices[kVerticesCount];

    static const GLuint kIndices[kIndicesCount];
};





#endif // __MODEL_BUFFERS__
