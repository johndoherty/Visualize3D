#include "Visualize3D/ModelBuffers.h"

const GLfloat Triangle::kVertices[kVerticesCount] = {
    -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

const GLuint Triangle::kIndices[kIndicesCount] = {0, 1, 2};

const GLfloat TriangleWireFrame::kVertices[kVerticesCount] = {
    -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

const GLuint TriangleWireFrame::kIndices[kIndicesCount] = {0, 1, 1, 2, 2, 0};

const GLfloat Cube::kVertices[kVerticesCount] = {
	-1.0f, 1.f, 0.0f,
	-1.0f, -1.f, 0.0f,
	1.0f, -1.f, 0.0f,
	1.0f, 1.f, 0.0f,
	1.0f, 1.f, -1.0f,
	1.0f, -1.f, -1.0f,
	-1.0f, -1.f, -1.0f,
	-1.0f, 1.f, -1.0f,
};

const GLuint Cube::kIndices[kIndicesCount] = {
	0, 1, 2, // Front
	0, 2, 3, // Front
	4, 5, 6, // Back
	4, 6, 7, // Back
	4, 0, 3, // Top
	4, 7, 0, // Top
};