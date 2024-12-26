#include "Poltergeist/Math/Math.hpp"

f32 NormalizeAngle(f32 angle) {
    if (angle < 0.f) {
        angle = glm::fmod(angle, 360.f) + 360.f;
    }

    if (angle > 360.f) {
        angle = glm::fmod(angle, 360.f);
    }

    return angle > 180.f ? angle - 360.f : angle;
}
