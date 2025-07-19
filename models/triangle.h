#ifndef TRIANGLE_H
#define TRIANGLE_H

const int TRIANGLE_VERTICES_COUNT = 9; // 3 vertices * 3 coordinates

void generateTriangleVertices(float* vertices) {
    vertices[0] =  0.0f;  vertices[1] =  0.5f;  vertices[2] = 0.0f; // Top vertex
    vertices[3] = -0.5f;  vertices[4] = -0.5f;  vertices[5] = 0.0f; // Bottom-left
    vertices[6] =  0.5f;  vertices[7] = -0.5f;  vertices[8] = 0.0f; // Bottom-right
}

#endif
