#pragma once

#include <glm/glm.hpp>

class Math
{
public:
    constexpr static const float Pi = 3.1415926536f;

    static float Lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    static glm::vec2 Lerp(const glm::vec2& a, const glm::vec2& b, float t)
    {
        return glm::vec2(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t));
    }

    static glm::vec3 Lerp(const glm::vec3& a, const glm::vec3& b, float t)
    {
        return glm::vec3(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.z, b.z, t));
    }

    static glm::vec4 Lerp(const glm::vec4& a, const glm::vec4& b, float t)
    {
        return glm::vec4(Lerp(a.r, b.r, t), Lerp(a.g, b.g, t), Lerp(a.b, b.b, t), Lerp(a.a, b.a, t));
    }
};
