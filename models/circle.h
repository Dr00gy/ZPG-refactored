#ifndef CIRCLE_H
#define CIRCLE_H

const int CIRCLE_SEGMENTS = 100; // Number of segments for the circle
const int CIRCLE_VERTICES_COUNT = (CIRCLE_SEGMENTS + 2) * 3; // center + segments

void generateCircleVertices(float* vertices, float radius) {
    vertices[0] = 0.0f; // Center vertex x
    vertices[1] = 0.0f; // Center vertex y
    vertices[2] = 0.0f; // Center vertex z

    for (int i = 0; i <= CIRCLE_SEGMENTS; ++i) {
        float angle = i * 2.0f * M_PI / CIRCLE_SEGMENTS;
        vertices[(i + 1) * 3] = radius * cos(angle);
        vertices[(i + 1) * 3 + 1] = radius * sin(angle);
        vertices[(i + 1) * 3 + 2] = 0.0f; // z coordinate
    }
}

#endif
