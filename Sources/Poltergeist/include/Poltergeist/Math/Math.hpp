#pragma once

#include <cmath>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <numbers>
#include "Poltergeist/Types.hpp"

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;
using Quat = glm::quat;

/** @brief Converts -180 - 180 range angle to -360 - 360 range.
 *  @param angle The angle to convert in degrees.
 *  @return The converted angle.
 */
f32 NormalizeAngle(f32 angle);
