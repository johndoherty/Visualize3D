#include "ModelBuffers.h"

const GLfloat Triangle::kVertices[kVerticesCount] = {
    -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

const GLuint Triangle::kIndices[kIndicesCount] = {0, 1, 2};
