#include <glm/glm.hpp>
#include <vector>
#include <cmath>

class BezierCurve {
private:
    glm::mat4 bezierMatrix;

public:
    BezierCurve() {
        bezierMatrix = glm::mat4(glm::vec4(-1.0,  3.0, -3.0, 1.0),
                                 glm::vec4( 3.0, -6.0,  3.0, 0.0),
                                 glm::vec4(-3.0,  3.0,  0.0, 0.0),
                                 glm::vec4( 1.0,  0.0,  0.0, 0.0));
    }

    glm::vec3 evaluate(const glm::mat4x3& controlPoints, float t) const {
        // param vector [t^3, t^2, t, 1]
        glm::vec4 parameterVector = glm::vec4(pow(t, 3), pow(t, 2), t, 1.0f);

        return parameterVector * bezierMatrix * glm::transpose(controlPoints);
    }
};