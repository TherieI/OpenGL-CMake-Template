#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// GameEngine includes
#include "Settings.h"
#include "InputManager.h"

namespace GameEngine {

    double lastFrame;
    double deltaTime;

    /*
    * Returns -1 on failure
    */
    int init(int major_version, int minor_version) {
        // GLFW is used to manage windows and input
        glfwInit();
        if (glfwInit() == GL_FALSE) {
            std::cout << "Failed to initialize GLAD\n";
            return -1;
        }
        // Ensure GLFW is running OpenGL V.MAJOR.MINOR
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        return 0;
    }

    /*
    * Returns nullptr on failure
    */
    GLFWwindow* createWindow() {
        GLFWmonitor* monitor = nullptr;
        if (Settings::fullscreen == true) {
            monitor = glfwGetPrimaryMonitor();
        }
        GLFWwindow* win = glfwCreateWindow(
            Settings::windowWidth,
            Settings::windowHeight,
            Settings::windowTitle,
            monitor, // Monitor, use glfwPrimaryMonitor() for full-screen
            nullptr  // Share, resource sharing
        );
        // If window is a null pointer, the creation has failed
        if (win == nullptr) {
            std::cout << "Failed to create GLFW window\n";
            glfwTerminate();
            return nullptr;
        }
        glfwMakeContextCurrent(win);
        // Check if glad was able to retrieve pointers to OpenGL functions
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD\n";
            return nullptr;
        }
        return win;
    }
       
    void update() {
        int currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

}