#ifndef SQUARE_H
#define SQUARE_H

const int SQUARE_VERTICES_COUNT = 12; // 4 vertices * 3 coordinates

void generateSquareVertices(float* vertices) {
    vertices[0] = -0.5f; vertices[1] = -0.5f; vertices[2] = 0.0f; // Bottom-left
    vertices[3] =  0.5f; vertices[4] = -0.5f; vertices[5] = 0.0f; // Bottom-right
    vertices[6] =  0.5f; vertices[7] =  0.5f; vertices[8] = 0.0f; // Top-right
    vertices[9] = -0.5f; vertices[10] =  0.5f; vertices[11] = 0.0f; // Top-left
}

#endif
