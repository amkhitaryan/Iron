#pragma once

#include <GLM/glm.hpp>
#include "KeyCodes.h"
#include "MouseCodes.h"
#include "../Rendering/Screen.h"

class GLFWwindow;

class Input
{
public:
    static void PollEvents();
    static bool IsKeyPressed(KeyCodes::KeyCode code);
    static bool IsMouseButtonPressed(MouseCodes::MouseCode button);
    static glm::vec2 GetMousePosition();
private:
    static void Init(GLFWwindow* window);

    friend class Screen;
};